#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>

void sigxfsz_handler(int signum) {
    printf("Caught SIGXFSZ: File Size Limit Exceeded\n");
    // You can handle the SIGXFSZ here or perform any necessary cleanup.
    // For simplicity, we just print a message.
}

int main() {
    // Registering SIGXFSZ handler
    signal(SIGXFSZ, sigxfsz_handler);

    // Setting file size limit
    struct rlimit rlim;
    rlim.rlim_cur = 1; // Set the soft limit to 1024 bytes
    rlim.rlim_max = 1; // Set the hard limit to 2048 bytes
    if (setrlimit(RLIMIT_FSIZE, &rlim) != 0) {
        perror("Error setting file size limit");
        return 1;
    }

    // Creating a file
    int fd = open("out.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error creating file");
        return 1;
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

    return 0;
}
