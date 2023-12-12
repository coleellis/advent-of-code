#include <stdio.h>
#include <stdlib.h>

char *one(FILE *fp)
{
    // prep the input
    char *line = NULL;
    ssize_t read;
    size_t len = 0;

    // read until the newline
    size_t des_line = 0;
    int num_stacks = 0;
    while ((read = getline(&line, &len, fp)) != 1)
    {
        // our desired line guaranteed starts with a space
        if (line[0] == ' ')
        {
            // get the number of stacks
            size_t num_idx = 0;
            char *num = malloc(3 * sizeof(char));
            for (size_t idx = read - 2; line[idx] != ' '; --idx)
                num[num_idx++] = line[idx];
            num_stacks = atoi(num);
            break;
        }
        else
        {
            ++des_line;
        }
    }

    // this resets the file to start reading from the beginning
    fseek(fp, 0, 0);

    // allocate the storage
    char **stacks = malloc(num_stacks * sizeof(char *));
    for (size_t i = 0; i < num_stacks; ++i)
    {
        stacks[i] = malloc(100 * sizeof(char));
    }
    size_t *size = malloc(9 * sizeof(size_t));

    // now read the first 8 lines and get the data
    size_t line_num = 0;
    while (line_num != des_line)
    {
        // get the line
        read = getline(&line, &len, fp);

        // read across the line looking for chars
        for (size_t i = 0; i < read; ++i)
        {
            if (line[i] >= 'A' && line[i] <= 'Z')
                stacks[i / 4][size[i / 4]++] = line[i];
        }

        ++line_num;
    }

    // we put them in backwards, reverse the lists
    for (size_t i = 0; i < num_stacks; ++i)
    {
        char *rev_stack = malloc(100 * sizeof(char));
        for (size_t j = 0; j <= size[i]; ++j)
            rev_stack[j] = stacks[i][size[i] - j - 1];
        free(stacks[i]);
        stacks[i] = rev_stack;
        free(rev_stack);
    }

    // push the line twice to get to the right spot
    getline(&line, &len, fp);
    getline(&line, &len, fp);

    // now we need to parse the rest of the lines
    while (getline(&line, &len, fp) != -1)
    {
        // move to first number
        size_t idx;
        for (idx = 1; line[idx - 1] != ' '; ++idx)
            ;

        // get first number
        size_t num_idx = 0;
        char *num = malloc(3 * sizeof(char));
        for (; line[idx] != ' '; ++idx)
            num[num_idx++] = line[idx];
        const size_t moving = atoi(num);

        // move to second
        idx += 2;
        for (; line[idx - 1] != ' '; ++idx)
            ;

        // get second number
        num_idx = 0;
        num = malloc(3 * sizeof(char));
        for (; line[idx] != ' '; ++idx)
            num[num_idx++] = line[idx];
        const size_t origin = atoi(num) - 1;

        // move to third
        idx += 2;
        for (; line[idx - 1] != ' '; ++idx)
            ;

        // get third number
        num_idx = 0;
        num = malloc(3 * sizeof(char));
        for (; line[idx] != '\n'; ++idx)
            num[num_idx++] = line[idx];
        const size_t destination = atoi(num) - 1;

        // perform the action
        for (size_t action = 0; action < moving; ++action)
        {
            stacks[destination][size[destination]++] =
                stacks[origin][(size[origin]--) - 1];
        }
    }

    // store top stacks in return
    char *ret = malloc(num_stacks * sizeof(char));
    for (size_t i = 0; i < num_stacks; ++i)
        ret[i] = stacks[i][size[i] - 1];

    // clear the memory
    for (size_t i = 0; i < num_stacks; ++i)
        free(stacks[i]);
    free(stacks);
    free(size);

    return ret;
}

char *two(FILE *fp)
{
    // prep the input
    char *line = NULL;
    ssize_t read;
    size_t len = 0;

    // read until the newline
    size_t des_line = 0;
    int num_stacks = 0;
    while ((read = getline(&line, &len, fp)) != 1)
    {
        // our desired line guaranteed starts with a space
        if (line[0] == ' ')
        {
            // get the number of stacks
            size_t num_idx = 0;
            char *num = malloc(3 * sizeof(char));
            for (size_t idx = read - 2; line[idx] != ' '; --idx)
                num[num_idx++] = line[idx];
            num_stacks = atoi(num);
            break;
        }
        ++des_line;
    }

    // this resets the file to start reading from the beginning
    fseek(fp, 0, 0);

    // allocate the storage
    char **stacks = malloc(num_stacks * sizeof(char *));
    for (size_t i = 0; i < num_stacks; ++i)
    {
        stacks[i] = malloc(100 * sizeof(char));
    }
    size_t *size = malloc(9 * sizeof(size_t));

    // now read the first 8 lines and get the data
    size_t line_num = 0;
    while (line_num != des_line)
    {
        // get the line
        read = getline(&line, &len, fp);

        // read across the line looking for chars
        for (size_t i = 0; i < read; ++i)
        {
            if (line[i] >= 'A' && line[i] <= 'Z')
                stacks[i / 4][size[i / 4]++] = line[i];
        }

        ++line_num;
    }

    // we put them in backwards, reverse the lists
    for (size_t i = 0; i < num_stacks; ++i)
    {
        char *rev_stack = malloc(100 * sizeof(char));
        for (size_t j = 0; j <= size[i]; ++j)
            rev_stack[j] = stacks[i][size[i] - j - 1];
        free(stacks[i]);
        stacks[i] = rev_stack;
        free(rev_stack);
    }

    // push the line twice to get to the right spot
    getline(&line, &len, fp);
    getline(&line, &len, fp);

    // now we need to parse the rest of the lines
    while (getline(&line, &len, fp) != -1)
    {
        // move to first number
        size_t idx;
        for (idx = 1; line[idx - 1] != ' '; ++idx)
            ;

        // get first number
        size_t num_idx = 0;
        char *num = malloc(3 * sizeof(char));
        for (; line[idx] != ' '; ++idx)
            num[num_idx++] = line[idx];
        const size_t moving = atoi(num);

        // move to second
        idx += 2;
        for (; line[idx - 1] != ' '; ++idx)
            ;

        // get second number
        num_idx = 0;
        num = malloc(3 * sizeof(char));
        for (; line[idx] != ' '; ++idx)
            num[num_idx++] = line[idx];
        const size_t origin = atoi(num) - 1;

        // move to third
        idx += 2;
        for (; line[idx - 1] != ' '; ++idx)
            ;

        // get third number
        num_idx = 0;
        num = malloc(3 * sizeof(char));
        for (; line[idx] != '\n'; ++idx)
            num[num_idx++] = line[idx];
        const size_t destination = atoi(num) - 1;

        // perform the action
        for (size_t action = 0; action < moving; ++action)
        {
            stacks[destination][size[destination]++] =
                stacks[origin][(size[origin] - moving) + action];
        }
        size[origin] -= moving;
    }

    // store top stacks in return
    char *ret = malloc(num_stacks * sizeof(char));
    for (size_t i = 0; i < num_stacks; ++i)
        ret[i] = stacks[i][size[i] - 1];

    // clear the memory
    for (size_t i = 0; i < num_stacks; ++i)
        free(stacks[i]);
    free(stacks);
    free(size);

    return ret;
}

int main()
{
    FILE *fp = fopen("day05.txt", "r");
    if (!fp)
    {
        printf("Bad file read\n");
        exit(EXIT_FAILURE);
    }
    printf("ONE: %s\n", one(fp));
    fseek(fp, 0, 0);
    printf("TWO: %s\n", two(fp));
    return 0;
}