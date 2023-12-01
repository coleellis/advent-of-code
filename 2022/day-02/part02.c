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

    total_score += 3 * ((int)self - 'X'); // score for match result

    if (self == 'X') {
      if (enemy == 'B' || enemy == 'C')
        total_score += ((int)enemy - 'A');
      else if (enemy == 'A')
        total_score += 3;
      else
        printf("Bad 1\n");
    } else if (self == 'Y') { // total score is what enemy put
      total_score += (((int)enemy - 'A') + 1);
    } else if (self == 'Z') {
      if (enemy == 'A' || enemy == 'B')
        total_score += (((int)enemy - 'A') + 2);
      else if (enemy == 'C')
        total_score += 1;
      else
        printf("Bad 2\n");
    } else {
      printf("Bad 0\n");
    }
  }

  // print the total score
  printf("%d\n", total_score);

  return 0;
}