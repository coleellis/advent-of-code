#include <stdio.h>
#include <stdlib.h>

#define STRING_LEN 14

int compare(const void *a, const void *b) { return *(char *)a - *(char *)b; }

int unique(char *string, size_t length) {
  qsort(string, length, sizeof(char), compare);

  for (size_t i = 0; i < length - 1; ++i) {
    if (string[i] == string[i + 1])
      return 0;
  }
  return 1;
}

int main(void) {
  // open the file
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // prep the input
  char *line = NULL;
  size_t len;
  ssize_t read;

  // read the line
  read = getline(&line, &len, fp);

  // parse the file
  size_t i = 0;
  while (i < read - STRING_LEN) {
    // build a copy of the string
    char *string = malloc(STRING_LEN * sizeof(char));
    for (size_t j = 0; j < STRING_LEN; ++j) {
      string[j] = line[i + j];
    }

    // check uniqueness
    if (unique(string, STRING_LEN)) {
      printf("%zd\n", i + STRING_LEN);
      break;
    }

    // increment otherwise
    ++i;
  }

  return 0;
}