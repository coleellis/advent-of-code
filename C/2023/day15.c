#include <advent.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** items;
size_t nitems;

typedef struct Item {
    char* k;
    int v;
    struct Item* n;
} Item;

void inode(Item** list, const Item item)
{
    Item* head = *list;
    if (!head) {
        head = malloc(sizeof(Item));
        *head = item;
        *list = head;
        return;
    }
    while (head->n != NULL) {
        if (strcmp(head->k, item.k) == 0) {
            head->v = item.v;
            return;
        }
        head = head->n;
    }
    if (strcmp(head->k, item.k) == 0) {
        head->v = item.v;
        return;
    }
    head->n = malloc(sizeof(Item));
    *(head->n) = item;
}

void rnode(Item** list, const char* k)
{
    Item* head = *list;
    if (!head)
        return;
    if (strcmp(head->k, k) == 0) {
        *list = head->n;
        free(head);
        return;
    }
    while (head->n != NULL) {
        if (strcmp(head->n->k, k) == 0) {
            Item* tmp = head->n;
            head->n = head->n->n;
            free(tmp);
            return;
        }
        head = head->n;
    }
}

int hash(const char* s)
{
    int r = 0;
    for (size_t i = 0; i < strlen(s); ++i) {
        r += (int)s[i];
        r *= 17;
        r %= 256;
    }
    return r;
}

void get_data(FILE* fp)
{
    size_t n = 0;
    char* line = NULL;
    getline(&line, &n, fp);
    items = split(line, ",", &nitems);
}

int one()
{
    int r = 0;
    for (size_t i = 0; i < nitems; ++i)
        r += hash(items[i]);
    return r;
}

int two()
{
    Item* m[256] = { NULL };
    for (size_t i = 0; i < nitems; ++i) {
        if (indexOf(items[i], '-') != -1) {
            const char* tmp = split(items[i], "-", NULL)[0];
            const int hh = hash(tmp);
            rnode(&m[hh], tmp);
        } else {
            char** tmp = split(items[i], "=", NULL);
            const int hh = hash(tmp[0]);
            const Item it = (Item) { tmp[0], atoi(tmp[1]), NULL };
            inode(&m[hh], it);
        }
    }

    int r = 0;
    for (size_t i = 0; i < 256; ++i) {
        const Item* head = m[i];
        size_t j = 0;
        while (head != NULL) {
            r += (i + 1) * (j + 1) * head->v;
            head = head->n;
            ++j;
        }
    }

    return r;
}

int main()
{
    FILE* fp = fopen("day15.txt", "r");
    if (!fp) {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    get_data(fp);
    printf("Part 1: %d\n", one());
    printf("Part 2: %d\n", two());

    free(items);
    fclose(fp);
    return 0;
}
