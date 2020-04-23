#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdint.h>

#define BUFFER_SIZE 1000

char *ip = "127.0.0.1";
char *port = "1500";

int read_response(int socket_fd) {
  // read #resp
  char resp[1000];
  int len = read(socket_fd, resp, 999);
  resp[len] = '\0';
  if (len < 0) {
    perror("read response failed\n");
    return -1;
  } else {
    printf("Server: %s\n", resp);
    if (memcmp(resp, "You guessed my secret number!", 10) == 0) {
      return 1;
    } else {
      return 0;
    }
  }
}

int guess() {
  // connect
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    perror("socket creation failed\n");
    close(socket_fd);
    return 1;
  }

  struct addrinfo hints, *results;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  int retval = getaddrinfo(ip, port, &hints, &results);
  if (retval != 0) {
    perror("get addr info failed\n");
    freeaddrinfo(results);
    close(socket_fd);
    return 1;
  }

  int res = connect(socket_fd, results->ai_addr, results->ai_addrlen);
  if (res < 0) {
    freeaddrinfo(results);
    close(socket_fd);
    return 1;
  }

  char resp[1000];
  printf("Client: ");
  scanf("%s", (char*)&resp);
  if (strlen(resp) == 1 && resp[0] == 'q') {
    printf("Thanks for playing!\n");
    // clean up
    freeaddrinfo(results);
    int close_status = close(socket_fd);
    if (close_status < 0) {
      perror("close guess connect failed\n");
    }
    return 1;
  } else {
    // send guess
    write(socket_fd, resp, strlen(resp));
    // read response
    int read_status = read_response(socket_fd);
    // clean up
    freeaddrinfo(results);
    int close_status = close(socket_fd);
    if (close_status < 0) {
      perror("close guess connect failed\n");
    }
    return read_status;
  }
}

int main(int argc, char **argv) {
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    perror("socket creation failed\n");
    close(socket_fd);
    return -1;
  }

  struct addrinfo hints, *results;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  int retval = getaddrinfo(ip, port, &hints, &results);
  if (retval != 0) {
    perror("get addr info failed\n");
    freeaddrinfo(results);
    close(socket_fd);
    return -1;
  }

  int res = connect(socket_fd, results->ai_addr, results->ai_addrlen);
  if (res < 0) {
    perror("connect");
    freeaddrinfo(results);
    close(socket_fd);
    return 0;
  } else {
    printf("Connected to guess server.\n\n");
  }

  // read welcome
  read_response(socket_fd);
  // guess loop
  int guess_status = 0;
  while (guess_status <= 0) {
    guess_status = guess();
  }

  freeaddrinfo(results);
  int close_status = close(socket_fd);
  if (close_status < 0) {
    perror("close guess connect failed\n");
  }
  return 0;
}
