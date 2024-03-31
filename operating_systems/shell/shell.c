#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS_SIZE 256
#define MAX_COMMAND_SIZE 128

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
        
        // tokenize by pipe char
        commands[cmd_i] = strtok(user_input, PIPE);
        while (commands[cmd_i] != NULL) {
            commands[++cmd_i] = strtok(NULL, PIPE);
        }

        int readfd = STDIN_FILENO;
        for (int i = 0; i < cmd_i; i++) {            
            // fork 
            int status;
            int argv_i = 0;
            int fds[2];
            
            pipe(fds);

            if ((childpid = fork()) < 0) {
                perror("fork failure");
                exit(EXIT_FAILURE);
            }

            // child process
            if (childpid == 0) {
                argv[argv_i] = strtok(commands[i], SEP);
                while (argv[argv_i] != NULL)
                    argv[++argv_i] = strtok(NULL, SEP);   

                if (i < cmd_i - 1)
                    dup2(fds[1], STDOUT_FILENO);
                    close(fds[1]);
                    close(fds[0]);
                printf("readfd: %d\n", readfd);
                dup2(readfd, STDIN_FILENO);
                if (execvp(argv[0], argv) < 0) {
                    perror("exec error");
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_FAILURE);
            }
            readfd = fds[0];
            // parent never needs a copy of the write end
            // only needs to save the read
            if (i != cmd_i - 1)
                close(fds[1]);
        }

        while ((wpid = wait(&status)) > 0);
    }
}
