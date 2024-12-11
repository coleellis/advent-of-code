#include <stdio.h>
#include <stdlib.h>

int one(FILE *fp)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // initialize array
    int totals[1000] = {0};
    uint16_t i = 0;
    uint32_t sum = 0;

    // read the file till no more lines
    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (read == 1)
        { // if blank line, store total
            totals[i] = sum;
            ++i;
            sum = 0;
        }
        else
        { // else, add to total
            sum += atoi(line);
        }
    }

    // get the max
    uint32_t max = 0;
    for (uint32_t j = 0; j < 1000; ++j)
    {
        if (totals[j] > max)
            max = totals[j];
    }
    if (line)
        free(line);

    return max;
}

int compare(const void *a, const void *b) { return (*(int *)b - *(int *)a); }

int two(FILE *fp)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // initialize array
    int totals[1000] = {0};
    uint16_t i = 0;
    uint32_t sum = 0;

    // read the file till no more lines
    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (read == 1)
        { // if blank line, store total
            totals[i] = sum;
            ++i;
            sum = 0;
        }
        else
        { // else, add to total
            sum += atoi(line);
        }
    }

    // sort the array
    qsort(totals, 1000, sizeof(int), compare);

    if (line)
        free(line);

    // print the sum of the top 3
    return totals[0] + totals[1] + totals[2];
}

int main()
{
    FILE *fp = fopen("day01.txt", "r");
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
