#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#define STARTING_CAPACITY 80
#define MAX_KEY_SIZE 50
#define DATA_EXISTS 1
#define TOMBSTONE 2 // for deletion

typedef struct {
  int flag; // DATA_EXISTS or TOMBSTONE
  uint32_t hash;
} Key;

typedef struct {
  Key** keys;
  void** values;
  uint32_t capacity;
  float load_factor; 
  uint32_t threshold; // the threshold of # of items before we resizing occurs
  uint32_t current_size;
} Hashmap;

// Implements the multiplication hash found in 
// https://sites.cs.queensu.ca/courses/cisc235/Record/20200312b%20-%20Choosing%20a%20Hashing%20Function.pdf
uint32_t multiplication_hash(unsigned int key, uint32_t capacity) {
  double v = .61803398875;
  // convert to double, float conversion loses precision for large values
  // causing this hashing method to break
  double x = v * key;
  // get the fractional i.e. decimal value of the double value.
  double fractional = x - (int)x;
  return floor(capacity * fractional);
}

unsigned int hash_djb2(char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))        // *str++ is going to the next address in memory, where the next char in the string is stored
    {
        if (isupper(c))
        {
            c = c + 32;
        }

        hash = ((hash << 5) + hash) + c; // hash * 33 + c   // hash << 5 = hash * 2^5
    }
    
    return hash & 0x7FFFFFFF;
}

uint32_t hash_to_index(unsigned int hash, uint32_t capacity) {
   uint32_t index = multiplication_hash(hash, capacity);
  return index % capacity;
}

Hashmap* Hashmap_new() {
  Hashmap* h = malloc(sizeof(h));;
  h->capacity = STARTING_CAPACITY;
  h->keys = malloc(h->capacity * sizeof(Key*));
  h->values = malloc(h->capacity * sizeof(void*));
  h->load_factor = (float).45;
  h->threshold = h->capacity * h->load_factor;
  h->current_size = 0;

  return h;
};

void _Hashmap_insert(Hashmap* h, unsigned int raw_hash, char* value) {
  uint32_t i = hash_to_index(raw_hash, h->capacity);
  uint32_t initial_index = i;
  uint32_t initial_index_seen = 0;
  while (h->keys[i] != NULL) {
    // Handle updates
    if (h->keys[i]->hash == raw_hash) {
      h->values[i] = value;
      return;
    }
    // At this point, we've gone through full cycle through the 
    if (i == initial_index && initial_index_seen) {
      printf("Hash table is full!\n");
      return;
    }

    i = (i + 1) % h->capacity;
    initial_index_seen |= 0x1;
  }

  Key* item = malloc(sizeof(Key));
  item->flag = DATA_EXISTS;
  item->hash = raw_hash;

  h->keys[i] = item;
  h->values[i] = value;
  h->current_size++;
}

void* Hashmap_get(Hashmap* h, char* key) {
  unsigned int raw_hash = hash_djb2(key);
  uint32_t i = hash_to_index(raw_hash, h->capacity);  
  uint32_t initial_idx = i; 
  uint8_t seen_initial = 0;
  
  while (h->keys[i] != NULL) {
    if (h->keys[i]->hash == raw_hash) {
      // Deleted tombstone is on
      if (h->keys[i]->flag == TOMBSTONE) {
        return NULL;
      } 
      return h->values[i];
    }

    if ((seen_initial > 0) && i == initial_idx) {
      return NULL;
    }
    seen_initial = 1;
    
    // Linear probing
    i = (i + 1) % h->capacity;
  }  
  return NULL;
}

void Hashmap_delete(Hashmap* h, char* key) {
  unsigned int raw_hash = hash_djb2(key);
  uint32_t i = hash_to_index(raw_hash, h->capacity);  
  uint32_t initial_idx = i; 
  uint8_t seen_initial = 0;

  while (h->keys[i] != NULL) {
    if (h->keys[i]->hash == raw_hash) {
      h->keys[i]->flag = TOMBSTONE;
      return;
    }    
    
    if ((seen_initial > 0) && i == initial_idx) {
      printf("Attempting to delete non-existent key");
      return;
    }

    seen_initial = 1;
    
    // Linear probing
    i = (i + 1) % h->capacity;    
  }
  return;
}

void _Hashmap_resize_table(Hashmap* h) {
  // Swap old keys and values into new mem locations
  Key** tmp_keys = malloc(h->capacity * sizeof(Key*));
  void** tmp_values = malloc(h->capacity * sizeof(void*));  
  memcpy(tmp_keys, h->keys, h->capacity * sizeof(Key*));
  memcpy(tmp_values, h->values, h->capacity * sizeof(void*));
  free(h->keys);
  free(h->values);
  h->capacity *= 2;
  h->threshold = h->capacity * h->load_factor;
  h->current_size = 0;
  // Reassign new key and value pointers
  h->keys =  malloc(h->capacity * (sizeof(Key)));
  h->values = malloc(h->capacity * (sizeof(void*)));
  for (int i = 0; i < h->capacity; i++) {
    if (tmp_values[i] != NULL && tmp_keys[i] != NULL && tmp_keys[i]->flag == DATA_EXISTS) {
      _Hashmap_insert(h, tmp_keys[i]->hash, tmp_values[i]);
    }
  }  
}

void Hashmap_set(Hashmap* h, char* key, void* value) {
  unsigned int raw_hash = hash_djb2(key);
  if (h->current_size >= h->threshold) {
    printf("Resizing event - current size %d is above threshold: %d\n", h->current_size, h->threshold);
    _Hashmap_resize_table(h);
  }
  _Hashmap_insert(h, raw_hash, value);
}

void Hashmap_free(Hashmap *h) {
  free(h->keys);
  free(h->values);
  free(h);
}

int main() {
  Hashmap *h = Hashmap_new();
  // basic get/set functionality
  int a = 5;
  float b = 7.2;
  Hashmap_set(h, "item a", &a);
  Hashmap_set(h, "item b", &b);

  assert(Hashmap_get(h, "item a") == &a);
  assert(Hashmap_get(h, "item b") == &b);
  assert(Hashmap_get(h, "non existent") == NULL);   
  uint32_t expected_size = 2;
  assert(h->current_size == expected_size);
  // using the same key should override the previous value
  int c = 20;
  Hashmap_set(h, "item a", &c);
  assert(Hashmap_get(h, "item a") == &c);   
  // size shouldn't increase if we update a value
  assert(h->current_size == expected_size);

  // basic delete functionality
  Hashmap_delete(h, "item a");
  Hashmap_delete(h, "nonexistent");
  Hashmap_delete(h, "item b");
  assert(Hashmap_get(h, "item a") == NULL);   
  assert(Hashmap_get(h, "item b") == NULL);   

  // handle collisions and expansion correctly
  int i, n = 1000, ns[n];
  char key[MAX_KEY_SIZE];
  for (i = 0; i < n; i++) {
    ns[i] = i;
    sprintf(key, "item %d", i);
    Hashmap_set(h, key, &ns[i]);
  }  

  for (i = 0; i < n; i++) {
    sprintf(key, "item %d", i);
    assert(Hashmap_get(h, key) == &ns[i]);
  }
  Hashmap_free(h);
  printf("ok\n");
  exit(0);  
}
