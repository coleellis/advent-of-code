#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool safe(int *row, size_t len)
{
    bool safe = true;
    bool inc  = true;

    for (size_t i = 0; i < len - 1; ++i)
    {
        // Set increment on first pass
        if (i == 0)
            inc = (row[i + 1] > row[i]);

        // Check for increment swap
        if ((inc && row[i + 1] < row[i]) || (!inc && row[i + 1] > row[i]))
        {
            safe = false;
            break;
        }

        // Check bounds
        if (abs(row[i + 1] - row[i]) < 1 || abs(row[i + 1] - row[i]) > 3)
        {
            safe = false;
            break;
        }
    }

    return safe;
}

int *tokenize(char *line, size_t *len)
{
    size_t i   = 0;
    int   *arr = calloc(++i, sizeof(int));

    char *ptr;
    char *token = strtok_r(line, " ", &ptr);
    while (token)
    {
        // Get number
        long num   = strtol(token, NULL, 10);
        arr[i - 1] = (int)num;

        // Resize and get next
        arr   = realloc(arr, (++i) * sizeof(int));
        token = strtok_r(NULL, " ", &ptr);
    }

    *len = i - 1;
    return arr;
}

int *pop(int *row, size_t len, size_t idx)
{
    // Make a copy
    int *copy = calloc(len - 1, sizeof(int));

    // Copy
    memcpy(copy, row, idx * sizeof(int));
    memcpy(&copy[idx], &row[idx + 1], (len - idx - 1) * sizeof(int));

    return copy;
}

int main(int argc, char **argv)
{
    // Args
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Get filename
    FILE *fp = fopen(argv[1], "r");
    if (!fp)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Run through
    char  *line = NULL;
    size_t len;
    int    one = 0;
    int    two = 0;
    while (getline(&line, &len, fp) != -1)
    {
        // Part 1
        int *row = tokenize(line, &len);
        if (safe(row, len))
            ++one;

        // Part 2
        for (size_t i = 0; i < len; ++i)
        {
            int *newrow = pop(row, len, i);
            if (safe(newrow, len - 1))
                ++two;
            free(newrow);
        }
        free(row);
    }

    printf("one: %d\n", one);
    printf("two: %d\n", two);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}
