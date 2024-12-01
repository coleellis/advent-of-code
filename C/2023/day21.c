#include <advent.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int one(FILE* fp)
{
    return 0;
}

int two(FILE* fp)
{
    return 0;
}

int main()
{
    FILE* fp = fopen("day21.txt", "r");
    if (!fp) {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    printf("ONE: %d\n", one(fp));
    fseek(fp, 0, 0);
    printf("TWO: %d\n", two(fp));

    fclose(fp);
    return 0;
}
