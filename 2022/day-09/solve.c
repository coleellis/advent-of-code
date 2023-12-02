#include <stdio.h>
#include <stdlib.h>

typedef struct Point
{
    int x;
    int y;
} Point;
Point Point_default = {0, 0};

typedef struct Vector
{
    int x;
    int y;
} Vector;

Vector build_vector(struct Point head, struct Point tail)
{
    Vector *ret = malloc(sizeof(Vector));
    ret->x = head.x - tail.x;
    ret->y = head.y - tail.y;
    return *ret;
}

int compare(const void *a, const void *b)
{
    Point const *first = (Point *)a;
    Point const *second = (Point *)b;

    if (first->x < second->x)
        return -1;
    else if (first->x > second->x)
        return 1;
    else
    {
        if (first->y < second->y)
            return -1;
        if (first->y > second->y)
            return 1;
        else
            return 0;
    }
}

int toInt(char first, char second)
{
    char *string = malloc(2 * sizeof(char));
    string[0] = first;
    if (string[1] != '\n')
        string[1] = second;
    return atoi(string);
}

int equal(Point a, Point b) { return (a.x == b.x && a.y == b.y); }

int one(FILE *fp)
{
    char *line = NULL;
    size_t len = 0;

    // head and tail positions
    Point head = Point_default;
    Point tail = Point_default;

    // list of points
    Point *tail_visits = malloc(20000 * sizeof(Point));

    // read the directional changes
    size_t count = 0;
    while (getline(&line, &len, fp) != -1)
    {
        int times = toInt(line[2], line[3]);
        while (times-- > 0)
        {
            // adjust the head coordinate
            if (line[0] == 'U')
                ++head.y;
            else if (line[0] == 'D')
                --head.y;
            else if (line[0] == 'L')
                --head.x;
            else if (line[0] == 'R')
                ++head.x;
            else
            {
                printf("Bad\n");
                exit(EXIT_FAILURE);
            }
            // build the vector
            Vector distance = build_vector(head, tail);

            // adjust tail location based on vector
            if (distance.x == 2)
            {
                ++tail.x;
                if (distance.y == 1)
                    ++tail.y;
                if (distance.y == -1)
                    --tail.y;
            }
            if (distance.x == -2)
            {
                --tail.x;
                if (distance.y == 1)
                    ++tail.y;
                if (distance.y == -1)
                    --tail.y;
            }
            if (distance.y == 2)
            {
                ++tail.y;
                if (distance.x == 1)
                    ++tail.x;
                if (distance.x == -1)
                    --tail.x;
            }
            if (distance.y == -2)
            {
                --tail.y;
                if (distance.x == 1)
                    ++tail.x;
                if (distance.x == -1)
                    --tail.x;
            }

            // record location in list
            tail_visits[count++] = tail;
        }
    }

    // sort the list of points
    qsort(tail_visits, count, sizeof(Point), compare);

    // count non-duplicates
    int visited = 1;
    for (size_t i = 1; i < count; ++i)
    {
        if (!equal(tail_visits[i], tail_visits[i - 1]))
        {
            ++visited;
        }
    }

    return visited;
}

Point adjust(Point head, Point tail)
{
    Vector distance = build_vector(head, tail);

    // adjust tail location based on vector
    if (distance.x == 2)
    {
        ++tail.x;
        if (distance.y == 1)
            ++tail.y;
        if (distance.y == -1)
            --tail.y;
    }
    if (distance.x == -2)
    {
        --tail.x;
        if (distance.y == 1)
            ++tail.y;
        if (distance.y == -1)
            --tail.y;
    }
    if (distance.y == 2)
    {
        ++tail.y;
        if (distance.x == 1)
            ++tail.x;
        if (distance.x == -1)
            --tail.x;
    }
    if (distance.y == -2)
    {
        --tail.y;
        if (distance.x == 1)
            ++tail.x;
        if (distance.x == -1)
            --tail.x;
    }

    return tail;
}

int two(FILE *fp)
{
    char *line = NULL;
    size_t len = 0;

    // build the chain
    Point *chain = malloc(10 * sizeof(Point));
    for (size_t i = 0; i < 10; ++i)
        chain[i] = Point_default;

    // list of points
    Point *tail_visits = malloc(20000 * sizeof(Point));

    // read the directional changes
    size_t count = 0;
    while (getline(&line, &len, fp) != -1)
    {
        int times = toInt(line[2], line[3]);
        while (times-- > 0)
        {
            // adjust the head coordinate
            if (line[0] == 'U')
                ++chain[0].y;
            else if (line[0] == 'D')
                --chain[0].y;
            else if (line[0] == 'L')
                --chain[0].x;
            else if (line[0] == 'R')
                ++chain[0].x;
            else
            {
                printf("Bad\n");
                exit(EXIT_FAILURE);
            }

            // adjust the links of the chain
            for (size_t i = 0; i < 9; ++i)
                chain[i + 1] = adjust(chain[i], chain[i + 1]);

            // record tail location in list
            tail_visits[count++] = chain[9];
        }
    }

    // sort the list of points
    qsort(tail_visits, count, sizeof(Point), compare);

    // count non-duplicates
    int visited = 1;
    for (size_t i = 1; i < count; ++i)
    {
        if (!equal(tail_visits[i], tail_visits[i - 1]))
        {
            ++visited;
        }
    }

    return visited;
}

int main()
{
    FILE *fp = fopen("input.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    printf("ONE: %d\n", one(fp));
    fseek(fp, 0, 0);
    printf("TWO: %d\n", two(fp));

    fclose(fp);
    return EXIT_SUCCESS;
}