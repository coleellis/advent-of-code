#include <stdio.h>
#include <stdlib.h>

#define STRING_LEN 14

int compare(const void *a, const void *b) { return *(char *)a - *(char *)b; }

int unique(char *string, size_t length)
{
    qsort(string, length, sizeof(char), compare);

    for (size_t i = 0; i < length - 1; ++i)
    {
        if (string[i] == string[i + 1])
            return 0;
    }
    return 1;
}

int solve(FILE *fp, int strlen)
{
    // prep the input
    char *line = NULL;
    size_t len;
    const ssize_t read = getline(&line, &len, fp);

    // parse the file
    int i = 0;
    while (i < read - strlen)
    {
        // build a copy of the string
        char *string = malloc(strlen * sizeof(char));
        for (size_t j = 0; j < strlen; ++j)
            string[j] = line[i + j];

        // check uniqueness
        if (unique(string, strlen))
        {
            free(string);
            return i + strlen;
        }

        // increment otherwise
        ++i;
        free(string);
    }
    return -1;
}

int main()
{
    FILE *fp = fopen("day06.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    printf("ONE: %d\n", solve(fp, 4));
    fseek(fp, 0, 0);
    printf("TWO: %d\n", solve(fp, 14));

    fclose(fp);
    return 0;
}