#include <stdio.h>
#include <stdlib.h>

typedef struct Point
{
    int x;
    int y;
} Point;
Point Point_default = { 0, 0 };

typedef struct Vector
{
    int x;
    int y;
} Vector;

Vector build_vector(const Point head, const Point tail)
{
    Vector *ret = malloc(sizeof(Vector));
    ret->x      = head.x - tail.x;
    ret->y      = head.y - tail.y;
    return *ret;
}

int compare(const void *a, const void *b)
{
    Point const *first  = (Point *)a;
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

int toInt(const char first, const char second)
{
    char *string = calloc(2, sizeof(char));
    string[0]    = first;
    string[1]    = second;
    int ret      = atoi(string);
    free(string);
    return ret;
}

int equal(const Point a, const Point b)
{
    return (a.x == b.x && a.y == b.y);
}

int one(FILE *fp)
{
    char  *line = NULL;
    size_t len  = 0;

    // Head and tail positions
    Point head = Point_default;
    Point tail = Point_default;

    // List of points
    Point *tail_visits = malloc(20000 * sizeof(Point));

    // Read the directional changes
    size_t count = 0;
    while (getline(&line, &len, fp) != -1)
    {
        int times = toInt(line[2], line[3]);
        while (times-- > 0)
        {
            // Adjust the head coordinate
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
            // Build the vector
            const Vector distance = build_vector(head, tail);

            // Adjust tail location based on vector
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

            // Record location in list
            tail_visits[count++] = tail;
        }
    }

    // Sort the list of points
    qsort(tail_visits, count, sizeof(Point), compare);

    // Count non-duplicates
    int visited = 1;
    for (size_t i = 1; i < count; ++i)
    {
        if (!equal(tail_visits[i], tail_visits[i - 1]))
        {
            ++visited;
        }
    }

    // Free memory
    free(tail_visits);
    if (line)
        free(line);

    return visited;
}

Point adjust(const Point head, Point tail)
{
    const Vector distance = build_vector(head, tail);

    // Adjust tail location based on vector
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
    char  *line = NULL;
    size_t len  = 0;

    // Build the chain
    Point *chain = malloc(10 * sizeof(Point));
    for (size_t i = 0; i < 10; ++i)
        chain[i] = Point_default;

    // List of points
    Point *tail_visits = malloc(20000 * sizeof(Point));

    // Read the directional changes
    size_t count = 0;
    while (getline(&line, &len, fp) != -1)
    {
        int times = toInt(line[2], line[3]);
        while (times-- > 0)
        {
            // Adjust the head coordinate
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

            // Adjust the links of the chain
            for (size_t i = 0; i < 9; ++i)
                chain[i + 1] = adjust(chain[i], chain[i + 1]);

            // Record tail location in list
            tail_visits[count++] = chain[9];
        }
    }

    // Sort the list of points
    tail_visits = realloc(tail_visits, count * sizeof(Point));
    qsort(tail_visits, count, sizeof(Point), compare);

    // Count non-duplicates
    int visited = 1;
    for (size_t i = 1; i < count; ++i)
    {
        if (!equal(tail_visits[i], tail_visits[i - 1]))
        {
            ++visited;
        }
    }

    // Free memory
    free(chain);
    free(tail_visits);
    if (line)
        free(line);

    return visited;
}

int main(void)
{
    // Get input file
    FILE *fp = fopen("day09.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    // Both parts
    printf("ONE: %d\n", one(fp));
    fseek(fp, 0, 0);
    printf("TWO: %d\n", two(fp));

    fclose(fp);
    return EXIT_SUCCESS;
}
