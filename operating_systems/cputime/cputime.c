/*
 * A program to measure real, user and system time given a code block. Also prints out the
 * CPU ID and process ID. Developed on linux 5.15.0-92-generic
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sched.h>
#include <sys/times.h>
#include <stdint.h>

#define SLEEP_SEC 3
#define NUM_MULS 100000000
#define NUM_MALLOCS 100000
#define MALLOC_SIZE 1000

struct profile_times {
    uintmax_t start;	/* starting tick value */
    struct tms st_times;
    struct tms en_times;
};

void profile_start(struct profile_times *t) {
    t->start = times(&t->st_times);    
}

void profile_log(struct profile_times *t) {
    unsigned long freq = sysconf(_SC_CLK_TCK); /* clock frequency */
    uintmax_t end = times(&t->en_times);
    int cpu = sched_getcpu();
    pid_t pid = getpid();
    printf(
        "[pid: %d, cpu: %d], real: %5.3f seconds, user: %5.3f, sys: %5.3f\n",
        pid,
        cpu, 
        (double)(end-t->start)/freq,
        (double) (t->en_times.tms_utime - t->st_times.tms_utime) / freq,
        (double) (t->en_times.tms_stime - t->st_times.tms_stime) / freq
    );
}      

int main(int argc, char *argv[]) {
  struct profile_times t;
  float x = 1.0;
  
  printf("%d floating point muls\n", NUM_MULS);
  profile_start(&t);
  for (int i = 0; i < NUM_MULS; i++)
    x *= 1.1;
  profile_log(&t);

  profile_start(&t);
  void *p;
  printf("%d mallocs of size %d\n", NUM_MALLOCS, MALLOC_SIZE);
  for (int i = 0; i < NUM_MALLOCS; i++)
    p = malloc(MALLOC_SIZE);
  profile_log(&t);

  printf("sleeping for %d secs\n", SLEEP_SEC);
  profile_start(&t);
  sleep(SLEEP_SEC);
  profile_log(&t);
  printf("OK\n");
  return 0;
}
