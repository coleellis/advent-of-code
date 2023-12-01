#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // open the file
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // prep the read
  char *line = NULL;
  size_t len = 0;

  // read
  size_t count = 0;
  while (getline(&line, &len, fp) != -1) {
    size_t i = 0;
    size_t j = 0;

    // populate left-left
    char *left_left = malloc(len * sizeof(char));
    while (line[i] != '-') {
      left_left[j] = line[i];
      ++i;
      ++j;
    }
    int l_first = atoi(left_left);
    j = 0;
    ++i;

    // populate left-left
    char *left_right = malloc(len * sizeof(char));
    while (line[i] != ',') {
      left_right[j] = line[i];
      ++i;
      ++j;
    }
    int l_second = atoi(left_right);
    j = 0;
    ++i;

    // populate left-left
    char *right_left = malloc(len * sizeof(char));
    while (line[i] != '-') {
      right_left[j] = line[i];
      ++i;
      ++j;
    }
    int r_first = atoi(right_left);
    j = 0;
    ++i;

    // populate left-left
    char *right_right = malloc(len * sizeof(char));
    while (line[i] != '\n') {
      right_right[j] = line[i];
      ++i;
      ++j;
    }
    int r_second = atoi(right_right);

    // get our count
    int rl_shift = r_second >= l_first && r_second <= l_second;
    int rr_shift = r_first <= l_second && r_first >= l_first;
    int lr_shift = l_first <= r_second && l_first >= r_first;
    int ll_shift = l_second >= r_first && l_second <= r_second;

    if (rl_shift || rr_shift || lr_shift || ll_shift)
      ++count;
  }

  printf("%zd\n", count);

  return 0;
}