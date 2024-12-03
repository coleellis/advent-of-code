#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int safe(int* row, int len)
{
    int safe = 1;
    int inc = 1;

    for (int i = 0; i < len - 1; ++i) {
        // First pass -- Set increasing flag
        if (i == 0) {
            if (row[i + 1] - row[i] > 0)
                inc = 1;
            else
                inc = 0;
        }

        // Check for swap
        if ((inc && row[i + 1] < row[i]) || (!inc && row[i + 1] > row[i])) {
            safe = 0;
            break;
        }

        // Check for bounds
        if (abs(row[i + 1] - row[i]) < 1 || abs(row[i + 1] - row[i]) > 3) {
            safe = 0;
            break;
        }
    }

    return safe;
}

int* tokenize(char* line, size_t* len)
{
    size_t i = 0;
    int* arr = calloc(++i, sizeof(int));

    char* ptr;
    char* token = strtok_r(line, " ", &ptr);
    while (token) {
        long i = strtol(token, NULL, 10);
        arr[i - 1] = (int)i;
        arr = realloc(arr, (++i) * sizeof(int));
        token = strtok_r(NULL, " ", &ptr);
    }

    *len = i - 1;
    return arr;
}

int main(int argc, char** argv)
{
    // Validate Arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Get File
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char* line = NULL;
    size_t len = 0;
    size_t one = 0;
    while (getline(&line, &len, fp) != -1) {
        int* row = tokenize(line, &len);
        if (safe(row, len))
            ++one;
        free(row);
    }

    // Print Answers
    printf("ONE: %zu\n", one);

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}