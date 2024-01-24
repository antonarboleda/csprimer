#include <stdio.h>

int main () {
    // int arr[10];
    int num = 1;
    int anotherNum = 12;
    int *ptr;
    ptr = &anotherNum;
    printf("%d\n", *ptr);
}