#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// removes space between string of characters
char removeSpace(char *string) {
    int index = 0;
    for (int i = 0; string[i] != '\n'; i++) {
        if (string[i] != ' ') {
            string[index] = string[i];
            index++;
        }
    }
    string[index] = '\0';
    return *string;
}

// reads single line user input from terminal 
// the user inputs words separated by single space and | before the end
// command> ls | wc -w
int main(int argc, char**argv) {
    char input[100], parent[100], child[100];
    int indexParent = 0, indexChild = 0, indexCom1 = 0, indexCom2 = 0;
    bool test = false;

    printf("Your command> ");
    fgets(input, 100, stdin);

    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == '|' && input[i + 1] == ' ') {
            test = true;
        } else if (!test) {
            parent[indexParent++] = input[i];
        } else {
            child[indexChild++] = input[i];
        }
    }
// commands and list of arguments
    char *cmd1[100], *cmd2[100];
    char *token1 = strtok(parent, " ");
    while (token1 != NULL) {
        removeSpace(token1);
        cmd1[indexCom1++] = token1;
        token1 = strtok(NULL, " ");
    }
    cmd1[indexCom1] = NULL;

    char *token2 = strtok(child, " ");
    while (token2 != NULL) {
        removeSpace(token2);
        cmd2[indexCom2++] = token2;
        token2 = strtok(NULL, " ");
    }
    cmd2[indexCom2] = NULL;
    
// initialize file and create pipeline
    int fd[2];
    if (pipe(fd) == -1) {
        perror("Error with opening the pipe.");
        return 1;
    }

    if (fork() == 0) { // Child Process
        dup2(fd[1], 1);
        close(fd[0]);
        execvp(cmd1[0], cmd1);
        perror(cmd1[0]);
        exit(0);
        
    } else { // Parent Process
        dup2(fd[0], 0);
        close(fd[1]);
        execvp(cmd2[0], cmd2);
        perror(cmd2[0]);
    }
    return (EXIT_SUCCESS);
}
