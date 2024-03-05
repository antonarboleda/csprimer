#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS_SIZE 256
// With '\n' included in the separator string, strtok() will tokenize this 
// input into "ls", "-l", and "pwd" as separate tokens. Without including 
// '\n', the program would only tokenize "ls", "-l" as the first command 
// and never tokenize "pwd" because it doesn't encounter a space after it.
#define SEP " \t\n" 


volatile pid_t childpid = 0;

void handle(int sig) {
    if (!childpid) return;
    // send SIGINT to child process
    if (kill(childpid, SIGINT) < 0) {
        perror("Error sending sigint to child");
    }; 
}

int main() {
    char user_input[MAX_INPUT_SIZE];
    char* argv[MAX_ARGS_SIZE];
    
    // register signals
    signal(SIGINT, handle);

    while (1) {
        int i = 0;
        printf("$ ");
        fgets(user_input, sizeof(user_input), stdin);
        
        // tokenize
        argv[i] = strtok(user_input, SEP);
        
	    while (argv[i] != NULL) {
		    argv[++i] = strtok(NULL, SEP);
	    } 
        
        // fork 
        int status;
        if ((childpid = fork()) < 0) {
            printf("failed to create child process");
            exit(1);
        }
        // child process
        if (childpid == 0) { 
            execvp(argv[0], argv);
        } else { 
            // parent process
            waitpid(childpid, &status, 0);
            childpid = 0;
        }
    }
}
