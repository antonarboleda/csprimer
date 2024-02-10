#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
// stack frame benchmark = 261964
void f(int depth, long int bottom) {
    if (depth % 1000 == 0) 
        printf("frame %d %ld (%p) %ld\n", depth, bottom - (long)&depth, &depth, bottom);
    f(depth + 1, bottom);
}

void start() {
    int depth = 0;
    f(depth, (long)&depth);
}

int main () {
    struct rlimit new_limit;
    // new_limit.rlim_max = 1000;
    // new_limit.rlim_cur = 1000;
    getrlimit(RLIMIT_STACK, &new_limit);
    printf("limit is %lu soft limit is %lu\n", new_limit.rlim_max, new_limit.rlim_cur);
    new_limit.rlim_cur = new_limit.rlim_max;    
    setrlimit(RLIMIT_STACK, &new_limit);
    
    getrlimit(RLIMIT_STACK, &new_limit);
    printf("limit is %lu soft limit is %lu\n", new_limit.rlim_max, new_limit.rlim_cur);
    start();
    printf("OK\n");
}
