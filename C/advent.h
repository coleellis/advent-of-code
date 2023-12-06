#ifndef ADVENT_H
#define ADVENT_H

#define SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

char *strip(char *str);
char **split(const char *str, const char *delim, size_t *len);
char** readlines(FILE* fp, size_t* len);

#endif // ADVENT_H