#include <advent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int   *times = NULL;
size_t items = 0;
int   *dists = NULL;

void parse_data(FILE *fp)
{
    char **lines = readlines(fp, NULL);
    char **t     = split(strip(split(lines[0], ":", NULL)[1]), " ", &items);
    char **d     = split(strip(split(lines[1], ":", NULL)[1]), " ", &items);
    times        = malloc(items * sizeof(int));
    for (size_t i = 0; i < items; ++i)
        times[i] = atoi(t[i]);
    dists = malloc(items * sizeof(int));
    for (size_t i = 0; i < items; ++i)
        dists[i] = atoi(d[i]);

    free(lines);
    free(t);
    free(d);
}

int one(void)
{
    int one = 1;
    for (size_t i = 0; i < items; ++i)
    {
        const int t = times[i], d = dists[i];
        long      w = 0;
        for (int j = 0; j < t; ++j)
        {
            if (j * (t - j) > d)
                ++w;
        }
        one *= w;
    }
    return one;
}

long two(void)
{
    char tstr[20] = "", dstr[20] = "";
    for (size_t i = 0; i < items; ++i)
    {
        char t[5], d[5];
        sprintf(t, "%d", times[i]);
        sprintf(d, "%d", dists[i]);
        strcat(tstr, t);
        strcat(dstr, d);
    }
    const long time = atol(tstr), dist = atol(dstr);

    int two = 0;
    for (long i = 0; i < time; ++i)
    {
        if (i * (time - i) > dist)
            ++two;
    }
    return two;
}

int main(void)
{
    FILE *fp = fopen("day06.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    parse_data(fp);

    printf("ONE: %d\n", one());
    printf("TWO: %ld\n", two());

    free(times);
    free(dists);

    fclose(fp);
    return 0;
}
