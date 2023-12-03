#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char grid[142][142] = {0};

// get number from grid, replace with '.'
int getnumber(int x, int y)
{
    int result;
    while (isdigit(grid[x][y]))
        --y;
    result = strtol(grid[x] + (++y), NULL, 10);
    while (isdigit(grid[x][y]))
        grid[x][y++] = '.';
    return result;
}

// part 1 - get sum of all adjacent numbers
int getparts(int x, int y)
{

    int sum = 0;
    for (int j = x - 1; j < x + 2; ++j)
        for (int k = y - 1; k < y + 2; ++k)
            if (isdigit(grid[j][k]))
                sum += getnumber(j, k);
    return sum;
}

// part 2 - get sum of all gears, but multiply instead of add
int getgears(int x, int y)
{
    int nums = 0;
    int sum = 0;
    for (int j = x - 1; j < x + 2; ++j)
        for (int k = y - 1; k < y + 2; ++k)
            if (isdigit(grid[j][k]))
            {
                if (nums == 0)
                    sum += getnumber(j, k);
                else if (nums == 1)
                    sum *= getnumber(j, k);
                else if (nums == 2)
                    return 0;
                nums++;
            }
    if (nums == 1)
        return 0;
    return sum;
}

long one(FILE* fp)
{
    char buf[145];
    int x = 0;
    while (fgets(buf, 145, fp) != NULL)
    {
        buf[140] = '\0';
        strcpy(grid[++x] + 1, buf);
    }

    long one = 0;
	for (x = 1; x < 142; x++)
		for (int y = 1; y < 142; y++)
			if (grid[x][y] != '\0' && grid[x][y] != '.' && !isdigit(grid[x][y]))
				one += getparts(x, y);
	return one;
}

long two(FILE* fp)
{
    char buf[145];
    int x = 0;
    while (fgets(buf, 145, fp) != NULL)
    {
        buf[140] = '\0';
        strcpy(grid[++x] + 1, buf);
    }

    long two = 0;
	for (x = 1; x < 142; x++)
		for (int y = 1; y < 142; y++)
			if (grid[x][y] == '*')
				two += getgears(x, y);
	return two;
}

int main()
{
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("error opening file\n");
		return 1;
	}

    printf("ONE: %ld\n", one(fp));
    rewind(fp);
    printf("TWO: %ld\n", two(fp));
    fclose(fp);
    return 0;
}