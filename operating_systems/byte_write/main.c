/*
 * Objective: 
 * The objective is to write 1MiB of data, and if any particular byte written 
 * causes the underlying allocated space on disk to change, log the fact that 
 * that happened, as well an the space taken on disk.
 * 
 * The size of the file and the size of the file on disk is not the same thing!
 * 
 * [ ] - Find the allocated space of the file on disk - number of allocated blocks. Each block is 2**12 (4096)
 * [ ] - Find the file size - use stat syscall to get Size attribute
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    char *filename = "out.txt";
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("ERROR\n");
	    return -1;
    }
    int one_mb = 1 << 20;
    struct stat sb;
    int fd = fileno(fp);
    int prev_block_size = -1;    
    for (int i = 0; i < one_mb; i++) {
        // write 1 byte to tmp file
        write(fd, "a", 1);
        fstat(fd, &sb);
	    int new_block_size = sb.st_blocks;
        if (prev_block_size != new_block_size) {
            printf("total size: %ld, block size has changed from %d to %d\n", sb.st_size, prev_block_size, new_block_size);
            prev_block_size = new_block_size;
        }
    }
    fclose(fp);
}
