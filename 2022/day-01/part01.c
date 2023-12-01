#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  // open the file
  fp = fopen("input.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // initialize array
  int totals[1000] = {0};
  uint16_t i = 0;
  uint32_t sum = 0;

  // read the file till no more lines
  while ((read = getline(&line, &len, fp)) != -1) {
    if (read == 1) { // if blank line, store total
      totals[i] = sum;
      ++i;
      sum = 0;
    } else { // else, add to total
      sum += atoi(line);
    }
  }

  // get the max
  uint32_t max = 0;
  for (uint32_t i = 0; i < 1000; ++i) {
    if (totals[i] > max)
      max = totals[i];
  }

  // print the max
  printf("%d\n", max);

  fclose(fp);
  if (line)
    free(line);
  exit(EXIT_SUCCESS);
}