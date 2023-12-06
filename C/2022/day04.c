#include <stdio.h>
#include <stdlib.h>

int one(FILE *fp)
{
    // prep the read
    char *line = NULL;
    size_t len = 0;

    // read
    int count = 0;
    while (getline(&line, &len, fp) != -1)
    {
        size_t i = 0;
        size_t j = 0;

        // populate left-left
        char *left_left = malloc(len * sizeof(char));
        while (line[i] != '-')
        {
            left_left[j] = line[i];
            ++i;
            ++j;
        }
        int l_first = atoi(left_left);
        j = 0;
        ++i;

        // populate left-left
        char *left_right = malloc(len * sizeof(char));
        while (line[i] != ',')
        {
            left_right[j] = line[i];
            ++i;
            ++j;
        }
        int l_second = atoi(left_right);
        j = 0;
        ++i;

        // populate left-left
        char *right_left = malloc(len * sizeof(char));
        while (line[i] != '-')
        {
            right_left[j] = line[i];
            ++i;
            ++j;
        }
        int r_first = atoi(right_left);
        j = 0;
        ++i;

        // populate left-left
        char *right_right = malloc(len * sizeof(char));
        while (line[i] != '\n')
        {
            right_right[j] = line[i];
            ++i;
            ++j;
        }
        int r_second = atoi(right_right);

        // get our count
        if ((l_first <= r_first && l_second >= r_second) ||
            (l_first >= r_first && l_second <= r_second))
            ++count;
    }
    return count;
}

int two(FILE *fp)
{
    // prep the read
    char *line = NULL;
    size_t len = 0;

    // read
    size_t count = 0;
    while (getline(&line, &len, fp) != -1)
    {
        size_t i = 0;
        size_t j = 0;

        // populate left-left
        char *left_left = malloc(len * sizeof(char));
        while (line[i] != '-')
        {
            left_left[j] = line[i];
            ++i;
            ++j;
        }
        int l_first = atoi(left_left);
        j = 0;
        ++i;

        // populate left-left
        char *left_right = malloc(len * sizeof(char));
        while (line[i] != ',')
        {
            left_right[j] = line[i];
            ++i;
            ++j;
        }
        int l_second = atoi(left_right);
        j = 0;
        ++i;

        // populate left-left
        char *right_left = malloc(len * sizeof(char));
        while (line[i] != '-')
        {
            right_left[j] = line[i];
            ++i;
            ++j;
        }
        int r_first = atoi(right_left);
        j = 0;
        ++i;

        // populate left-left
        char *right_right = malloc(len * sizeof(char));
        while (line[i] != '\n')
        {
            right_right[j] = line[i];
            ++i;
            ++j;
        }
        int r_second = atoi(right_right);

        // get our count
        int rl_shift = r_second >= l_first && r_second <= l_second;
        int rr_shift = r_first <= l_second && r_first >= l_first;
        int lr_shift = l_first <= r_second && l_first >= r_first;
        int ll_shift = l_second >= r_first && l_second <= r_second;

        if (rl_shift || rr_shift || lr_shift || ll_shift)
            ++count;
        free(left_left);
        free(right_left);
        free(left_right);
        free(right_right);
    }
    return count;
}

int main()
{
    FILE *fp = fopen("day04.txt", "r");
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