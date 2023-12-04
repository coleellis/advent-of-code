#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <advent.h>

int one(FILE *fp)
{
	char *line = NULL;
	size_t len = 0;
	int one = 0;
	while (getline(&line, &len, fp) != -1)
	{
		int card = 0;
		size_t n_given = 0, n_win = 0;
		char **vert = split(line, "|", NULL);
		char **winning = split(strip(split(vert[0], ":", NULL)[1]), " ", &n_win);
		char **given = split(strip(vert[1]), " ", &n_given);
		for (size_t i = 0; i < n_given; i++)
		{
			for (size_t j = 0; j < n_win; j++)
			{
				if (given[i] && winning[j] && strcmp(given[i], winning[j]) == 0)
				{
					card = (card == 0) ? 1 : card * 2;
					break;
				}
			}
		}
		one += card;
		free(vert);
		free(given);
		free(winning);
	}
	if (line)
		free(line);
	return one;
}

int two(FILE *fp)
{
	char *line = NULL;
	size_t len = 0;
	int two = 0, l_num = 0, t_num = 0;
	// get number of lines
	while (getline(&line, &len, fp) != -1)
		++t_num;
	fseek(fp, 0, 0);

	// make an array of card counts
	int *cards = malloc(t_num * sizeof(int));
	for (int i = 0; i < t_num; i++)
		cards[i] = 1;

	while (getline(&line, &len, fp) != -1)
	{
		int card = 0;
		size_t n_given = 0, n_win = 0;
		char **vert = split(line, "|", NULL);
		char **winning = split(strip(split(vert[0], ":", NULL)[1]), " ", &n_win);
		char **given = split(strip(vert[1]), " ", &n_given);
		for (size_t i = 0; i < n_given; i++)
		{
			for (size_t j = 0; j < n_win; j++)
			{
				if (given[i] && winning[j] && strcmp(given[i], winning[j]) == 0)
					card += 1;
			}
		}
		// add number of matches to next cards in line
		for (size_t i = 0; i < card; ++i)
			cards[l_num + i + 1] += cards[l_num];

		free(vert);
		free(given);
		free(winning);
		++l_num;
	}
	if (line)
		free(line);

	for (size_t i = 0; i < t_num; ++i)
		two += cards[i];

	free(cards);
	return two;
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
