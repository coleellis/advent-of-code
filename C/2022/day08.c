#include <stdio.h>
#include <stdlib.h>

enum Visible
{
    NOT_VISIBLE,
    VISIBLE
};

int one(FILE *fp)
{
    // Prep file
    char   *line = NULL;
    ssize_t read;
    size_t  len;

    // Get the size of the file
    size_t rows = 0;
    size_t cols = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        cols = ((size_t)(read - 1) > cols) ? (size_t)(read - 1) : cols;
        ++rows;
    }

    // Allocate the grid
    char **grid = calloc(rows, sizeof(char *));
    for (size_t i = 0; i < rows; ++i)
        grid[i] = calloc(cols, sizeof(char));

    // Read the lines and allocate again
    fseek(fp, 0, SEEK_SET);
    size_t count = 0;
    while (getline(&line, &len, fp) != -1)
    {
        for (size_t i = 0; i < cols; ++i)
            grid[count][i] = line[i];
        ++count;
    }

    // Allocate a visibility grid
    int **vis = malloc(rows * sizeof(int *));
    for (size_t i = 0; i < rows; ++i)
    {
        vis[i] = malloc(cols * sizeof(int));
        for (size_t j = 0; j < cols; ++j)
            vis[i][j] = NOT_VISIBLE;
    }

    // Run the rows
    for (size_t i = 0; i < rows; ++i)
    {
        char tallest = grid[i][0];

        vis[i][0] = VISIBLE;
        vis[i][cols - 1] = VISIBLE;

        // Run the rows forward
        for (size_t j = 0; j < cols; ++j)
        {
            if (grid[i][j] > tallest)
                vis[i][j] = VISIBLE;
            tallest = (grid[i][j] > tallest) ? grid[i][j] : tallest;
        }

        // Run the rows in reverse
        tallest = grid[i][cols - 1];
        for (size_t j = cols - 1; j < cols; --j)
        {
            if (grid[i][j] > tallest)
                vis[i][j] = VISIBLE;
            tallest = (grid[i][j] > tallest) ? grid[i][j] : tallest;
            if (j == 0)
                break; // Prevent underflow
        }
    }

    // Run the columns
    for (size_t j = 0; j < cols; ++j)
    {
        char tallest = grid[0][j];

        vis[0][j] = VISIBLE;
        vis[rows - 1][j] = VISIBLE;

        // Run the rows forward
        for (size_t i = 0; i < rows; ++i)
        {
            if (grid[i][j] > tallest)
                vis[i][j] = VISIBLE;
            tallest = (grid[i][j] > tallest) ? grid[i][j] : tallest;
        }

        // Run the rows in reverse
        tallest = grid[rows - 1][j];
        for (size_t i = rows - 1; i < rows; --i)
        {
            if (grid[i][j] > tallest)
                vis[i][j] = VISIBLE;
            tallest = (grid[i][j] > tallest) ? grid[i][j] : tallest;
            if (i == 0)
                break; // Prevent underflow
        }
    }
    free(grid);

    // Count the number of visible
    int num_visible = 0;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            if (vis[i][j] == VISIBLE)
                ++num_visible;
        }
    }
    for (size_t i = 0; i < rows; ++i)
        free(vis[i]);
    free(vis);
    return num_visible;
}

int two(FILE *fp)
{
    // Prep file
    char   *line = NULL;
    ssize_t read;
    size_t  len;

    // Get the size of the file
    size_t rows = 0;
    size_t cols = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        cols = ((size_t)(read - 1) > cols) ? (size_t)(read - 1) : cols;
        ++rows;
    }

    // Allocate the grid
    char **grid = malloc(rows * sizeof(char *));
    for (size_t i = 0; i < rows; ++i)
        grid[i] = malloc(cols * sizeof(char));

    // Read the lines and allocate again
    fseek(fp, 0, SEEK_SET);
    size_t count = 0;
    while (getline(&line, &len, fp) != -1)
    {
        for (size_t i = 0; i < cols; ++i)
            grid[count][i] = line[i];
        ++count;
    }

    // Find the max score
    size_t max_score = 0;
    for (size_t row = 1; row < rows - 1; ++row)
    {
        for (size_t col = 1; col < cols - 1; ++col)
        {
            const char height = grid[row][col];
            size_t     point_score = 1;

            // Check the up direction
            size_t up_score = 1;
            for (size_t i = row - 1; i > 0; --i)
            {
                ++up_score;
                if (height <= grid[i][col])
                    break;
                if (i == 0)
                    break; // Prevent underflow
            }
            point_score *= up_score;

            // Check the down direction
            size_t down_score = 1;
            for (size_t i = row + 1; i < rows; ++i)
            {
                ++down_score;
                if (height <= grid[i][col])
                    break;
            }
            point_score *= down_score;

            // Check the left direction
            size_t left_score = 1;
            for (size_t j = col - 1; j > 0; --j)
            {
                ++left_score;
                if (height <= grid[row][j])
                    break;
                if (j == 0)
                    break; // Prevent underflow
            }
            point_score *= left_score;

            // Check the right direction
            size_t right_score = 1;
            for (size_t j = col + 1; j < cols; ++j)
            {
                ++right_score;
                if (height <= grid[row][j])
                    break;
            }
            point_score *= right_score;

            // Check the max
            max_score = (point_score > max_score) ? point_score : max_score;
        }
    }

    for (size_t i = 0; i < rows; ++i)
        free(grid[i]);
    free(grid);
    return max_score;
}

int main(void)
{
    FILE *fp = fopen("day08.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    printf("ONE: %d\n", one(fp));
    fseek(fp, 0, SEEK_SET);
    printf("TWO: %d\n", two(fp));

    fclose(fp);
    return EXIT_SUCCESS;
}
