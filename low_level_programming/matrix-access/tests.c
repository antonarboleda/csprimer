#include <assert.h>
#include <stdio.h>

extern int index(int *matrix, int rows, int cols, int rindex, int cindex);
extern int index_optimized(int *matrix, int rows, int cols, int rindex, int cindex);
extern int index_lea(int *matrix, int rows, int cols, int rindex, int cindex);
int main(void) {

  int matrix0[1][4] = {{1, 2, 3, 4}};
  assert(index((int *)matrix0, 1, 4, 0, 0) == 1);
  assert(index_optimized((int *)matrix0, 1, 4, 0, 0) == 1);
  
  int matrix00[1][4] = {{1, 2, 3, 4}};
  assert(index((int *)matrix00, 1, 4, 0, 1) == 2);  
  assert(index_optimized((int *)matrix00, 1, 4, 0, 1) == 2);  

  int matrix1[1][4] = {{1, 2, 3, 4}};
  assert(index((int *)matrix1, 1, 4, 0, 2) == 3);
  assert(index_optimized((int *)matrix1, 1, 4, 0, 2) == 3);

  int matrix2[4][1] = {{1}, {2}, {3}, {4}};
  assert(index((int *)matrix2, 4, 1, 1, 0) == 2);
  assert(index_optimized((int *)matrix2, 4, 1, 1, 0) == 2);

  int matrix3[2][3] = {{1, 2, 3}, {4, 5, 6}};
  assert(index((int *)matrix3, 2, 3, 1, 2) == 6);
  assert(index_optimized((int *)matrix3, 2, 3, 1, 2) == 6);
  assert(index_lea((int *)matrix3, 2, 3, 1, 2) == 6);

  printf("OK\n");
}
