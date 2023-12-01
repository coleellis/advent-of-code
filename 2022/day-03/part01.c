#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) { return *(char *)a < *(char *)b; }

int main(void) {
  // open the file
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // prep the input
  char *line = NULL;
  ssize_t read;
  size_t len = 0;

  // get the input
  char *items = malloc(1000 * sizeof(char));
  uint16_t count = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    // populate the left
    char *left = malloc((read - 1) / 2 * sizeof(char));
    for (uint16_t i = 0; i < (read - 1) / 2; ++i)
      left[i] = line[i];

    // populate the right
    char *right = malloc((read - 1) / 2 * sizeof(char));
    for (uint16_t i = 0; i < (read - 1) / 2; ++i)
      right[i] = line[(read - 1) / 2 + i];

    // check for commonality
    for (uint32_t i = 0; i < (read - 1) / 2; ++i) {
      for (uint32_t j = 0; j < (read - 1) / 2; ++j) {
        if (left[i] == right[j])
          items[count] = left[i];
      }
    }

    // inc counter
    ++count;

    // free memory
    if (left)
      free(left);
    if (right)
      free(right);
  }

  // get the total
  uint32_t total = 0;
  for (uint16_t i = 0; i < 1000; ++i) {
    if ((int)items[i] >= 0x61) {
      total += (((int)items[i] - 'a') + 1);
    } else if ((int)items[i] >= 0x41) {
      total += (((int)items[i] - 'A') + 27);
    }
  }

  // print the total
  printf("%d\n", total);

  return 0;
}