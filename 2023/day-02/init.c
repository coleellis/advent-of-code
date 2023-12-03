#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct max
{
    int red;
    int green;
    int blue;
} Max;

int one(FILE *fp)
{
    char *line = NULL;
    size_t len;
    char *colonPtr, *lhsPtr, *semiPtr, *commaPtr, *spacePtr;
    Max maxes = {12, 13, 14};

    int total = 0;
    while (getline(&line, &len, fp) != -1)
    {
        int x = 0;
        char *stripped = strtok(line, "\n");

        // get game number
        char *n = strtok_r(stripped, ":", &colonPtr);
        strtok_r(n, " ", &lhsPtr);
        n = strtok_r(NULL, " ", &lhsPtr);

        // get list of turns
        char *t = strtok_r(NULL, ":", &colonPtr);
        // iterate through all turns
        char *e = strtok_r(t, ";", &semiPtr);
        while (e != NULL)
        {
            // for each enum, check the letters
            char *c = strtok_r(e, ",", &commaPtr);
            while (c != NULL)
            {
                // get key value
                char const *i = strtok_r(c, " ", &spacePtr);
                char const *v = strtok_r(NULL, " ", &spacePtr);

                // check if conditions are met
                int pass = 1;
                if (strcmp(v, "red") == 0 && atoi(i) > maxes.red)
                    pass = 0;
                else if (strcmp(v, "green") == 0 && atoi(i) > maxes.green)
                    pass = 0;
                else if (strcmp(v, "blue") == 0 && atoi(i) > maxes.blue)
                    pass = 0;

                if (!pass)
                    ++x;

                c = strtok_r(NULL, ",", &commaPtr);
            }
            e = strtok_r(NULL, ";", &semiPtr);
        }

        // if x==0, all passed, add to total
        if (x == 0)
            total += atoi(n);
    }
    return total;
}

int two(FILE *fp)
{
    char *line = NULL;
    size_t len;
    char *colonPtr, *semiPtr, *commaPtr, *spacePtr;

    int total = 0;
    while (getline(&line, &len, fp) != -1)
    {
        Max maxes = {0, 0, 0};
        char *stripped = strtok(line, "\n");
        // get game number
        strtok_r(stripped, ":", &colonPtr);

        // get list of turns
        char *t = strtok_r(NULL, ":", &colonPtr);
        // iterate through all turns
        char *e = strtok_r(t, ";", &semiPtr);
        while (e != NULL)
        {
            // for each enum, check the letters
            char *c = strtok_r(e, ",", &commaPtr);
            while (c != NULL)
            {
                // get key value
                char const *i = strtok_r(c, " ", &spacePtr);
                char const *v = strtok_r(NULL, " ", &spacePtr);

                // get the power
                if (strcmp(v, "red") == 0)
                    maxes.red = atoi(i) > maxes.red ? atoi(i) : maxes.red;
                else if (strcmp(v, "green") == 0)
                    maxes.green = atoi(i) > maxes.green ? atoi(i) : maxes.green;
                else if (strcmp(v, "blue") == 0)
                    maxes.blue = atoi(i) > maxes.blue ? atoi(i) : maxes.blue;

                c = strtok_r(NULL, ",", &commaPtr);
            }
            e = strtok_r(NULL, ";", &semiPtr);
        }

        total += (maxes.blue * maxes.green * maxes.red);
    }
    return total;
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
    return 0;
}