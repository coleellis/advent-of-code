#include <stdio.h>
#include <stdlib.h>

enum Visible { NOT_VISIBLE, VISIBLE };

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

  // allocate a visibility grid
  int **vis = malloc(rows * sizeof(int *));
  for (size_t i = 0; i < rows; ++i) {
    vis[i] = malloc(cols * sizeof(int));
    for (size_t j = 0; j < cols; ++j)
      vis[i][j] = NOT_VISIBLE;
  }

  // run the rows
  for (size_t i = 0; i < rows; ++i) {
    size_t tallest = grid[i][0];

    vis[i][0] = VISIBLE;
    vis[i][cols - 1] = VISIBLE;

    // run the rows forward
    for (size_t j = 0; j < cols; ++j) {
      if (grid[i][j] > tallest)
        vis[i][j] = VISIBLE;
      tallest = (grid[i][j] > tallest) ? grid[i][j] : tallest;
    }

    // run the rows in reverse
    tallest = grid[i][rows - 1];
    for (int j = cols - 1; j >= 0; --j) {
      if (grid[i][j] > tallest)
        vis[i][j] = VISIBLE;
      tallest = (grid[i][j] > tallest) ? grid[i][j] : tallest;
    }
  }

  // run the columns
  for (size_t j = 0; j < cols; ++j) {
    size_t tallest = grid[0][j];

    vis[0][j] = VISIBLE;
    vis[rows - 1][j] = VISIBLE;

    // run the rows forward
    for (size_t i = 0; i < cols; ++i) {
      if (grid[i][j] > tallest)
        vis[i][j] = VISIBLE;
      tallest = (grid[i][j] > tallest) ? grid[i][j] : tallest;
    }

    // run the rows in reverse
    tallest = grid[cols - 1][0];
    for (int i = rows - 1; i >= 0; --i) {
      if (grid[i][j] > tallest)
        vis[i][j] = VISIBLE;
      tallest = (grid[i][j] > tallest) ? grid[i][j] : tallest;
    }
  }

  // count the number of visible
  size_t num_visible = 0;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      if (vis[i][j] == VISIBLE)
        ++num_visible;
    }
  }
  printf("%zd\n", num_visible);
  return 0;
}