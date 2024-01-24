#include <assert.h>
#include <stdio.h>

extern int sum_to_n(int n);
extern int sum_to_n_optimized(int n);
extern int sum_to_n_constant_time(int n);


int main(void) {
  assert(sum_to_n(0) == 0);
  assert(sum_to_n(1) == 1);
  assert(sum_to_n(2) == 3);
  assert(sum_to_n(3) == 6);
  assert(sum_to_n(10) == 55);
  assert(sum_to_n(1000) == 500500);

  assert(sum_to_n_optimized(0) == 0);
  assert(sum_to_n_optimized(1) == 1);
  assert(sum_to_n_optimized(2) == 3);
  assert(sum_to_n_optimized(3) == 6);
  assert(sum_to_n_optimized(10) == 55);
  assert(sum_to_n_optimized(1000) == 500500);

  assert(sum_to_n_constant_time(0) == 0);
  assert(sum_to_n_constant_time(1) == 1);
  assert(sum_to_n_constant_time(2) == 3);
  assert(sum_to_n_constant_time(3) == 6);
  assert(sum_to_n_constant_time(10) == 55);
  assert(sum_to_n_constant_time(1000) == 500500);  
  printf("OK\n");
}
