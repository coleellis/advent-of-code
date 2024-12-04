#include <advent.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char k[4];
    char l[4];
    char r[4];
} Node;

char  *generator = NULL;
Node  *tree      = NULL;
size_t e         = 0;

Node *get(const char *k)
{
    size_t i = 0;
    while (i < e && strcmp(tree[i].k, k) != 0)
        ++i;
    return i < e ? &tree[i] : NULL;
}

void build_tree(FILE *fp)
{
    // Get generator
    generator = malloc(1000 * sizeof(char));
    fscanf(fp, "%s\n\n", generator);
    generator = realloc(generator, strlen(generator) * sizeof(char));

    // Get tree items
    tree  = malloc(1000 * sizeof(Node));
    int i = 0;
    while (fscanf(fp, " %[^ ] = (%[^,], %[^)])\n", tree[i].k, tree[i].l, tree[i].r) == 3)
        ++i;
    tree = realloc(tree, i * sizeof(Node));
    if (!tree)
        exit(EXIT_FAILURE);
    e = i;
}

long parse(char **s, long l)
{
    // Make a map of successes
    long f = 0, idx = 0;
    long k[l];

    while (f != l)
    {
        // For each item, send it left or right (or mark it successful)
        for (long i = 0; i < l; ++i)
        {
            if (s[i][strlen(s[i]) - 1] == 'Z')
                k[f++] = idx;
            if (generator[idx % strlen(generator)] == 'R')
                s[i] = get(s[i])->r;
            else if (generator[idx % strlen(generator)] == 'L')
                s[i] = get(s[i])->l;
            else
            {
                printf("Bad character in generator: %c\n", generator[idx % strlen(generator)]);
                exit(EXIT_FAILURE);
            }
        }
        ++idx;
    }

    return lcm(k, l);
}

int main(void)
{
    FILE *fp = fopen("day08.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    build_tree(fp);

    // Part 1 - start at just AAA
    char *f[1] = { "AAA" };
    printf("ONE: %ld\n", parse(f, 1));

    // Part 2 - start at all items ending in A
    size_t i   = 0;
    char **two = malloc(e * sizeof(char *));
    for (size_t j = 0; j < e; ++j)
    {
        if (tree[j].k[2] == 'A')
            two[i++] = tree[j].k;
    }
    two = realloc(two, i * sizeof(char *));
    if (!two)
        exit(EXIT_FAILURE);
    printf("TWO: %ld\n", parse(two, i));

    free(generator);
    free(tree);
    fclose(fp);
    return 0;
}
