#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "advent.h"

// perform python-like stripping
char *strip(char *str)
{
    // strip leading whitespace
    while (isspace(*str))
        ++str;

    // strip trailing whitespace
    char *end = str + strlen(str) - 1;
    while (end > str && isspace(*end))
        --end;
    *(end + 1) = '\0';

    // return stripped string
    return str;
}

// perform python-like split on string
char **split(const char *str, const char *delim, size_t *len)
{
    // make copy
    char *copy = strdup(str);
    if (!str)
        return NULL;

    // get number of instances
    size_t num = 1, idx = 0;
    char *tmp = copy, *ptr;
    while (*tmp)
    {
        if (strstr(tmp, delim) == tmp)
        {
            ++num;
            tmp += strlen(delim);
        }
        else
        {
            ++tmp;
        }
    }

    // generate list
    char **list = malloc(num * sizeof(char *));
    if (!list)
        return NULL;

    // get tokens
    char *token = strtok_r(copy, delim, &ptr);
    while (token != NULL)
    {
        list[idx++] = token;
        token = strtok_r(NULL, delim, &ptr);
    }

    // return list
    if (len)
        *len = idx;
    return list;
}

char** readlines(FILE* fp, size_t* len)
{
    // get number of lines
    size_t num = 0;
    char* line = NULL;
    while (getline(&line, len, fp) != -1)
        ++num;
    fseek(fp, 0, 0);

    char** lines = malloc(num * sizeof(char*));
    for (size_t i = 0; i < num; ++i)
    {
        getline(&line, len, fp);
        lines[i] = strdup(line);
    }
    if (len) *len = num;
    return lines;
}