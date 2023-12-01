#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Point {
  int x;
  int y;
} Point_default = {0, 0};

struct Vector {
  int x;
  int y;
} Vector_default = {0, 0};

struct Vector build_vector(struct Point head, struct Point tail) {
  struct Vector *ret = malloc(sizeof(struct Vector));
  ret->x = head.x - tail.x;
  ret->y = head.y - tail.y;
  return *ret;
}

int compare(const void *a, const void *b) {
  struct Point *first = (struct Point *)a;
  struct Point *second = (struct Point *)b;

  if (first->x < second->x)
    return -1;
  else if (first->x > second->x)
    return 1;
  else {
    if (first->y < second->y)
      return -1;
    if (first->y > second->y)
      return 1;
    else
      return 0;
  }
}

int toInt(char first, char second) {
  char *string = malloc(2 * sizeof(char));
  string[0] = first;
  if (string[1] != '\n')
    string[1] = second;
  return atoi(string);
}

int equal(struct Point a, struct Point b) { return (a.x == b.x && a.y == b.y); }

int main(void) {
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  char *line = NULL;
  size_t len = 0;

  // head and tail positions
  struct Point head = Point_default;
  struct Point tail = Point_default;

  // list of points
  struct Point *tail_visits = malloc(20000 * sizeof(struct Point));

  // read the directional changes
  size_t count = 0;
  while (getline(&line, &len, fp) != -1) {
    int times = toInt(line[2], line[3]);
    while (times-- > 0) {
      // adjust the head coordinate
      if (line[0] == 'U')
        ++head.y;
      else if (line[0] == 'D')
        --head.y;
      else if (line[0] == 'L')
        --head.x;
      else if (line[0] == 'R')
        ++head.x;
      else {
        printf("Bad\n");
        exit(EXIT_FAILURE);
      }
      // build the vector
      struct Vector distance = build_vector(head, tail);

      // adjust tail location based on vector
      if (distance.x == 2) {
        ++tail.x;
        if (distance.y == 1)
          ++tail.y;
        if (distance.y == -1)
          --tail.y;
      }
      if (distance.x == -2) {
        --tail.x;
        if (distance.y == 1)
          ++tail.y;
        if (distance.y == -1)
          --tail.y;
      }
      if (distance.y == 2) {
        ++tail.y;
        if (distance.x == 1)
          ++tail.x;
        if (distance.x == -1)
          --tail.x;
      }
      if (distance.y == -2) {
        --tail.y;
        if (distance.x == 1)
          ++tail.x;
        if (distance.x == -1)
          --tail.x;
      }

      // record location in list
      tail_visits[count++] = tail;
    }
    printf("Count: %zd\n  Head: (%d,%d)\n  Tail: (%d,%d)\n  Line: %s", count,
           head.x, head.y, tail.x, tail.y, line);
  }

  // sort the list of points
  qsort(tail_visits, count, sizeof(struct Point), compare);

  // count non-duplicates
  size_t visited = 1;
  for (size_t i = 1; i < count; ++i) {
    if (!equal(tail_visits[i], tail_visits[i - 1])) {
      ++visited;
    }
  }

  printf("Part 1: %zd\n", visited);

  exit(EXIT_SUCCESS);
}