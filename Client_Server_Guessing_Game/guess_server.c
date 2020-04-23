#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

#define BUFFER_SIZE 1000
#define MAX_NUM 50
#define MIN_NUM 1

unsigned int seed;
char* ip = "127.0.0.1";
char* port = "1500";
char* plus_stmt = ", plus something I didn't understand";
char* final_stmt = "You guessed my secret number!\n"
                   "It only took you %d guesses%s.";

int valid = 0;
int invalid = 0;
int guess(int sock_fd, int target);
void send_msg(int client_fd, char* msg);
int read_num(int client_fd);
void sigint_handler(int sig);
int get_rand(int lower, int upper);


int get_rand(int lower, int upper) {
    seed++;
    return (rand_r(&seed) % (upper - lower + 1)) + lower;
}

int guess(int sock_fd, int target) {
  printf("Waiting for connection...\n");
  int client_fd = accept(sock_fd, NULL, NULL);
  printf("Client connected: client_fd=%d\n", client_fd);
  int num = read_num(client_fd);
  if (num <= 0 || num > 50) {
    send_msg(client_fd, "I don't recognize that number.\n"
      "Please guess a number between 1 and 50.");
    invalid++;
  } else {
    valid++;
    if (target == num) {
      char plus[BUFFER_SIZE] = {'\0'};
      if (invalid > 0) {
        snprintf(plus, BUFFER_SIZE, "%s", plus_stmt);
      }
      char msg[BUFFER_SIZE];
      snprintf(msg, BUFFER_SIZE, final_stmt, valid, plus);
      send_msg(client_fd, msg);
      return 1;
    } else if (target > num) {
      send_msg(client_fd, "Too low.");
    } else {
      send_msg(client_fd, "Too high.");
    }
  }
  return 0;
}

void send_msg(int client_fd, char* msg) {
  write(client_fd, msg, strlen(msg));
}

int read_num(int client_fd) {
  char resp[10];
  int len = read(client_fd, (char*)&resp, 9);
  resp[len] = '\0';
  if (len < 0) {
    perror("read response failed\n");
    return -1;
  } else {
    return atoi(resp);
  }
}

void sigint_handler(int sig) {
  write(0, "Exit signal sent.\nCleaning up...\n", 34);
  exit(0);
}

int main(int argc, char **argv) {
  valid = 0;
  invalid = 0;

  // Setup graceful exit
  struct sigaction kill;

  kill.sa_handler = sigint_handler;
  kill.sa_flags = 0;  // or SA_RESTART
  sigemptyset(&kill.sa_mask);

  if (sigaction(SIGINT, &kill, NULL) == -1) {
    perror("sigaction");
    exit(1);
  }

  int s;

  // Step 1: Get address stuff
  struct addrinfo hints, *result;

  // Setting up the hints struct...
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  s = getaddrinfo(ip, port, &hints, &result);
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
  int num = get_rand(MIN_NUM, MAX_NUM);
  printf("===answer: %d===\n", num);

  printf("Waiting for connection...\n");
  int client_fd = accept(sock_fd, NULL, NULL);
  printf("Client connected: client_fd=%d\n", client_fd);
  send_msg(client_fd,
    "Welcome! I've chosen a number between 1 and 50. Guess it!");

  int correct = 0;
  while (correct == 0) {  // not correct
    correct = guess(sock_fd, num);
  }

  // Got Kill signal
  close(sock_fd);
  return 0;
}
