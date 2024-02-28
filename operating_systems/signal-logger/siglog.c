#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <sys/types.h>
#include <setjmp.h>

#define INTERVAL_MS 500

volatile sig_atomic_t handled = 0;
sigjmp_buf jmp_env_seg;
sigjmp_buf jmp_env_bus;

void handle(int sig) {
    handled |= (1 << sig);
    printf("Caught %d: %s (%d total)\n", sig, strsignal(sig), __builtin_popcount(handled));
    if (sig == SIGILL) {
        printf("caught SIGILL\n");
    }

    if (sig == SIGSEGV) {
	siglongjmp(jmp_env_seg, 1);
    }	
    if (sig == SIGBUS) {
	siglongjmp(jmp_env_bus, 1);
    }
}

// cause a segfault!
void sigsegv() {
    char* str = "Hello World";
    if (sigsetjmp(jmp_env_seg, 1) == 0) {
        memcpy(str, "Copy\0", 5);
    }
}

void sigxfsz() {
    // Setting file size limit
    struct rlimit rlim;
    rlim.rlim_cur = 1024; // Set the soft limit to 1024 bytes
    rlim.rlim_max = 2048; // Set the hard limit to 2048 bytes
    if (setrlimit(RLIMIT_FSIZE, &rlim) != 0) {
        perror("Error setting file size limit");
        exit(1);
    }
    // Creating a file
    int fd = open("out.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error creating file");
        exit(1);
    }
    // Writing data to the file until the file size limit is exceeded
    char data = 'A';
    while (1) {
        if (write(fd, &data, sizeof(data)) == -1) {
            perror("Error writing to file");
            break;
        }
    }
    // Closing the file
    close(fd);
}

int main(int argc, char* argv[]) {
    // Register all valid signals
    for (int i = 1; i < NSIG; i++) {
        signal(i, handle);
    }
    if (0 == fork()) {
        exit(0);
    }
	
	sigxfsz(); // Call the function that may cause a file size limit exceeded err
    sigsegv(); // Call the function that may cause a segmentation fault
    
    // sig bus error
    int *num;
    if (sigsetjmp(jmp_env_bus, 1) == 0) {
        *num = 7;
    }


    int n = 9 / 0;
    struct rlimit rlim;
    rlim.rlim_cur = 0.01; // Set the CPU time limit (in seconds)
    rlim.rlim_max = 0.01;
    setrlimit(RLIMIT_CPU, &rlim);
	
	// SIGALRM
    alarm(1);
    if (setitimer(ITIMER_VIRTUAL, &it_val, NULL) == -1) {
        perror("error calling setitimer()");
 		exit(1);
    }    
    // Spin forever
    for (;;) {
        sleep(1);
    }
    return 0;
}
