#include <stdio.h>
#include <stdlib.h>

typedef struct FileNode {
  char *name;
  size_t size;
} file;

struct DirNode {
  char *name;
  struct DirNode *parent;
  // for parsing laterally
  struct DirNode *next;
  // files and folders
  struct DirNode *folders;
  struct FileNode *files;
} DirNode_default = {"", NULL, NULL, NULL, NULL};
typedef struct DirNode folder;

int main(void) {
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL) {
    perror("Unable to open file!");
    exit(EXIT_FAILURE);
  }

  // data collected in parse
  char *line = NULL;
  char *prevLine = NULL;
  size_t len;
  ssize_t read;

  // root of directory
  folder *root = malloc(sizeof(folder));
  *root = DirNode_default;
  root->name = "/";
  folder *current = root;

  // parse the file
  int isFirstLine = 1;
  while ((read = getline(&line, &len, fp)) != -1) {
    if (isFirstLine) {
      isFirstLine = 0;
      continue;
    }

    printf("Current directory: %s\n", current->name);
    printf("Line %zd: %s", ftell(fp), line);
    // first line guaranteed command
    if (line[2] == 'l') // ls command
    {
      // read until next line is '$'
      do {
        prevLine = line;
        read = getline(&line, &len, fp);
        printf("%zd : %s", read, line);
      } while (line[0] != '$' && read != -1);
      fseek(fp, fseek(fp) - read, SEEK_SET);
    } else if (line[2] == 'c') // cd command
    {
      // get name
      char *name = malloc(sizeof(char) * (read - 6));
      for (size_t i = 6; line[i] != '\n'; ++i) {
        name[i - 6] = line[i];
      }
      // check if we've made the directory
      for (folder *child = root->folders; child != NULL; child = child->next) {
        if (child->name == name) {
          current = child;
          break;
        }
      }
    }
    line = prevLine;
  }
}