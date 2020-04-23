#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#define MAX_ARGS 5
#define MAX_ARG_LEN 10
#define MAX_LINE_LEN 80
#define MAX_HISTORY_LEN 40

char history_lst[MAX_HISTORY_LEN][MAX_ARG_LEN];
int history_idx = 0;

pid_t Fork(void) {
  pid_t pid;
  if ((pid = fork()) < 0) {
    fprintf(stderr, "%s: %s\n", "fork error", strerror(errno));
    exit(0);
  }
  return pid;
}

char *Fgets(char *ptr, int n, FILE *stream) {
  char *rptr;
  if (((rptr = fgets(ptr, n, stream)) == NULL) && ferror(stream)) {
    fprintf(stderr, "%s\n", "fgets error");
    exit(0);
  }
  return rptr;
}

// print out help documentation
void print_help() {
  printf("Usage:\n"
    "> cd [directory]\n"
    "> help\n"
    "> exit\n"
    "> pwd\n"
    "> history\n");
}

// print out current working directory
void print_work_dir() {
  char cwd[100];
  getcwd(cwd, sizeof(cwd));
  printf("current working directory: %s\n", cwd);
}

// Is the command one built into the shell?
// That is, that the *shell* has implemented?
// If so, execute it here
int builtin_command(char** argv) {
  int kNumCmd = 5;
  char* cmd_lst[kNumCmd];
  int arg_idx = 0;

  cmd_lst[0] = "cd";
  cmd_lst[1] = "help";
  cmd_lst[2] = "exit";
  cmd_lst[3] = "pwd";
  cmd_lst[4] = "history";

  for (int i = 0; i < kNumCmd; i++) {
    if (strcmp(argv[0], cmd_lst[i]) == 0) {
      arg_idx = i + 1;
      break;
    }
  }

  return arg_idx;
}

// print out histories, max to MAX_HISTORY_LEN
void print_history() {
  for (int i = 0; i < history_idx; i++) {
    printf("history %d: ", i + 1);
    for (int j = 0; j < MAX_ARG_LEN; j++) {
      if (history_lst[i][j]) {
        printf("%c", history_lst[i][j]);
      }
    }
    printf("\n");
  }
}

// execute the given command
int execute_command(char** argv, int arg_idx) {
  switch (arg_idx) {
    case 1:  // cd
      printf("you're going to %s\n", argv[1]);
      chdir(argv[1]);
      return 1;
    case 2:  // help
      print_help();
      return 2;
    case 3:  // exit
      return 3;
    case 4:  // pwd
      print_work_dir();
      return 4;
    case 5:  // history
      print_history();
      return 5;
    default:
      break;
  }
  return 0;
}

// parse the argments and get the option
void parse_arg(char** arg_lst, char* arg_str) {
  char* token;
  int idx = 0;
  arg_lst[idx] = strtok(arg_str, " ");
  while (arg_lst[idx] != NULL) {
    arg_lst[++idx] = strtok(NULL, " ");
  }
}

// evaluate the command line input
void eval(char *cmdline) {
  char* argv[MAX_ARGS]; /* Argument list execve() */
  char buf[MAX_LINE_LEN]; /* Holds modified command line */
  pid_t pid; /* Process id */
  int child_status;

  parse_arg(argv, cmdline);

  snprintf(buf, MAX_LINE_LEN, "%s", cmdline);
  // strcpy(buf, cmdline);
  if (argv[0] == NULL)
    return;  /* Ignore empty lines */

  int arg_idx = builtin_command(argv);

  // Run the program/command
  if (arg_idx == 0) {  // not support
    printf("Command not found--Did you mean something else?\n");
  } else if (arg_idx == 1) {  // cd command
    execute_command(argv, arg_idx);
  } else {
    // What do we do if it *IS* a command built into the shell?
    // Create a child process
    pid_t pid = Fork();
    int status;
    if (pid == 0) {
      status = execute_command(argv, arg_idx);
      if (status == 3) {
        kill(pid, SIGINT);
      }
      exit(0);
    }
    /* Parent waits for foreground job to terminate */
    pid_t wpid = wait(&child_status);
    if (!WIFEXITED(child_status)) {
      // printf("Child terminated normally.\n");
    // } else {
      printf("Child terminated abnormally.\n");
    }
  }
  return;
}

// Create a signal handler
void sigint_handler(int sig) {
  // Ask yourself why is 35 the last parameter here?
  // SIGRTMIN is 34 or 35
  // it is the real-time signal to exit the program
  write(1, "k-sea-shell terminated\n", 35);
  exit(0);
}

int main() {
  // Install our signal handler
  signal(SIGINT, sigint_handler);

  char cmdline[MAX_LINE_LEN]; /* command line */

  pid_t pid;
  history_idx = 0;
  while (1) {
    /* read */
    printf("k-sea-shell> ");
    Fgets(cmdline, MAX_LINE_LEN, stdin);
    char *end;

    if (feof(stdin))
      exit(0);

    if ((end=strchr(cmdline, '\n')) != NULL) {
      *end = '\0';
    }
    snprintf(history_lst[history_idx++], MAX_LINE_LEN, "%s", cmdline);
    // strcpy(history_lst[history_idx++], cmdline);
    eval(cmdline);
  }
}
