#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

#include "DirectoryParser_MT.h"
#include "QueryProtocol.h"
#include "MovieSet.h"
#include "MovieIndex.h"
#include "MovieTitleIndex.h"
#include "DocIdMap.h"
#include "Hashtable.h"
#include "QueryProcessor.h"
#include "FileParser.h"
#include "FileCrawler.h"
#include "DirectoryParser.h"
#include "Util.h"

DocIdMap docs;
MovieTitleIndex docIndex;

#define BUFFER_SIZE 1000

#define SEARCH_RESULT_LENGTH 1500
char movieSearchResult[SEARCH_RESULT_LENGTH];

int Cleanup();

void sigint_handler(int sig) {
  write(0, "Exit signal sent. Cleaning up...\n", 34);
    Cleanup();
  exit(0);
}

void send_message(char *msg, int sock_fd) {
  printf("SERVER SENDING: %s", msg);
  printf("===\n");
  write(sock_fd, msg, strlen(msg));
}

void read_ack(int socket_fd) {
  char resp[1000];
  int len = read(socket_fd, resp, 999);
  resp[len] = '\0';
  int check_status = CheckAck((char*)&resp);
  if (check_status < 0) {
    perror("read ack failed\n");
  }
}

int HandleClient(int sock_fd) {
  // Step 5: Accept connection
  printf("Waiting for connection...\n");
  int client_fd = accept(sock_fd, NULL, NULL);
  printf("Client connected: client_fd=%d\n", client_fd);

  // Step 6: Read, then write if you want

  // Send ACK
  SendAck(client_fd);

  // Listen for query
  // If query is GOODBYE close connection
  char query[1000];
  int len = read(client_fd, query, sizeof(query) - 1);
  query[len] = '\0';
  printf("checking goodbye...%s\n", query);

  if (CheckGoodbye((char*)&query) < 0) {
    // Run query and get revsponses
    SearchResultIter iter = FindMovies(docIndex, (char*)&query);
    int num;
    if (iter == NULL) {
      num = 0;
    } else {
      num = NumResultsInIter(iter);
    }
    printf("num_responses: %d\n", num);
    // Send number of responses
    write(client_fd, &num, sizeof(1));

    // Wait for ACK
    read_ack(client_fd);

    if (num > 0) {
      // For each response
      SearchResult output;
      for (int i = 0; i < num; i++) {
        // Send response
        output = (SearchResult)malloc(sizeof(*output));
        if (output == NULL) {
          perror("malloc failed\n");
          break;
        }
        SearchResultGet(iter, output);
        CopyRowFromFile(output, docs, (char*)&movieSearchResult);
        write(client_fd, (char*)&movieSearchResult, strlen(movieSearchResult));

        free(output);
        output = NULL;

        // Wait for ACK
        read_ack(client_fd);

        // switch to next result
        SearchResultNext(iter);
      }

      // Cleanup
      printf("Destroying search result iter\n");
      DestroySearchResultIter(iter);
    }
  }

  // Send GOODBYE
  SendGoodbye(client_fd);

  // close connection.
  printf("Client connection closed.\n");
  close(client_fd);
  return 0;
}

int Setup(char *dir) {
  printf("Crawling directory tree starting at: %s\n", dir);
  // Create a DocIdMap
  docs = CreateDocIdMap();
  CrawlFilesToMap(dir, docs);
  printf("Crawled %d files.\n", NumElemsInHashtable(docs));

  // Create the index
  docIndex = CreateMovieTitleIndex();

  if (NumDocsInMap(docs) < 1) {
    printf("No documents found.\n");
    return 0;
  }

  // Index the files
  printf("Parsing and indexing files...\n");
  ParseTheFiles(docs, docIndex);
  printf("%d entries in the index.\n", NumElemsInHashtable(docIndex->ht));
  return NumElemsInHashtable(docIndex->ht);
}

int Cleanup() {
  DestroyMovieTitleIndex(docIndex);
  DestroyDocIdMap(docs);

  return 0;
}

int main(int argc, char **argv) {
  char *port = NULL;
  char *dir_to_crawl = NULL;

  // int debug_flag = 0;
  int c;

  while ((c = getopt(argc, argv, "dp:f:")) != -1) {
    switch (c) {
      case 'd':
        // debug_flag = 1;
        break;
      case 'p':
        port = optarg;
        break;
      case 'f':
        dir_to_crawl = optarg;
        break;
    }
  }

  if (port == NULL) {
    printf("No port provided; please include with a -p flag.\n");
    exit(0);
  }

  if (dir_to_crawl == NULL) {
    printf("No directory provided; please include with a -f flag.\n");
    exit(0);
  }

  // Setup graceful exit
  struct sigaction kill;

  kill.sa_handler = sigint_handler;
  kill.sa_flags = 0;  // or SA_RESTART
  sigemptyset(&kill.sa_mask);

  if (sigaction(SIGINT, &kill, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  int num_entries = Setup(dir_to_crawl);
  if (num_entries == 0) {
    printf("No entries in index. Quitting.\n");
    exit(0);
  }

  int s;


  // Step 1: Get address stuff
  struct addrinfo hints, *result;

  // Setting up the hints struct...
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  s = getaddrinfo("localhost", port, &hints, &result);
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(1);
  }

  // Step 2: Open socket
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  int yes = 1;

  // lose the pesky "Address already in use" error message
  if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
    perror("setsockopt");
    exit(1);
  }

  // Step 3: Bind socket
  if (bind(sock_fd, result->ai_addr, result->ai_addrlen) != 0) {
    perror("bind()");
    exit(1);
  }

  // Step 4: Listen on the socket
  if (listen(sock_fd, 10) != 0) {
    perror("listen()");
    exit(1);
  }
  freeaddrinfo(result);

  while (1) {
    HandleClient(sock_fd);
  }

  // Got Kill signal
  close(sock_fd);

  Cleanup();

  return 0;
}
