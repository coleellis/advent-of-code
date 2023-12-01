#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // get file
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  // prep file
  char *line = NULL;
  ssize_t read;
  size_t len;

  // get the size of the file
  size_t rows = 0;
  size_t cols = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    cols = ((read - 1) > cols) ? (read - 1) : cols;
    ++rows;
  }

  // allocate the grid
  char **grid = malloc(rows * sizeof(char *));
  for (size_t i = 0; i < rows; ++i)
    grid[i] = malloc(cols * sizeof(char));

  // read the lines and allocate again
  fp = fopen("input.txt", "r");
  size_t count = 0;
  while (getline(&line, &len, fp) != -1) {
    for (size_t i = 0; i < cols; ++i)
      grid[count][i] = line[i];
    ++count;
  }

  // find the max score
  size_t max_score = 0;
  for (size_t row = 1; row < rows - 1; ++row) {
    for (size_t col = 1; col < cols - 1; ++col) {
      char height = grid[row][col];
      size_t point_score = 1;

      // check the up direction
      size_t up_score = 1;
      for (int i = row - 2; i >= 0; --i) {
        ++up_score;
        if (height <= grid[i][col])
          break;
      }
      point_score *= up_score;

      // check the down direction
      size_t down_score = 1;
      for (int i = row + 2; i < cols; ++i) {
        ++down_score;
        if (height <= grid[i][col])
          break;
      }
      point_score *= down_score;

      // check the left direction
      size_t left_score = 1;
      for (int j = col - 2; j >= 0; --j) {
        ++left_score;
        if (height <= grid[row][j])
          break;
      }
      point_score *= left_score;

      // check the down direction
      size_t right_score = 1;
      for (int j = col + 2; j < cols; ++j) {
        ++right_score;
        if (height <= grid[row][j])
          break;
      }
      point_score *= right_score;

      // check the max
      max_score = (point_score > max_score) ? point_score : max_score;
    }
  }

  printf("%zd\n", max_score);
  return 0;
}