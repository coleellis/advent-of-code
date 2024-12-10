#include "advent.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int  **grid;
    size_t rows;
    size_t cols;
} Grid;

typedef struct
{
    size_t x;
    size_t y;
} Point;

typedef struct
{
    Point **pts;
    size_t  len;
} Points;

// Global grid
Grid grid = { .grid = NULL, .rows = 0, .cols = 0 };

void fill_grid(char *data)
{
    char *line = data;
    char *end;

    while (line && *line)
    {
        // Get line length
        end        = strchr(line, '\n');
        size_t len = end ? (size_t)(end - line) : strlen(line);
        if (grid.cols == 0)
            grid.cols = (int)len;

        // Reallocate
        grid.grid            = realloc(grid.grid, (grid.rows + 1) * sizeof(int *));
        grid.grid[grid.rows] = calloc(grid.cols, sizeof(int));

        // Fill row
        for (size_t i = 0; i < grid.cols; ++i)
        {
            char c                  = line[i];
            long l                  = strtol(&c, NULL, 10);
            grid.grid[grid.rows][i] = (int)l;
        }

        // Move onto next
        ++grid.rows;
        line = end ? end + 1 : NULL;
    }
}

int dfs_unique(size_t i, size_t j, Points *pts)
{
    // We're at the end
    if (grid.grid[i][j] == 9)
    {
        // Check if we've been here before
        int flag = 1;
        for (size_t n = 0; n < pts->len; ++n)
        {
            if (pts->pts[n]->x == i && pts->pts[n]->y == j)
            {
                flag = 0;
                break;
            }
        }

        // Add unique point
        if (flag)
        {
            // New point
            Point *point = calloc(1, sizeof(Point));
            point->x     = i;
            point->y     = j;

            // Add to array
            pts->pts               = realloc(pts->pts, (++pts->len) * sizeof(Point *));
            pts->pts[pts->len - 1] = point;
        }

        // This return doesn't matter, we never read it. But we
        // must match return type, so I went consistent. This
        // could be anything.
        return pts->len;
    }

    // DFS
    for (int di = -1; di <= 1; ++di)
    {
        for (int dj = -1; dj <= 1; ++dj)
        {
            // Can't go diagonal
            if (di == dj || di * -1 == dj)
                continue;

            size_t ni = i + di, nj = j + dj;
            if (ni < grid.rows && nj < grid.cols && grid.grid[ni][nj] == grid.grid[i][j] + 1)
                dfs_unique(ni, nj, pts);
        }
    }
    return pts->len;
}

int dfs_any(size_t i, size_t j)
{
    // We are at the end
    if (grid.grid[i][j] == 9)
        return 1;

    int ret = 0;
    for (int di = -1; di <= 1; ++di)
    {
        for (int dj = -1; dj <= 1; ++dj)
        {
            // Can't go diagonal
            if (di == dj || di * -1 == dj)
                continue;

            size_t ni = i + di, nj = j + dj;
            if (ni < grid.rows && nj < grid.cols && grid.grid[ni][nj] == grid.grid[i][j] + 1)
                ret += dfs_any(ni, nj);
        }
    }
    return ret;
}

int main(void)
{
    char *data = get_data(10, 2024);
    fill_grid(data);

    int one = 0, two = 0;
    for (size_t i = 0; i < grid.rows; ++i)
    {
        for (size_t j = 0; j < grid.cols; ++j)
        {
            if (grid.grid[i][j] == 0)
            {
                // Make points for P1
                Points *pts = calloc(1, sizeof(Points));

                // DFS
                one += dfs_unique(i, j, pts);
                two += dfs_any(i, j);

                // Cleanup points
                for (size_t n = 0; n < pts->len; ++n)
                    free(pts->pts[n]);
                free(pts->pts);
                free(pts);
            }
        }
    }

    // Print answers
    printf("ONE: %d\n", one);
    printf("TWO: %d\n", two);

    // Cleanup
    for (size_t i = 0; i < grid.rows; ++i)
        free(grid.grid[i]);
    free(grid.grid);
    free(data);

    return EXIT_SUCCESS;
}
