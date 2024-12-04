#include <stdio.h>
#include <stdlib.h>

int one(FILE *fp)
{
    size_t len;
    char  *line = NULL;

    size_t cycles = 1;      // Cycle counter
    int    keys[6] = { 0 }; // Holds strengths at indices
    int    X = 1;           // Register value of X
    while (getline(&line, &len, fp) != -1)
    {
        // Check cycles
        ++cycles;
        if (cycles == 20 || cycles == 60 || cycles == 100 || cycles == 140 || cycles == 180
            || cycles == 220)
            keys[(cycles - 20) / 40] = (cycles * X);

        if (line[0] == 'n')
            continue;

        // Finally finish operation
        char *toInt = malloc(4 * sizeof(char));
        for (int i = 5; line[i] != '\n'; ++i)
            toInt[i - 5] = line[i];
        X += atoi(toInt);

        // Let another cycle go by
        ++cycles;
        if (cycles == 20 || cycles == 60 || cycles == 100 || cycles == 140 || cycles == 180
            || cycles == 220)
            keys[(cycles - 20) / 40] = (cycles * X);
    }

    return keys[0] + keys[1] + keys[2] + keys[3] + keys[4] + keys[5];
}

void two(FILE *fp)
{
    size_t len;
    char  *line = NULL;

    size_t cycles = 1;          // Cycle counter
    int    X = 1;               // Register value of X
    char   lights[240] = { 0 }; // Array of lights
    while (getline(&line, &len, fp) != -1)
    {
        int position = (cycles - 1) % 40;
        // Check cycles
        if (abs(X - position) <= 1)
            lights[cycles - 1] = '#';
        else
            lights[cycles - 1] = '.';
        ++cycles;
        ++position;

        if (line[0] == 'n')
            continue;

        // Let another cycle go by
        if (abs(X - position) <= 1)
            lights[cycles - 1] = '#';
        else
            lights[cycles - 1] = '.';
        ++cycles;
        ++position;

        // Finally finish operation
        char *toInt = malloc(4 * sizeof(char));
        for (int i = 5; line[i] != '\n'; ++i)
            toInt[i - 5] = line[i];
        X += atoi(toInt);
    }

    printf("\n");
    for (size_t i = 0; i < 6; ++i)
    {
        for (size_t j = 0; j < 40; ++j)
        {
            printf("%c", lights[40 * i + j]);
        }
        printf("\n");
    }
}

int main(void)
{
    FILE *fp = fopen("day10.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }

    printf("ONE: %d\n", one(fp));
    fseek(fp, 0, 0);
    printf("TWO:");
    two(fp);

    fclose(fp);
    return EXIT_SUCCESS;
}
