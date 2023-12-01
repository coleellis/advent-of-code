#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  size_t len;
  ssize_t read;
  char *line = NULL;

  size_t cycles = 1; // cycle counter
  int keys[6] = {0}; // holds strengths at indices
  int X = 1;         // register value of X
  while ((read = getline(&line, &len, fp)) != -1) {
    // check cycles
    ++cycles;
    if (cycles == 20 || cycles == 60 || cycles == 100 || cycles == 140 ||
        cycles == 180 || cycles == 220)
      keys[(cycles - 20) / 40] = (cycles * X);

    if (line[0] == 'n')
      continue;

    // finally finish operation
    char *toInt = malloc(4 * sizeof(char));
    for (int i = 5; line[i] != '\n'; ++i)
      toInt[i - 5] = line[i];
    X += atoi(toInt);

    // let another cycle go by
    ++cycles;
    if (cycles == 20 || cycles == 60 || cycles == 100 || cycles == 140 ||
        cycles == 180 || cycles == 220)
      keys[(cycles - 20) / 40] = (cycles * X);
  }

  printf("%d %d %d %d %d %d = %d\n", keys[0], keys[1], keys[2], keys[3],
         keys[4], keys[5],
         keys[0] + keys[1] + keys[2] + keys[3] + keys[4] + keys[5]);

  fclose(fp);
}