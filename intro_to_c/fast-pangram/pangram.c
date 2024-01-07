#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool ispangram(char *s) {
  size_t i = 0;
  uint32_t bitmap = 0;
  uint8_t A = 0x41;
  uint8_t Z = 0x5a;
  uint8_t a = 0x61;
  uint8_t z = 0x7a;
  
  char c; 
  int mask = 0x03ffffff; // lower order 26 bits are on

  do {
    c = s[i];

    // convert to lower case
    if (s[i] <= Z && s[i] >= A) {
      c = s[i] + 32;
    }

    // At this point, c is alphabetical so we can turn on the 0 to 25th bit
    if (c >= a && c <= z) {
      bitmap |= (1 << (c - a));
    }
    i++;
  } while (s[i] != '\0'); 

  return (bitmap & mask) == mask;
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
