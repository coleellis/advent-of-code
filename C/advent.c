#include "advent.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* strip(char* str)
{
    // strip leading whitespace
    while (isspace(*str))
        ++str;

    // strip trailing whitespace
    char* end = str + strlen(str) - 1;
    while (end > str && isspace(*end))
        --end;
    *(end + 1) = '\0';

    // return stripped string
    return str;
}

char** split(const char* str, const char* delim, size_t* len)
{
    // make copy
    char* copy = strdup(str);
    if (!str)
        return NULL;

    // get number of instances
    size_t num = 1, idx = 0;
    const char *tmp = copy, *ptr;
    while (*tmp) {
        if (strstr(tmp, delim) == tmp) {
            ++num;
            tmp += strlen(delim);
        } else {
            ++tmp;
        }
    }

    // generate list
    char** list = calloc(num, sizeof(char*));
    if (!list)
        return NULL;

    // get tokens
    char* token = strtok_r(copy, delim, &ptr);
    while (token != NULL) {
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
    size_t dummy;
    while (getline(&line, &dummy, fp) != -1)
        ++num;
    fseek(fp, 0, 0);

    char** lines = calloc(num, sizeof(char*));
    for (size_t i = 0; i < num; ++i) {
        getline(&line, &dummy, fp);
        lines[i] = strdup(line);
    }
    if (len)
        *len = num;
    return lines;
}

int indexOf(const char* str, const char c)
{
    const char* l = strchr(str, c);
    return l != NULL ? (l - str) : -1;
}

int* rev(int* arr, const size_t len)
{
    for (size_t i = 0; i < len / 2; ++i) {
        const int tmp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = tmp;
    }
    return arr;
}

char* replace(const char* s, const char a, const char b)
{
    char* ret = strdup(s);
    for (size_t i = 0; i < strlen(s); ++i)
        if (s[i] == a)
            ret[i] = b;
    return ret;
}

long gcd(const long a, const long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long lcm(const long a[], const size_t n)
{
    long ans = a[0];
    for (size_t i = 1; i < n; ++i)
        ans = (((a[i] * ans)) / (gcd(a[i], ans)));
    return ans;
}

int* intify(char** a, const size_t n)
{
    int* r = calloc(n, sizeof(int));
    for (size_t i = 0; i < n; ++i)
        r[i] = atoi(a[i]);
    free(a);
    return r;
}

long* longify(char** a, const size_t n)
{
    long* r = calloc(n, sizeof(long));
    for (size_t i = 0; i < n; ++i)
        r[i] = atol(a[i]);
    free(a);
    return r;
}

void sprint(const char** a, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        printf("%s ", a[i]);
    printf("\n");
}

void dprint(const int* a, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        printf("%d ", a[i]);
    printf("\n");
}

void lprint(const long* a, const size_t n) {
    for (size_t i = 0; i < n; ++i)
        printf("%ld ", a[i]);
    printf("\n");
}

void fprint(const double* a, const size_t n)
{
    for (size_t i = 0; i < n; ++i)
        printf("%f ", a[i]);
    printf("\n");
}