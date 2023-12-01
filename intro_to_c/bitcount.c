#include <assert.h>
#include <stdio.h>
/* 
    Write a function which given an integer returns 
    the number of "on" bits
*/
// Must be an unsigned int, if you use a 
// signed int, the right shift will add a 1 at the beginning
// first bit when right shifting
int bitcount(unsigned n) {
    int count = 0;
    while (n) {
        count += n & 0x01; 
        /* if last bit & 1 is on. Can also do n % 1*/
        /* shift by 1 */
        n >>= 1;
    }
    return count;
}

// Use the fact that x &= (x-1) deletes the rightmost 1 bit to write a faster 
// version. 2.9 p.51 in K&R The C Programming Language
int bitcount_optimized(unsigned n) {
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count;
}

int main() {
    assert(bitcount(0) == 0);
    assert(bitcount(1) == 1);
    assert(bitcount(7) == 3);
    assert(bitcount(8) == 1);
    assert(bitcount(-8) == 1);
    assert(bitcount(32) == 1);
    assert(bitcount(0xffffffff) == 32);
    printf("OK\n");
}