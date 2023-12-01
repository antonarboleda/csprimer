#include <assert.h>
#include <stdio.h>
/* 
    Write a function which given an integer returns 
    the number of "on" bits
*/

int bitcount(int n) {
    int count = 0;
    while (n > 0) {
        /* if last bit & 1 is on. Can also do n % 1*/
        count += n & 0x01; 
        /* shift by 1 */
        n >>= 1;
    }
    return count;
}

int main() {
    assert(bitcount(0) == 0);
    assert(bitcount(1) == 1);
    assert(bitcount(7) == 3);
    assert(bitcount(8) == 1);
    assert(bitcount(32) == 1);
    printf("passed!\n");
}