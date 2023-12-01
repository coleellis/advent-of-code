#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t part01() {
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
  return total_score;
}

uint32_t part02() {
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

  return total_score;
}

int main(void) {
  uint32_t first = part01();
  uint32_t second = part02();

  // print the total score
  printf("flag{%d_%d}\n", first, second);

  return 0;
}