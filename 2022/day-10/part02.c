#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  size_t len;
  ssize_t read;
  char *line = NULL;

  size_t cycles = 1;      // cycle counter
  int X = 1;              // register value of X
  char lights[240] = {0}; // array of lights
  while ((read = getline(&line, &len, fp)) != -1) {
    int position = (cycles - 1) % 40;
    // check cycles
    if (abs(X - position) <= 1)
      lights[cycles - 1] = '#';
    else
      lights[cycles - 1] = '.';
    ++cycles;
    ++position;

    if (line[0] == 'n')
      continue;

    // let another cycle go by
    if (abs(X - position) <= 1)
      lights[cycles - 1] = '#';
    else
      lights[cycles - 1] = '.';
    ++cycles;
    ++position;

    // finally finish operation
    char *toInt = malloc(4 * sizeof(char));
    for (int i = 5; line[i] != '\n'; ++i)
      toInt[i - 5] = line[i];
    X += atoi(toInt);
  }

  printf("\n");
  for (size_t i = 0; i < 6; ++i) {
    for (size_t j = 0; j < 40; ++j) {
      printf("%c", lights[40 * i + j]);
    }
    printf("\n");
  }

  fclose(fp);
}