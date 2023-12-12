#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define STARTING_CAPACITY 8

// Use an underlying C array
// Accommodate any data type - integers, floats
// 1. Define the struct [x]
// 2. Implement new, size and free [x]
// 3. Push pop set and get without resizing [x]
// 4. Resize [x] - double the array size if it is about to exceed the capacity
typedef struct DA {
  void** items; // the starting location of a pointer to anything
  int size; // number of items in the array
  int capacity; 
} DA;


DA* DA_new (void) {
  // TODO allocate and return a new dynamic array
  DA* da = malloc(sizeof(DA));
  da->size = 0;
  da->capacity = STARTING_CAPACITY;
  da->items = malloc(da->capacity * sizeof(void *));
  return da;
}

int DA_size(DA *da) {
  return da->size;
}

void DA_push (DA* da, void* x) {
  if (da->size == da->capacity) 
  {
    da->capacity *= 2;
    da->items = realloc(da->items, da->capacity * sizeof(void *));
  }
  da->items[da->size] = x;
  da->size++;
}

void *DA_pop(DA *da) {
  if (da->size == 0) {
    return NULL;
  }

  return da->items[--da->size];
}

void DA_set(DA *da, void *x, int i) {
  if (i < 0 || i > da->size) return;

  da->items[i] = x;
}

void *DA_get(DA *da, int i) {
  assert(i < da->size && i >= 0);
  return da->items[i];
}


void DA_free(DA *da) {
  free(da->items);
  free(da);
}

int main() {
    DA* da = DA_new();

    assert(DA_size(da) == 0);

    int x = 5;
    float y = 12.4;
    DA_push(da, &x);
    DA_push(da, &y);
    assert(DA_size(da) == 2);
    assert(DA_pop(da) == &y);
    assert(DA_size(da) == 1);

    assert(DA_pop(da) == &x);
    assert(DA_size(da) == 0);
    assert(DA_pop(da) == NULL);

    // basic set/get test
    DA_push(da, &x);
    DA_set(da, &y, 0);
    assert(DA_get(da, 0) == &y);
    DA_pop(da);
    assert(DA_size(da) == 0);

    // expansion test
    DA *da2 = DA_new(); // use another DA to show it doesn't get overriden
    DA_push(da2, &x);
    int i, n = 100 * STARTING_CAPACITY, arr[n];
    for (i = 0; i < n; i++) {
      arr[i] = i;
      DA_push(da, &arr[i]);
    }
    assert(DA_size(da) == n);
    for (i = 0; i < n; i++) {
      assert(DA_get(da, i) == &arr[i]);
    }
    for (; n; n--)
      DA_pop(da);
    assert(DA_size(da) == 0);
    assert(DA_pop(da2) == &x); // this will fail if da doesn't expand

    DA_free(da);
    DA_free(da2);
    printf("OK\n");
}