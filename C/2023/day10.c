#include <advent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *fp = fopen("day10.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    // Printf("Part 1: %ld\n", solve(fp, 2));
    // Printf("Part 2: %ld\n", solve(fp, 1000000));

    fclose(fp);
    return 0;
}
