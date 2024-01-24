#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool ispangram(char *s) {
  uint32_t bitset = 0;
  char c; 
  int mask = 0x07fffffe;

  do {
    c = *s;

    if (c < '@') { // ignore first 64 chars in ascii table
      continue;
    }
    bitset |= 1 << (c & 0x1f);
  } while (*s++ != '\0'); 

  return (bitset & mask) == mask;
}

int main() {
  size_t len;
  ssize_t read;
  char *line = NULL;
  while ((read = getline(&line, &len, stdin)) != -1) {
    if (ispangram(line))
      printf("%s", line);
  }

  if (ferror(stdin))
    fprintf(stderr, "Error reading from stdin");

  free(line);
  fprintf(stderr, "ok\n");
  return 0;
}
