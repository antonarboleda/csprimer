/*
 * Goals
 * 1. Research needed syscalls / library functions
 *    - we'll need to make sure it works on the macos machine
 * 2. Print PID - how does ps get a process ID? using getpid(2)
 * 3. Determine elapsed "real" (wall clock) time 
 *  - gettimeofday(&time, NULL) (2)
 * 4. Determine elapsed time on CPU (both user and system)
 * 
 * 5. Refactoring/cleanup, maybe cpuid
 */
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SLEEP_SEC 3
#define NUM_MULS 100000000
#define NUM_MALLOCS 100000
#define MALLOC_SIZE 1000

// TODO define this struct
struct profile_times {
  struct timeval start; /* start time */
  struct timeval end; /* end time */
  unsigned long e_usec;	/* elapsed microseconds */

};

// TODO populate the given struct with starting information
void profile_start(struct profile_times *t) {
  gettimeofday(&t->start, 0);
}

// TODO given starting information, compute and log differences to now
void profile_log(struct profile_times *t) {
  // reads and stores input
  &t->e_usec = ((&t->end.tv_sec * 1000000) + &t->end.tv_usec) - ((&t->start.tv_sec * 1000000) + &t->start.tv_usec);
}

int main(int argc, char *argv[]) {
  struct profile_times t;

  // TODO profile doing a bunch of floating point muls
  float x = 1.0;
  profile_start(&t);
  for (int i = 0; i < NUM_MULS; i++)
    x *= 1.1;
  profile_log(&t);

  // TODO profile doing a bunch of mallocs
  profile_start(&t);
  void *p;
  for (int i = 0; i < NUM_MALLOCS; i++)
    p = malloc(MALLOC_SIZE);
  profile_log(&t);

  // TODO profile sleeping
  profile_start(&t);
  sleep(SLEEP_SEC);
  profile_log(&t);
}
