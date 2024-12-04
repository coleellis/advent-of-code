// Inspiration: https://github.com/fuzesmarcell/aoc/blob/main/2023/day_02.c

#include <advent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Max
{
    int r;
    int g;
    int b;
} Max;

int one(FILE *fp)
{
    int  total = 0, n;
    char buf[128];

    // Get kv-pairs with colon
    while (fscanf(fp, "%s %d:", buf, &n) == 2)
    {
        const Max m = { 12, 13, 14 };
        int       i, x = 0;
        char      v[128];

        // Get kv-pairs
        while (fscanf(fp, "%d %s", &i, v) == 2)
        {
            int pass = 1;
            if (strstr(v, "red") != NULL && i > m.r)
                pass = 0;
            else if (strstr(v, "green") != NULL && i > m.g)
                pass = 0;
            else if (strstr(v, "blue") != NULL && i > m.b)
                pass = 0;

            if (!pass)
                ++x;
        }
        // X == 0 implies no failures this line
        if (x == 0)
            total += n;
    }
    return total;
}

int two(FILE *fp)
{
    int  total = 0, n;
    char buf[128];

    // Get pairs with colon after
    while (fscanf(fp, "%s %d:", buf, &n) == 2)
    {
        Max  m = { 0, 0, 0 };
        int  i;
        char v[128];
        // Get key/values
        while (fscanf(fp, "%d %s", &i, v) == 2)
        {
            // Find red/blue/green
            if (strstr(v, "red") != NULL && i > m.r)
                m.r = MAX(i, m.r);
            else if (strstr(v, "green") != NULL && i > m.g)
                m.g = MAX(i, m.g);
            else if (strstr(v, "blue") != NULL && i > m.b)
                m.b = MAX(i, m.b);
        }
        total += (m.r * m.g * m.b);
    }
    return total;
}

int main(void)
{
    FILE *fp = fopen("day02.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    printf("ONE: %d\n", one(fp));
    fseek(fp, 0, 0);
    printf("TWO: %d\n", two(fp));

    fclose(fp);
    return 0;
}
