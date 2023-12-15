#include <advent.h>
#include <stdio.h>
#include <stdlib.h>

long* recurse(long* list, const size_t num)
{
    // base case -- list contains all zeros
    int empty = 1;
    for (size_t i = 0; i < num; ++i)
        empty &= list[i] == 0;
    if (empty)
        return list;

    // allocate memory to pass difference list to next iteration
    long* pass = malloc((num - 1) * sizeof(long));
    for (size_t i = 0; i < num - 1; ++i)
        pass[i] = list[i + 1] - list[i];
    const long* back = recurse(pass, num - 1);

    // append the first and last elements
    long* r = malloc((num + 2) * sizeof(long));
    for (size_t i = 0; i < num; ++i)
        r[i + 1] = list[i];
    r[0] = r[1] - back[0];
    r[num + 1] = r[num] + back[num];
    return r;
}

long* solve(FILE* fp)
{
    long* sol = calloc(2, sizeof(long));
    // get the data
    size_t num_lines, items;
    char** lines = readlines(fp, &num_lines);
    for (size_t i = 0; i < num_lines; ++i) {
        long* nums = longify(split(strip(lines[i]), " ", &items), items);
        const long* r = recurse(nums, items);
        sol[0] += r[0];
        sol[1] += r[items + 1];
        free(nums);
    }
    free(lines);
    return sol;
}

int main()
{
    FILE* fp = fopen("day09.txt", "r");
    if (!fp) {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    long* sol = solve(fp);
    printf("ONE: %ld\n", sol[1]);
    printf("TWO: %ld\n", sol[0]);

    free(sol);
    fclose(fp);
    return 0;
}
