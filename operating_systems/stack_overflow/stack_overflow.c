#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Plan 
 *  Print size of stack - use getrlimiit RLIMIT_STACK
 *  Approximate top of stack
 *  Number of stack frames
 */
int fib(int n, struct rusage* ru) {
    if (n <= 1) return n;

    /* print out the maximum size of the stack*/
    if (n == 4) {
        struct rlimit new_limit;
        new_limit.rlim_cur = 9388608;
        setrlimit(RLIMIT_STACK, &new_limit);
    }
    struct rlimit rlim;
    getrlimit(RLIMIT_STACK, &rlim);
    printf("stack soft limit: %d stack hard limit: %d\n", (unsigned) rlim.rlim_cur, (unsigned) rlim.rlim_max);
    
    size_t stksize;
    pthread_attr_t atr;
    pthread_attr_getstacksize(&atr, &stksize);
    printf("current stack size %d\n", (unsigned) stksize);

    /* print out stack pointer */
    register void *sp asm ("sp");
    printf("%p\n", sp);

    int left = fib(n - 1, ru);
    int right = fib(n - 2, ru);
    return left + right;
}
int main () {
    struct rusage ru;
    int i = 3;
    printf("fib(%d) = %d\n", i, fib(i, &ru));
    return 0;
}
