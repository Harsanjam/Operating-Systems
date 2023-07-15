#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char** argv)
{
    // Local Variable list
    char cmd[100];
    char execCmd[100];
    int cmdIndex = 0;
    bool backgroundFlag; 
    char *argList[100];
    int argListIndex = 0;
    int argCount = 0; 

    while (1) {
        printf("Your command> \n");
        argList[argListIndex] = &cmd[0];
        argCount++;

        cmdIndex = 0;
        while((cmd[cmdIndex] = getchar()) != '\n')
        {
            if(cmd[cmdIndex] == ' ')
           { 
              cmd[cmdIndex] = NULL; 
              argListIndex++;
              argCount++; 
              argList[argListIndex] = &cmd[cmdIndex + 1];
           }

            cmdIndex++;
        }

        if(cmd[cmdIndex - 1] == '&' && cmd[cmdIndex - 2] != ' ')
        {
            backgroundFlag  = true;
        }
        // Create a new processes.
        pid_t childPID;

        if(fork()==0)
        {
            printf("Child process created\n");
            // Execute the commands.
            cmdIndex = 0;
            argListIndex = 0;
            for(argListIndex = 0; argListIndex < argCount;  argListIndex++)
            {
                cmdIndex = 0;

                while(*argList[argListIndex] != NULL)
                {
                    execCmd[cmdIndex] = *argList[argListIndex];
                    argList[argListIndex] = argList[argListIndex] + 1;
                    cmdIndex++;
                }
                execCmd[cmdIndex] = NULL;
                system(execCmd);
            }
            exit(0);
        }
        else
        {
            printf("Parent process is waiting \n");

            if(backgroundFlag == false)
            {
                childPID = wait(NULL);
            } 
            printf("Parent process ends.\n");
        }
    }
    return (EXIT_SUCCESS);
}


