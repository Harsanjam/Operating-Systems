#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 100
#define MAX_ARG_LENGTH 100

int main() {
  char line[MAX_LINE_LENGTH + 1];
  char *args[MAX_ARG_LENGTH + 1];
  int line_length;
  int argc;
  int i, j;
  pid_t pid;
  int wait_flag;

  while (1) {
    printf("Your command> ");

    // Read line from stdin
    line_length = 0;
    while (1) {
      int ch = getchar();
      if (ch == '\n' || ch == EOF) {
        break;
      }
      line[line_length++] = ch;
    }
    line[line_length] = '\0';

    // Check if line ends with &
    wait_flag = 1;
    if (line_length > 0 && line[line_length - 1] == '&') {
      wait_flag = 0;
      line[line_length - 1] = '\0';
    }

    // Parse line into arguments
    argc = 0;
    args[argc++] = strtok(line, " ");
    while (args[argc - 1] != NULL) {
      args[argc++] = strtok(NULL, " ");
    }
    args[argc - 1] = NULL;

    // Fork a new process
    pid = fork();
    if (pid == 0) {
      // Child process
      execvp(args[0], args);
      printf("Error: execvp failed\n");
      exit(1);
    } else if (pid > 0) {
      // Parent process
      if (wait_flag) {
        waitpid(pid, NULL, 0);
      }
    } else {
      // Fork failed
      printf("Error: fork failed\n");
    }
  }

  return 0;
}