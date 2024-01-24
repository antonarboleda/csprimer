#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array;
    size_t size = 5;

    // Allocate memory for an array of 5 integers
    array = (int*)malloc(size * sizeof(int));

    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printf("Can use the memory here!\n");
    array[0] = 1;
    printf("the value at array[0] is %d\n", array[0]);

    // Free the allocated memory when done
    free(array);

    return 0;
}
