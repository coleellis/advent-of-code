#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // open file
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // initialize reader variables
  char *line = NULL;
  size_t len = 0;

  // read the file
  uint32_t total_score = 0;
  while (getline(&line, &len, fp) != -1) {
    char enemy = line[0];
    char self = line[2];

    total_score += ((int)self - 'W'); // score for self move

    // draw case
    if (((int)enemy - 'A') == ((int)self - 'X')) {
      total_score += 3;
      continue;
    }

    int difference = ((int)self - 'X') - ((int)enemy - 'A');
    if (difference == 1 || difference == -2) {
      total_score += 6;
      continue;
    }

    if (difference == -1 || difference == 2) {
      total_score += 0;
      continue;
    }

    printf("Bad\n");
  }

  // print the total score
  printf("%d\n", total_score);

  return 0;
}