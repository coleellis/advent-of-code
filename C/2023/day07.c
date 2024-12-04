#include <advent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_SIZE 256

typedef struct Map
{
    int *k;
    int  v;
} Map;

int c_map(const void *a, const void *b)
{
    const Map aa = *(const Map *)a;
    const Map bb = *(const Map *)b;
    const int tl = 6;

    for (int i = 0; i < tl; i++)
    {
        if (aa.k[i] != bb.k[i])
            return aa.k[i] - bb.k[i];
    }
    return 0;
}

int c_int(const void *a, const void *b)
{
    return *(const int *)b - *(const int *)a;
}

const int types[7][5]
    = { { 1, 1, 1, 1, 1 }, { 1, 1, 1, 2 }, { 1, 2, 2 }, { 1, 1, 3 }, { 2, 3 }, { 1, 4 }, { 5 } };

int *one(const char *h)
{
    const size_t l = strlen(h);
    // Get indices for each one
    int indices[l];
    for (size_t i = 0; i < l; ++i)
        indices[i] = indexOf("J23456789TXQKA", h[i]);

    // Make a map of the number of instances of each char in the string
    int *m = calloc(ASCII_SIZE, sizeof(int));
    for (size_t i = 0; i < l; ++i)
        ++m[(int)h[i]];

    // Filter out the 0s
    qsort(m, ASCII_SIZE, sizeof(int), c_int);
    size_t ns = 0;
    while (m[ns] != 0)
        ++ns;
    m = rev(realloc(m, ns * sizeof(int)), ns);

    // Determine the type of hand
    int type = -1;
    for (size_t i = 0; i < 7; ++i)
    {
        int z = 1;
        for (size_t j = 0; j < 5; ++j)
        {
            if (j >= ns)
                break;
            if (types[i][j] != m[j])
            {
                z = 0;
                break;
            }
        }
        if (z)
        {
            type = i;
            break;
        }
    }
    free(m);

    // Concatenate the type and the indices
    int *ret = calloc((l + 1), sizeof(int));
    ret[0]   = type;
    for (size_t i = 0; i < l + 1; ++i)
        ret[i + 1] = indices[i];
    return ret;
}

int *two(const char *h)
{
    const size_t l = strlen(h);
    // Get indices for each char
    int    indices[l];
    size_t ns;
    for (size_t i = 0; i < l; ++i)
        indices[i] = indexOf("J23456789TXQKA", h[i]);

    // Get the best hand based on the joker wildcard
    const char *p    = "J23456789TQKA";
    int       **list = malloc(1000 * sizeof(int *));
    for (ns = 0; ns < strlen(p); ++ns)
        list[ns] = one(replace(h, 'J', p[ns]));
    list = realloc(list, ns * sizeof(int *));
    qsort(list, ns, sizeof(int *), c_map);

    // Use the pre-replacement indices
    int *ret = malloc((l + 1) * sizeof(int));
    ret[0]   = list[ns - 1][0];
    for (size_t i = 0; i < l; ++i)
        ret[i + 1] = indices[i];

    free(list);
    return ret;
}

int main(void)
{
    FILE *fp = fopen("day07.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    // Read the hands
    size_t len;
    char **lines = readlines(fp, &len);

    // Parse the hands
    Map *first  = malloc(len * sizeof(Map));
    Map *second = malloc(len * sizeof(Map));
    for (size_t i = 0; i < len; ++i)
    {
        char **tokens = split(lines[i], " ", NULL);
        first[i]      = (Map) { one(replace(tokens[0], 'J', 'X')), atoi(tokens[1]) };
        second[i]     = (Map) { two(tokens[0]), atoi(tokens[1]) };
    }

    // Sort the hands
    qsort(first, len, sizeof(Map), c_map);
    qsort(second, len, sizeof(Map), c_map);

    // Get the total
    int f = 0, s = 0;
    for (size_t i = 0; i < len; ++i)
    {
        f += ((i + 1) * first[i].v);
        s += ((i + 1) * second[i].v);
    }
    printf("ONE: %d\n", f);
    printf("TWO: %d\n", s);

    // Free the hands
    for (size_t i = 0; i < len; ++i)
    {
        free(first[i].k);
        free(second[i].k);
    }
    free(first);
    free(second);
    free(lines);
    fclose(fp);
    return 0;
}
