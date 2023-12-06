#include <stdio.h>
#include <stdlib.h>

enum Visible
{
    NOT_VISIBLE,
    VISIBLE
};

int one(FILE *fp)
{
    // prep file
    char *line = NULL;
    ssize_t read;
    size_t len;

    // get the size of the file
    size_t rows = 0;
    size_t cols = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        cols = ((read - 1) > cols) ? (read - 1) : cols;
        ++rows;
    }

    // allocate the grid
    char **grid = malloc(rows * sizeof(char *));
    for (size_t i = 0; i < rows; ++i)
        grid[i] = malloc(cols * sizeof(char));

    // read the lines and allocate again
    fp = fopen("input.txt", "r");
    size_t count = 0;
    while (getline(&line, &len, fp) != -1)
    {
        for (size_t i = 0; i < cols; ++i)
            grid[count][i] = line[i];
        ++count;
    }

    // allocate a visibility grid
    int **vis = malloc(rows * sizeof(int *));
    for (size_t i = 0; i < rows; ++i)
    {
        vis[i] = malloc(cols * sizeof(int));
        for (size_t j = 0; j < cols; ++j)
            vis[i][j] = NOT_VISIBLE;
    }

    // run the rows
    for (size_t i = 0; i < rows; ++i)
    {
        size_t tallest = grid[i][0];

        vis[i][0] = VISIBLE;
        vis[i][cols - 1] = VISIBLE;

        // run the rows forward
        for (size_t j = 0; j < cols; ++j)
        {
            if (grid[i][j] > tallest)
                vis[i][j] = VISIBLE;
            tallest = (grid[i][j] > tallest) ? grid[i][j] : tallest;
        }

        // run the rows in reverse
        tallest = grid[i][rows - 1];
        for (int j = cols - 1; j >= 0; --j)
        {
            if (grid[i][j] > tallest)
                vis[i][j] = VISIBLE;
            tallest = (grid[i][j] > tallest) ? grid[i][j] : tallest;
        }
    }

    // run the columns
    for (size_t j = 0; j < cols; ++j)
    {
        size_t tallest = grid[0][j];

        vis[0][j] = VISIBLE;
        vis[rows - 1][j] = VISIBLE;

        // run the rows forward
        for (size_t i = 0; i < cols; ++i)
        {
            if (grid[i][j] > tallest)
                vis[i][j] = VISIBLE;
            tallest = (grid[i][j] > tallest) ? grid[i][j] : tallest;
        }

        // run the rows in reverse
        tallest = grid[cols - 1][0];
        for (int i = rows - 1; i >= 0; --i)
        {
            if (grid[i][j] > tallest)
                vis[i][j] = VISIBLE;
            tallest = (grid[i][j] > tallest) ? grid[i][j] : tallest;
        }
    }

    // count the number of visible
    int num_visible = 0;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            if (vis[i][j] == VISIBLE)
                ++num_visible;
        }
    }

    return num_visible;
}

int two(FILE *fp)
{
    // prep file
    char *line = NULL;
    ssize_t read;
    size_t len;

    // get the size of the file
    size_t rows = 0;
    size_t cols = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        cols = ((read - 1) > cols) ? (read - 1) : cols;
        ++rows;
    }

    // allocate the grid
    char **grid = malloc(rows * sizeof(char *));
    for (size_t i = 0; i < rows; ++i)
        grid[i] = malloc(cols * sizeof(char));

    // read the lines and allocate again
    fseek(fp, 0, 0);
    size_t count = 0;
    while (getline(&line, &len, fp) != -1)
    {
        for (size_t i = 0; i < cols; ++i)
            grid[count][i] = line[i];
        ++count;
    }

    // find the max score
    int max_score = 0;
    for (size_t row = 1; row < rows - 1; ++row)
    {
        for (size_t col = 1; col < cols - 1; ++col)
        {
            char height = grid[row][col];
            size_t point_score = 1;

            // check the up direction
            size_t up_score = 1;
            for (int i = row - 2; i >= 0; --i)
            {
                ++up_score;
                if (height <= grid[i][col])
                    break;
            }
            point_score *= up_score;

            // check the down direction
            size_t down_score = 1;
            for (int i = row + 2; i < cols; ++i)
            {
                ++down_score;
                if (height <= grid[i][col])
                    break;
            }
            point_score *= down_score;

            // check the left direction
            size_t left_score = 1;
            for (int j = col - 2; j >= 0; --j)
            {
                ++left_score;
                if (height <= grid[row][j])
                    break;
            }
            point_score *= left_score;

            // check the down direction
            size_t right_score = 1;
            for (int j = col + 2; j < cols; ++j)
            {
                ++right_score;
                if (height <= grid[row][j])
                    break;
            }
            point_score *= right_score;

            // check the max
            max_score = (point_score > max_score) ? point_score : max_score;
        }
    }

    for (size_t i = 0; i < rows; ++i)
        free(grid[i]);
    free(grid);
    return max_score;
}

int main()
{
    FILE *fp = fopen("day08.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    printf("ONE: %d\n", one(fp));
    fseek(fp, 0, 0);
    printf("TWO: %d\n", two(fp));

    fclose(fp);
    return EXIT_SUCCESS;
}