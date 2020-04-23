#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdint.h>

#include "QueryProtocol.h"

char *port_string = "1500";
uint16_t port;
char *ip = "127.0.0.1";

#define BUFFER_SIZE 1000

void read_response(int socket_fd) {
  char resp[1000];
  int len = read(socket_fd, resp, 999);
  resp[len] = '\0';
  if (strcmp(resp, "GOODBYE") == 0) {
    printf("Got %ld bytes. resp: %s\n", strlen(resp), resp);
  } else {
    printf("%s\n", resp);
  }
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

void send_ack(int socket_fd) {
  int send_status = SendAck(socket_fd);
  if (send_status < 0) {
    perror("send ack failed\n");
  }
}

void RunQuery(char *query) {
  // Find the address

  // Create the socket

  // Connect to the server

  // Do the query-protocol

  // Close the connection

  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    perror("socket creation failed\n");
    close(socket_fd);
    return;
  }

  struct addrinfo hints, *results;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  int retval = getaddrinfo(ip, port_string, &hints, &results);
  if (retval != 0) {
    perror("get addr info failed\n");
    freeaddrinfo(results);
    close(socket_fd);
    return;
  }

  int res = connect(socket_fd, results->ai_addr, results->ai_addrlen);
  if (res < 0) {
    perror("query connect failed\nconnect");
    freeaddrinfo(results);
    close(socket_fd);
    return;
  } else {
    printf("Connected to movie server.\n\n");
  }

  // read ack
  read_ack(socket_fd);

  // send query
  write(socket_fd, query, strlen(query));

  // read #resp
  int num;
  int read_status = read(socket_fd, &num, sizeof(1));
  if (read_status < 0) {
    perror("read num failed\n");
  } else {
    printf("Receiving %d results\n", num);
  }

  // send ack
  send_ack(socket_fd);

  // loop resp
  for (int i = 0; i < num;  i++) {
    // read result
    read_response(socket_fd);
    // send ack
    send_ack(socket_fd);
  }

  // summary report
  // printf("Got %d items!\n", num);
  // read goodbye
  read_response(socket_fd);
  freeaddrinfo(results);
  int close_status = close(socket_fd);
  if (close_status < 0) {
    perror("close query connect failed\n");
  }
}

void RunPrompt() {
  char input[BUFFER_SIZE];

  while (1) {
    printf("Enter a term to search for, or q to quit: ");
    scanf("%s", input);

    printf("input was: %s\n", input);

    if (strlen(input) == 1) {
      if (input[0] == 'q') {
        printf("Thanks for playing!\n");
        return;
      }
    }
    printf("\n\n");
    RunQuery(input);
  }
}

// This function connects to the given IP/port to ensure
// that it is up and running, before accepting queries from users.
// Returns 0 if can't connect; 1 if can.
int CheckIpAddress(char *ip, char *port) {
  // Connect to the server
  // Listen for an ACK
  // Send a goodbye
  // Close the connection

  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    perror("socket creation failed\n");
    close(socket_fd);
    return 0;
  }

  struct addrinfo hints, *results;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  int retval = getaddrinfo(ip, port_string, &hints, &results);
  if (retval != 0) {
    perror("get addr info failed\n");
    freeaddrinfo(results);
    close(socket_fd);
    return 0;
  }
  int res = connect(socket_fd,
    (struct sockaddr*)results->ai_addr, results->ai_addrlen);
  if (res < 0) {
    perror("check-ip connect failed\nconnect");
    freeaddrinfo(results);
    close(socket_fd);
    return 0;
  }

  char resp[1000];
  int len = read(socket_fd, resp, 999);
  resp[len] = '\0';

  int check_status = CheckAck((char*)&resp);
  if (check_status < 0) {
    perror("check ack failed\n");
    freeaddrinfo(results);
    close(socket_fd);
    return 0;
  }

  int send_status = SendGoodbye(socket_fd);
  if (send_status < 0) {
    perror("send goodbye failed\n");
    freeaddrinfo(results);
    close(socket_fd);
    return 0;
  }
  freeaddrinfo(results);
  int close_status = close(socket_fd);
  if (close_status < 0) {
    perror("close check-ip connect failed\n");
    return 0;
  }
  printf("Connected to movie server.\n\n");
  return 1;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Incorrect number of arguments.\n");
    printf("Correct usage: ./queryclient [IP] [port]\n");
  } else {
    ip = argv[1];
    port_string = argv[2];
  }

  if (CheckIpAddress(ip, port_string)) {
    RunPrompt();
  }
  return 0;
}
