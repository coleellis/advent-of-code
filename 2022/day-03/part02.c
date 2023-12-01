#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) { return *(char *)a < *(char *)b; }

int main(void) {
  // open the file
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // prep the input
  char *first = NULL;
  char *second = NULL;
  char *third = NULL;
  ssize_t f_read, s_read, t_read;
  size_t len = 0;

  // get the input
  char *items = malloc(1000 * sizeof(char));
  uint16_t count = 0;
  while ((f_read = getline(&first, &len, fp)) != -1) {
    // get the second and third lines
    s_read = getline(&second, &len, fp);
    t_read = getline(&third, &len, fp);

    // check for commonality
    for (uint16_t i = 0; i < f_read - 1; ++i) {
      for (uint16_t j = 0; j < s_read - 1; ++j) {
        for (uint16_t k = 0; k < t_read - 1; ++k) {
          if (first[i] == second[j] && first[i] == third[k]) {
            items[count] = first[i];
          }
        }
      }
    }

    // inc counter
    ++count;
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

  free(items);

  return 0;
}