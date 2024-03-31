#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

/**
 * Fork, setup a pipe, then exec
 * []Proof of concept - implement ls | wc
 * What is the system call to associate ends of a pipe? - dup system call
 */

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS_SIZE 256
#define MAX_COMMAND_SIZE 128
// With '\n' included in the separator string, strtok() will tokenize this 
// input into "ls", "-l", and "pwd" as separate tokens. Without including 
// '\n', the program would only tokenize "ls", "-l" as the first command 
// and never tokenize "pwd" because it doesn't encounter a space after it.
#define SEP " \t\n" 
#define PIPE "|"

volatile pid_t childpid = 0;

void handle_sigint(int sig) {
    if (!childpid) return;
    // send SIGINT to child process
    if (kill(childpid, SIGINT) < 0) {
        perror("Error sending sigint to child");
    }; 
}

int main() {
    char user_input[MAX_INPUT_SIZE];
    char* argv[MAX_ARGS_SIZE];
    char* commands[MAX_COMMAND_SIZE];
    // register signal handlers
    signal(SIGINT, handle_sigint);

    while (1) {
        int cmd_i = 0;
        int wpid = 0;
        int status = 0;
        printf("$$$ ");
        fgets(user_input, sizeof(user_input), stdin);
        commands[cmd_i] = strtok(user_input, PIPE);
        while (commands[cmd_i] != NULL) {
            commands[++cmd_i] = strtok(NULL, PIPE);
        }
        
        for (int i = 0; i < cmd_i; i++) {            
            // fork 
            int status;
            int argv_i = 0;
            if ((childpid = fork()) < 0) {
                perror("fork failure");
                exit(EXIT_FAILURE);
            }

            // child process
            if (childpid == 0) {
                argv[argv_i] = strtok(commands[i], SEP);
                while (argv[argv_i] != NULL)
                    argv[++argv_i] = strtok(NULL, SEP);   
                                 
                execvp(argv[0], argv);
                printf("%s, %s\n", argv[0], argv[1]);
            }
        }

        while ((wpid = wait(&status)) > 0);
    }
}
