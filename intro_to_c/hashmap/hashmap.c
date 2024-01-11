#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define STARTING_CAPACITY 80
#define MAX_KEY_SIZE 50
#define DATA_EXISTS 1
#define TOMBSTONE 2 // for deletion

typedef struct {
  int flag; // DATA_EXISTS or TOMBSTONE
  char* key;
  uint32_t hash;
} Key;

typedef struct {
  Key** keys;
  void** values;
  uint32_t capacity;
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
  Hashmap* hashmap = malloc(sizeof(Hashmap));;
  hashmap->capacity = STARTING_CAPACITY;
  hashmap->keys = malloc(hashmap->capacity * sizeof(Key*));
  hashmap->values = malloc(hashmap->capacity * sizeof(void*));

  return hashmap;
};

void Hashmap_set(Hashmap* h, char* key, void* value) {
  unsigned int raw_hash = hash_djb2(key);
  uint32_t i = hash_to_index(raw_hash, h->capacity);
  uint32_t initial_index = i;
  uint32_t initial_index_seen = 0;
  while (h->keys[i] != NULL) {
    // Handle updates
    if (h->keys[i]->hash == raw_hash) {
      break;
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
  item->key = key;
  item->hash = raw_hash;

  h->keys[i] = item;
  h->values[i] = value;
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
      break;
    }    
    
    if ((seen_initial > 0) && i == initial_idx) {
      printf("Attempting to delete non-existent key");
      return;
    }

    seen_initial = 1;
    
    // Linear probing
    i = (i + 1) % h->capacity;    
  }

  if (h->keys[i] != NULL) {
    // Mark item as deleted
    h->keys[i]->flag = TOMBSTONE;
  }
  return;

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
  // using the same key should override the previous value
  int c = 20;
  Hashmap_set(h, "item a", &c);
  assert(Hashmap_get(h, "item a") == &c);   
  

  // basic delete functionality
  Hashmap_delete(h, "item a");
  Hashmap_delete(h, "nonexistent");
  Hashmap_delete(h, "item b");
  assert(Hashmap_get(h, "item a") == NULL);   
  assert(Hashmap_get(h, "item b") == NULL);   
    
  // handle collisions correctly
  // note: this doesn't necessarily test expansion
  int i, n = 50, ns[n];
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
