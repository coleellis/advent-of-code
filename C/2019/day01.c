#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = fopen("day01.txt", "r");
    if (!fp)
    {
        printf("Can't open file\n");
        return 1;
    }
    return 0;
}
