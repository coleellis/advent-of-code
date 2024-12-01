#include <stdio.h>
#include <stdlib.h>

long one(const char* s)
{
}

int main()
{
    FILE* fp = fopen("day01.txt", "r");
    if (!fp) {
        printf("Can't open file\n");
        return 1;
    }

    char* s = NULL;
    size_t l = 0;
    getline(&s, &l, fp);
    return 0;
}