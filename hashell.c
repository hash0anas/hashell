#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    puts("Welcome to the Hashell, a simple shell where you can execute simple programs, but don't use pipes or anything fancy.\n");
    char line[100];
    char* argv[20];
    while(1) {
        printf("hashell-> ");
        char* rv = fgets(line, 100, stdin);
        if(!rv || strcmp(line, "") == 0) continue;
        int ii = 0;
        char *p = strtok(line, " \t\r\n\v\f"); // POSIX white-space characters
        while(p != NULL) {
            argv[ii++] = strdup(p);
            p = strtok(NULL, " \t\r\n\v\f");
        }
        argv[ii] = NULL;
        
        if(strcmp(argv[0], "exit") == 0) exit(0);
        if(strcmp(argv[0], "cd") == 0 || strcmp(argv[0], "mycd") == 0) {
            int rv = chdir(argv[1]);
            if(rv == -1) {
                puts("Error, the new directory doesn't exist or is not readable by you :)\n");
            }
            continue;
        }

        pid_t pid;
        pid = fork();
        if(pid == -1) {
            puts("Something wrong happend, it's likely not your fault, run the shell again please.");
            exit(1);
        }
        else if(pid == 0) { // child
            // might need to change it to look in the current direcotry after finding nothing in the environment
            execvp(argv[0], argv);
            puts("Didn't find it in the standard environment. Checking the current directory...\n");
            
            char *newarg;
            strcat(newarg, "./");
            strcat(newarg, argv[0]);
            free(argv[0]);
            argv[0] = newarg;
            execvp(argv[0], argv);
        }
        else { // parent
            int *status;
            wait(status);
            // printf("\nTerminated: ");
            // if(WIFEXITED(*status)) puts("Normally");
            // else if(WIFSIGNALED(*status)) puts("Signaled");
            // else if(WCOREDUMP(*status)) puts("Core dumped");
            // else puts("Stopped");
            printf("\nExit status: %d\n\n", *status);
        }
    }
}
