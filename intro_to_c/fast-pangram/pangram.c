#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

bool ispangram(char *s) {
  size_t i = 0;
  size_t j = 0;
  int all_on = 0;
  int bitset = 0;
  size_t len = strlen(s);
  char c;

  for (i = 0; i < len; i++) {
    c = s[i];
    if (isalnum(tolower(c))) {
      // c - 'a' will always be an integer in the range 
      // of 0 to 25
      bitset |= (1 << (c - 'a'));
    }
  }

  return bitset == 0x03ffffff;
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
}
