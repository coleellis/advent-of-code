#include <advent.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** grids = NULL;
size_t ngrids = 0;

void get_data(FILE* fp)
{
    char* line = NULL;
    char* grid = malloc(1e6);
    size_t len;
    while (getline(&line, &len, fp) != -1) {
        if (strcmp(line, "\n") == 0) {
            grids = realloc(grids, sizeof(char*) * (ngrids + 1));
            grids[ngrids++] = strdup(grid);
            memset(grid, 0, sizeof(grid));
        } else {
            strcat(grid, line);
        }
    }
    // add last grid
    grids = realloc(grids, sizeof(char*) * (ngrids + 1));
    grids[ngrids++] = grid;

    free(grid);
}

long symmetry(char** grid, const int margin)
{
    return 0;
}

long iterate(const int margin)
{
    long r = 0;
    for (size_t i = 0; i < ngrids; ++i) {
        size_t rows = 0;
        char** grid = split(grids[i], "\n", &rows);
        const size_t cols = strlen(grid[0]);
        // create a transposed grid
        char** tgrid = malloc(cols);
        for (size_t j = 0; j < cols; ++j) {
            tgrid[j] = malloc(rows);
            for (size_t k = 0; k < rows; ++k) {
                tgrid[j][k] = grid[k][j];
            }
        }

        long s = symmetry(tgrid, margin);
        if (s == -1)
            s = symmetry(grid, margin);
        r += s;
        free(tgrid);
    }
    return r;
}

int main()
{
    FILE* fp = fopen("day13.txt", "r");
    if (!fp) {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    get_data(fp);

    printf("ONE: %ld\n", iterate(0));
    printf("TWO: %ld\n", iterate(1));

    fclose(fp);
    return 0;
}
