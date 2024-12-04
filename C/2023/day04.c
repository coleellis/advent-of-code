#include <advent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t  nlines = 0;
char ***vert = NULL;
char ***winning = NULL;
char ***given = NULL;
size_t  n_given = 0, n_win = 0;

void get_data(FILE *fp)
{
    char **lines = readlines(fp, &nlines);
    vert = malloc(nlines * sizeof(char **));
    winning = malloc(nlines * sizeof(char **));
    given = malloc(nlines * sizeof(char **));

    for (size_t n = 0; n < nlines; ++n)
    {
        vert[n] = split(lines[n], "|", NULL);
        winning[n] = split(strip(split(vert[n][0], ":", NULL)[1]), " ", &n_win);
        given[n] = split(strip(vert[n][1]), " ", &n_given);
    }

    free(lines);
}

void free_data(void)
{
    for (size_t n = 0; n < nlines; ++n)
    {
        free(vert[n]);
        free(winning[n]);
        free(given[n]);
    }
    free(vert);
    free(winning);
    free(given);
}

int one(void)
{
    int one = 0;
    for (size_t n = 0; n < nlines; ++n)
    {
        int    card = 0;
        char **w = winning[n], **g = given[n];
        for (size_t i = 0; i < n_given; ++i)
        {
            for (size_t j = 0; j < n_win; ++j)
            {
                if (g[i] && w[j] && strcmp(g[i], w[j]) == 0)
                {
                    card = (card == 0) ? 1 : card * 2;
                    break;
                }
            }
        }
        one += card;
    }
    return one;
}

int two(void)
{
    // Make an array of card counts
    int *cards = malloc(nlines * sizeof(int));
    for (size_t i = 0; i < nlines; ++i)
        cards[i] = 1;

    int two = 0;
    for (size_t n = 0; n < nlines; ++n)
    {
        int    card = 0;
        char **w = winning[n], **g = given[n];
        for (size_t i = 0; i < n_given; i++)
        {
            for (size_t j = 0; j < n_win; j++)
            {
                if (g[i] && w[j] && strcmp(g[i], w[j]) == 0)
                    card += 1;
            }
        }
        // Add number of matches to next cards in line
        for (int i = 0; i < card; ++i)
            cards[n + i + 1] += cards[n];
    }

    for (size_t i = 0; i < nlines; ++i)
        two += cards[i];

    free(cards);
    return two;
}

int main(void)
{
    FILE *fp = fopen("day04.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    get_data(fp);
    printf("ONE: %d\n", one());
    printf("TWO: %d\n", two());

    free_data();
    fclose(fp);
    return 0;
}
