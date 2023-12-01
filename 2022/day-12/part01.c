#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int x;
  int y;
  int steps;
  struct node *next;
} node;

// Global variable declaration
char *map[50];
node *queue, *visited;
int height, width;

// Functions declarations
int bfs(int x, int y);
int is_node_in_queue(node *n);
void free_memory(node *list);
int get_value(int x, int y);
node *create_node(int x, int y, int steps);
void enque(node **list, node *n);

int main(void) {
  // Open file for reading
  FILE *file = fopen("input.txt", "r");
  if (file == NULL) {
    printf("Could not open file.\n");
    return 1;
  }

  // Read data for file
  int index = 0;
  map[index] = malloc(100);
  while (fscanf(file, "%s", map[index]) != EOF) {
    index++;
    map[index] = malloc(100);
  }

  // Declare height and width of the heightmap
  height = index;
  width = strlen(map[0]);

  // Find Starting coordinates and calculate shortest path
  int part1 = INT_MAX;
  int part2 = INT_MAX;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (map[y][x] == 'S') {
        part1 = bfs(x, y);
      }
      if (map[y][x] == 'a') {
        int p = bfs(x, y);

        if (p < part2) {
          part2 = p;
        }
      }
    }
  }

  // Print results to console
  printf("PART 1: %d steps.\n", part1);
  printf("PART 2: %d steps.\n", part2);

  // Free memory
  for (int i = 0; i < index + 1; i++) {
    free(map[i]);
  }
  free_memory(visited);
  free_memory(queue);
  fclose(file);
}

int bfs(int x, int y) {
  // Free memory of the queue and visited
  free_memory(queue);
  free_memory(visited);
  queue = visited = NULL;

  // Create new node
  node *start = create_node(x, y, 0);

  // Neighbors coordinates
  int dx[] = {1, 0, -1, 0};
  int dy[] = {0, 1, 0, -1};

  // Add starting node to the queue
  queue = start;

  while (queue != NULL) {
    // Get data from current node
    int x = queue->x;
    int y = queue->y;
    int value = get_value(x, y);
    int steps = queue->steps;

    // Remove node from the queue
    node *current = queue;
    queue = queue->next;
    current->next = NULL;

    // Add current node to the visited queue
    current->next = visited;
    visited = current;

    // Find neighbors
    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];

      if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
        // Check if node is the goal
        if (value >= 24 && map[ny][nx] == 'E') {
          return steps + 1;
        }

        int neighbor_value = get_value(nx, ny);
        if (neighbor_value <= value + 1) {
          node *n = create_node(nx, ny, steps + 1);

          if (!is_node_in_queue(n)) {
            // Add node to the queue
            enque(&queue, n);
          } else {
            free(n);
          }
        }
      }
    }
  }
  return INT_MAX;
}

int is_node_in_queue(node *n) {
  node *ptr = queue;
  while (ptr != NULL) {
    if (n->x == ptr->x && n->y == ptr->y && n->steps >= ptr->steps) {
      return 1;
    }
    ptr = ptr->next;
  }

  ptr = visited;
  while (ptr != NULL) {
    if (n->x == ptr->x && n->y == ptr->y && n->steps >= ptr->steps) {
      return 1;
    }
    ptr = ptr->next;
  }
  return 0;
}

void free_memory(node *list) {
  while (list) {
    node *temp = list;
    list = list->next;
    free(temp);
  }
}

int get_value(int x, int y) {
  char value = map[y][x];
  switch (value) {
  case 'S':
    return 0;
  case 'E':
    return 25;
  default:
    return value - 'a';
  }
}

node *create_node(int x, int y, int steps) {
  node *new_node = malloc(sizeof(node));
  new_node->x = x;
  new_node->y = y;
  new_node->steps = steps;
  new_node->next = NULL;
  return new_node;
}

void enque(node **list, node *n) {
  if (*list == NULL) {
    *list = n;
  } else {
    node *current = *list;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = n;
  }
}