#include <advent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Point
{
    long x;
    long y;
} Point;

Point *points = NULL;
size_t npoints = 0;

void get_data(FILE *fp)
{
    size_t n = 0;
    char **lines = readlines(fp, &n);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < strlen(strip(lines[i])); ++j)
        {
            if (lines[i][j] == '#')
            {
                points = realloc(points, ++npoints * sizeof(Point));
                points[npoints - 1] = (Point) { j, i };
            }
        }
    }
    free(lines);
}

Point *scale(FILE *fp, const long dup)
{
    fseek(fp, 0, SEEK_SET);
    size_t n = 0;
    char **lines = readlines(fp, &n);
    long  *rows = NULL, *cols = NULL;
    size_t nrow = 0, ncol = 0;
    // Check for empty horizontal lines
    for (size_t i = 0; i < n; ++i)
    {
        if (indexOf(lines[i], '#') == -1)
        {
            rows = realloc(rows, sizeof(long) * (++nrow));
            rows[nrow - 1] = i;
        }
    }
    // Check for empty vertical lines
    for (size_t i = 0; i < strlen(strip(lines[0])); ++i)
    {
        int empty = 1;
        for (size_t j = 0; j < n; ++j)
        {
            if (lines[j][i] == '#')
            {
                empty = 0;
                break;
            }
        }
        if (empty)
        {
            cols = realloc(cols, sizeof(long) * (++ncol));
            cols[ncol - 1] = i;
        }
    }
    Point *r = calloc(npoints, sizeof(Point));
    for (size_t i = 0; i < npoints; ++i)
    {
        size_t r_inc = 0, c_inc = 0;
        for (size_t j = 0; j < nrow; ++j)
            if (rows && points[i].y > rows[j])
                ++r_inc;
        for (size_t j = 0; j < ncol; ++j)
            if (cols && points[i].x > cols[j])
                ++c_inc;
        r[i] = (Point) { points[i].x + c_inc * (dup - 1), points[i].y + r_inc * (dup - 1) };
    }
    free(rows);
    free(cols);
    return r;
}

long solve(FILE *fp, const long dup)
{
    const Point *pp = scale(fp, dup);

    size_t r = 0;
    for (size_t i = 0; i < npoints; ++i)
        for (size_t j = i + 1; j < npoints; ++j)
            r += (labs(pp[i].x - pp[j].x) + labs(pp[i].y - pp[j].y));
    return r;
}

int main(void)
{
    FILE *fp = fopen("day11.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    get_data(fp);
    printf("Part 1: %ld\n", solve(fp, 2));
    printf("Part 2: %ld\n", solve(fp, 1000000));

    free(points);
    fclose(fp);
    return 0;
}
