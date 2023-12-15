#include <stdio.h>
#include <stdlib.h>

int one(FILE* fp)
{
    int c = 0, ll, lr, rl, rr;
    while (fscanf(fp, "%d-%d,%d-%d\n", &ll, &lr, &rl, &rr) != EOF) {
        if ((ll <= rl && lr >= rr) || (ll >= rl && lr <= rr))
            ++c;
    }
    return c;
}

int two(FILE* fp)
{
    int c = 0, ll, lr, rl, rr;
    while (fscanf(fp, "%d-%d,%d-%d\n", &ll, &lr, &rl, &rr) != EOF) {
        // get our count
        const int rl_shift = rr >= ll && rr <= lr;
        const int rr_shift = rl <= lr && rl >= ll;
        const int lr_shift = ll <= rr && ll >= rl;
        const int ll_shift = lr >= rl && lr <= rr;

        if (rl_shift || rr_shift || lr_shift || ll_shift)
            ++c;
    }
    return c;
}

int main()
{
    FILE* fp = fopen("day04.txt", "r");
    if (!fp) {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    printf("ONE: %d\n", one(fp));
    fseek(fp, 0, SEEK_SET);
    printf("TWO: %d\n", two(fp));
    fclose(fp);
    return 0;
}