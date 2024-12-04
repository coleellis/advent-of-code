#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **grid;
int    gridlen;

bool bounded(int i, int j)
{
    return 0 <= i && i < gridlen && 0 <= j && j < gridlen;
}

int one(void)
{
    int  ret     = 0;
    char match[] = "XMAS";
    for (int i = 0; i < gridlen; ++i)
    {
        for (int j = 0; j < gridlen; ++j)
        {
            // Start with X
            if (grid[i][j] != 'X')
                continue;

            // Walk each direction
            for (int di = -1; di <= 1; ++di)
            {
                for (int dj = -1; dj <= 1; ++dj)
                {
                    // Ignore standing still
                    if (di == 0 && dj == 0)
                        continue;

                    // Bounds check
                    if (bounded(i + 3 * di, j + 3 * dj))
                    {
                        bool valid = true;

                        // String check
                        for (int k = 0; k < 4; ++k)
                        {
                            if (grid[i + k * di][j + k * dj] != match[k])
                            {
                                valid = false;
                                break;
                            }
                        }

                        // Check if we found a match
                        if (valid)
                            ++ret;
                    }
                }
            }
        }
    }
    return ret;
}

int two(void)
{
    int ret = 0;

    for (int i = 0; i < gridlen; ++i)
    {
        for (int j = 0; j < gridlen; ++j)
        {
            // Start with middle ('A')
            if (grid[i][j] != 'A')
                continue;

            // Check 3x3 bounds (+= 2 is intentional, we don't need to hit 0)
            bool bound = true;
            for (int di = -1; di <= 1; di += 2)
            {
                for (int dj = -1; dj <= 1; dj += 2)
                {
                    if (!bounded(i + di, j + dj))
                        bound = false;
                    break;
                }
                // Slight time saver (I think)
                if (!bound)
                    break;
            }
            if (!bound)
                continue;

            // Match the characters
            if (((grid[i - 1][j - 1] == 'M' && grid[i + 1][j + 1] == 'S')
                    || (grid[i - 1][j - 1] == 'S' && grid[i + 1][j + 1] == 'M'))
                && ((grid[i + 1][j - 1] == 'M' && grid[i - 1][j + 1] == 'S')
                    || (grid[i + 1][j - 1] == 'S' && grid[i - 1][j + 1] == 'M')))
                ++ret;
        }
    }
    return ret;
}

int main(void)
{
    // Get data
    FILE *fp = fopen("day04.txt", "r");
    if (!fp)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Make grid
    char  *line    = NULL;
    size_t len     = 0;
    bool   first   = true;
    int    linenum = 0;
    while (getline(&line, &len, fp) != -1)
    {
        // Allocate grid on first pass
        if (first)
        {
            gridlen = strlen(line);

            grid = calloc(gridlen, sizeof(char *));
            for (int i = 0; i < gridlen; ++i)
                grid[i] = calloc(gridlen, sizeof(char));

            first = false;
        }

        // Assign the line
        strncpy(grid[linenum], line, gridlen);
        ++linenum;
    }

    // Run each part
    printf("one: %d\n", one());
    printf("two: %d\n", two());

    // Free grid
    for (int i = 0; i < gridlen; ++i)
        free(grid[i]);
    free(grid);
    // Free line
    if (line)
        free(line);
    // Close file
    fclose(fp);

    exit(EXIT_SUCCESS);
}
