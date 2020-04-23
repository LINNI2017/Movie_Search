#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>


#include "QueryProtocol.h"
#include "MovieSet.h"
#include "MovieIndex.h"
#include "DocIdMap.h"
#include "Hashtable.h"
#include "QueryProcessor.h"
#include "FileParser.h"
#include "DirectoryParser.h"
#include "FileCrawler.h"
#include "Util.h"

#define BUFFER_SIZE 1000

int Cleanup();

DocIdMap docs;
MovieTitleIndex docIndex;

#define SEARCH_RESULT_LENGTH 1500

char movieSearchResult[SEARCH_RESULT_LENGTH];

void sigchld_handler(int s) {
  write(0, "Handling zombies...\n", 20);
  // waitpid() might overwrite errno, so we save and restore it:
  int saved_errno = errno;

  while (waitpid(-1, NULL, WNOHANG) > 0);

  errno = saved_errno;
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

void sigint_handler(int sig) {
  write(0, "Ahhh! SIGINT!\n", 14);
  Cleanup();
  exit(0);
}

/**
 * Return 0 for successful connection;
 * Return -1 for some error.
 */
int HandleClient(int client_fd, char* query) {
  // Run query and get responses

  // Send number of responses

  // Wait for ACK

  // For each response

    // Send response

    // Wait for ACK

  // Send GOODBYE

  // close connection.

  // Run query and get revsponses
  SearchResultIter iter = FindMovies(docIndex, query);
  int num;
  if (iter == NULL) {
    num = 0;
  } else {
    num = NumResultsInIter(iter);
  }
  printf("num_responses: %d\n", num);
  // send number of responses
  write(client_fd, &num, sizeof(1));

  // wait for ACK
  read_ack(client_fd);

  if (num > 0) {
    // For each response
    SearchResult output;
    for (int i = 0; i < num; i++) {
      output = (SearchResult)malloc(sizeof(*output));
      if (output == NULL) {
        perror("malloc failed\n");
        break;
      }
      // find movie
      SearchResultGet(iter, output);
      CopyRowFromFile(output, docs, (char*)&movieSearchResult);

      // Send response
      write(client_fd, (char*)&movieSearchResult, strlen(movieSearchResult));

      // free movie
      free(output);
      output = NULL;

      // wait for ACK
      read_ack(client_fd);

      // switch to next result
      SearchResultNext(iter);
    }
    // Cleanup
    printf("Destroying search result iter\n");
    DestroySearchResultIter(iter);
  }
  // Send GOODBYE
  SendGoodbye(client_fd);

  // close connection.
  printf("Client connection closed.\n");
  close(client_fd);
  return 0;
}



/**
 * Handle connections for multiple clients.
 */
int HandleConnections(int sock_fd, int debug) {
  // Step 5: Accept connection
  // Fork on every connection

  printf("Waiting for connection...\n");
  int client_fd = accept(sock_fd, NULL, NULL);
  if (client_fd < 0) {
    perror("accept failed\n");
    close(client_fd);
  }
  int pid = fork();
  if (pid < 0) {
    perror("fork failed\n");
  } else if (pid == 0) {
    printf("Client connected: client_fd=%d\n", client_fd);
    // Send ACK
    int send_status = SendAck(client_fd);
    if (send_status < 0) {
      perror("send ack failed\n");
      return -1;
    }
    if (debug == 1) {
      sleep(10);
    }
    char query[1000];
    int len = read(client_fd, query, sizeof(query) - 1);
    query[len] = '\0';
    printf("checking goodbye...%s\n", query);
    int check_status = CheckGoodbye((char*)&query);
    if (check_status == 0) {
      close(client_fd);
      exit(0);
    } else {
      HandleClient(client_fd, (char*)&query);
      exit(0);
    }
  }
  return 0;
}

int Setup(char *dir) {
  struct sigaction sa;

  sa.sa_handler = sigchld_handler;  // reap all dead processes
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  struct sigaction kill;

  kill.sa_handler = sigint_handler;
  kill.sa_flags = 0;  // or SA_RESTART
  sigemptyset(&kill.sa_mask);

  if (sigaction(SIGINT, &kill, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

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
  // port
  char *port = NULL;
  char *dir_to_crawl = NULL;

  int debug_flag = 0;
  int c;

  while ((c = getopt(argc, argv, "dp:f:")) != -1) {
    switch (c) {
      case 'd':
        debug_flag = 1;
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

  struct sockaddr_in *result_addr = (struct sockaddr_in *) result->ai_addr;
  printf("Listening on file descriptor %d, port %d\n", sock_fd,
    ntohs(result_addr->sin_port));
  freeaddrinfo(result);

  while (1) {
    HandleConnections(sock_fd, debug_flag);
  }

  // Got Kill signal
  close(sock_fd);
  Cleanup();
  return 0;
}
