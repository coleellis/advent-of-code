#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) { return *(char *)a < *(char *)b; }

int one(FILE *fp)
{
    // prep the input
    char *line = NULL;
    ssize_t read;
    size_t len = 0;

    // get the input
    char *items = malloc(1000 * sizeof(char));
    uint16_t count = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        // populate the left
        char *left = malloc((read - 1) / 2 * sizeof(char));
        for (uint16_t i = 0; i < (read - 1) / 2; ++i)
            left[i] = line[i];

        // populate the right
        char *right = malloc((read - 1) / 2 * sizeof(char));
        for (uint16_t i = 0; i < (read - 1) / 2; ++i)
            right[i] = line[(read - 1) / 2 + i];

        // check for commonality
        for (uint32_t i = 0; i < (read - 1) / 2; ++i)
        {
            for (uint32_t j = 0; j < (read - 1) / 2; ++j)
            {
                if (left[i] == right[j])
                    items[count] = left[i];
            }
        }

        // inc counter
        ++count;

        // free memory
        if (left)
            free(left);
        if (right)
            free(right);
    }

    // get the total
    uint32_t total = 0;
    for (uint16_t i = 0; i < 1000; ++i)
    {
        if ((int)items[i] >= 0x61)
        {
            total += (((int)items[i] - 'a') + 1);
        }
        else if ((int)items[i] >= 0x41)
        {
            total += (((int)items[i] - 'A') + 27);
        }
    }
    free(items);
    return total;
}

int two(FILE *fp)
{
    // prep the input
    char *first = NULL;
    char *second = NULL;
    char *third = NULL;
    ssize_t f_read;
    size_t len = 0;

    // get the input
    char *items = malloc(1000 * sizeof(char));
    uint16_t count = 0;
    while ((f_read = getline(&first, &len, fp)) != -1)
    {
        // get the second and third lines
        const ssize_t s_read = getline(&second, &len, fp);
        const ssize_t t_read = getline(&third, &len, fp);

        // check for commonality
        for (uint16_t i = 0; i < f_read - 1; ++i)
        {
            for (uint16_t j = 0; j < s_read - 1; ++j)
            {
                for (uint16_t k = 0; k < t_read - 1; ++k)
                {
                    if (first[i] == second[j] && first[i] == third[k])
                    {
                        items[count] = first[i];
                    }
                }
            }
        }

        // inc counter
        ++count;
    }

    // get the total
    uint32_t total = 0;
    for (uint16_t i = 0; i < 1000; ++i)
    {
        if ((int)items[i] >= 0x61)
        {
            total += (((int)items[i] - 'a') + 1);
        }
        else if ((int)items[i] >= 0x41)
        {
            total += (((int)items[i] - 'A') + 27);
        }
    }
    free(items);
    return total;
}

int main()
{
    FILE *fp = fopen("day03.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }
    printf("ONE: %d\n", one(fp));
    fseek(fp, 0, 0);
    printf("TWO: %d\n", two(fp));
    return 0;
}