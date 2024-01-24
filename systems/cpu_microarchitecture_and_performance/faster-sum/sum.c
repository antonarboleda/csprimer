// /*
//  * Ideas after watching the video
//  * 1. Use a SIMD register to load 16 32 bit integers into a single . SIMD 
//  *  (single instruction multiple data) register
//  *  - https://www.agner.org/optimize/optimizing_cpp.pdf pg. 115
//  * 2. Utilize multiple Execution units to add nums[i] to total. Ordering doesn't
//  * really matter here. We can utilize out of order execution
//  * 3. We are loading a value nums[i] from memory at each iteration. We are loading
//  * a value from *nums[i]. Can we do this out of order?
//  * 
//  * Test1: Use 4 accumulators as in 5.9.1 in CSApp. 
//  * result - Overall timing and CPU timing increased nearly 1.5 to 2x from
//  * the original solution.
//  * CPU Caches:
//   L1 Data 64 KiB
//   L1 Instruction 128 KiB
//   L2 Unified 4096 KiB (x10)
// Load Average: 3.86, 4.19, 4.41
// ---------------------------------------------------------
// Benchmark               Time             CPU   Iterations
// ---------------------------------------------------------
// BM_Sum/4096          1.23 us         1.22 us       574401
// BM_Sum/16384         4.90 us         4.89 us       143983
// BM_Sum/65536         19.6 us         19.6 us        35640
// BM_Sum/262144        77.4 us         77.1 us         9122
// BM_Sum/1048576        330 us          320 us         2204

// Load Average: 4.23, 4.30, 4.45
// ---------------------------------------------------------
// Benchmark               Time             CPU   Iterations
// ---------------------------------------------------------
// BM_Sum/4096         0.696 us        0.692 us      1028066
// BM_Sum/16384         2.74 us         2.73 us       255534
// BM_Sum/65536         13.7 us         13.7 us        51496
// BM_Sum/262144        55.2 us         54.9 us        13002
// BM_Sum/1048576        224 us          223 us         3132
//  * 
//  */

#include <arm_neon.h>
#include <stdio.h>

// declare fn as
int sum_rollup(int* __restrict nums, int n) {
  int total0 = 0;
  int total1 = 0;
  int total2 = 0;
  int total3 = 0;
  for (int i = 0; i < n; i += 4) {
    total0 += nums[i];
    total1 += nums[i+1];
    total2 += nums[i+2];
    total3 += nums[i+3];

  }
  return total0 + total1 + total2 + total3;
}

int sum_intrinsic(int* nums, int n) {
    int32_t result = 0;

    // Process the array in chunks of 4 elements
    for (int i = 0; i < n; i += 4) {
        int32x4_t v_data = vld1q_s32(nums + i);
        result += vaddvq_s32(v_data);
    }

    return result;
}


int sum(int *nums, int n) {
  int total = 0;
  for (int i = 0; i < n; i++) {
    total += nums[i];
  }
  return total;
}
