#include <arm_neon.h>

int main () {
    // Example of SIMD addition using NEON
    int32x4_t a = vdupq_n_s32(1);
    int32x4_t b = vdupq_n_s32(2);
    int32x4_t result = vaddq_s32(a, b);
    return 0;
}