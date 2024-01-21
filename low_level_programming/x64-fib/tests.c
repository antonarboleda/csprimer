#include <assert.h>
#include <stdio.h>

extern int fib(int n);
extern int rfact(int n);


int main(void) {
  assert(fib(0) == 0);
  assert(fib(1) == 1);
  assert(fib(2) == 1); 
  assert(fib(3) == 2);
  assert(fib(10) == 55);
  assert(fib(12) == 144);
  assert(rfact(3) == 6);
  assert(rfact(7) == 5040);
  assert(rfact(6) == 720);  
  printf("OK\n");
}
