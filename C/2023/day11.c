#include <advent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Point {
    long x;
    long y;
} Point;

size_t items = 0;
Point* p = NULL;

void get_data(FILE* fp, const size_t dup)
{
    size_t l;
    char** lines = readlines(fp, &l);

    // get all the points
    const size_t r = l;
    const size_t c = strlen(strip(lines[0]));
    for (size_t y = 0; y < l; ++y) {
        for (size_t x = 0; x < c; ++x) {
            if (lines[y][x] == '#') {
                p = realloc(p, sizeof(Point) * (++items));
                p[items - 1] = (Point) { x, y };
            }
        }
    }

    // get the rows and cols that are empty
    int* rows = malloc(r * sizeof(int));
    int* cols = malloc(c * sizeof(int));
    size_t rr = 0, cc = 0;
    for (size_t y = 0; y < r; ++y) {
        int b = 1;
        for (size_t x = 0; x < c; ++x) {
            if (lines[y][x] == '#') {
                b = 0;
                break;
            }
        }
        if (b)
            rows[rr++] = y;
    }
    rows = realloc(rows, rr * sizeof(int));
    for (size_t x = 0; x < c; ++x) {
        int b = 1;
        for (size_t y = 0; y < l; ++y) {
            if (lines[y][x] == '#') {
                b = 0;
                break;
            }
        }
        if (b)
            cols[cc++] = x;
    }
    cols = realloc(cols, cc * sizeof(int));

    // duplicate the empty columns/rows dup times
    for (size_t i = 0; i < items; ++i) {
        size_t nr = 0, nc = 0;
        for (size_t j = 0; j < rr; ++j) {
            if (rows[j] < p[i].y)
                ++nr;
            else
                break;
        }
        for (size_t j = 0; j < cc; ++j) {
            if (cols[j] < p[i].x)
                ++nc;
            else
                break;
        }
        p[i] = (Point) { p[i].x + (dup - 1) * nc, p[i].y + (dup - 1) * nr };
    }

    free(rows);
    free(cols);
    free(lines);
}

long solve()
{
    long r = 0;
    for (size_t i = 0; i < items; ++i)
        for (size_t j = i + 1; j < items; ++j)
            r += (labs(p[i].x - p[j].x) + labs(p[i].y - p[j].y));
    return r;
}

void reset(FILE* fp)
{
    free(p);
    p = NULL;
    items = 0;
    fseek(fp, 0, SEEK_SET);
}

int main()
{
    FILE* fp = fopen("day11.txt", "r");
    if (!fp) {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    get_data(fp, 2);
    printf("Part 1: %ld\n", solve());
    reset(fp);

    get_data(fp, 1000000);
    printf("Part 2: %ld\n", solve());
    reset(fp);

    fclose(fp);
    return 0;
}
