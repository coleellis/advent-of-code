#include <stdio.h>
#include <stdlib.h>

char *one(FILE *fp)
{
    // Prep the input
    char   *line = NULL;
    ssize_t read;
    size_t  len = 0;

    // Read until the newline
    size_t des_line   = 0;
    int    num_stacks = 0;
    while ((read = getline(&line, &len, fp)) != 1)
    {
        // Our desired line guaranteed starts with a space
        if (line[0] == ' ')
        {
            // Get the number of stacks
            size_t num_idx = 0;
            char  *num     = malloc(3 * sizeof(char));
            for (int idx = read - 2; line[idx] != ' '; --idx)
                num[num_idx++] = line[idx];
            num_stacks = atoi(num);
            break;
        }
        else
        {
            ++des_line;
        }
    }

    // This resets the file to start reading from the beginning
    fseek(fp, 0, 0);

    // Allocate the storage
    char **stacks = malloc(num_stacks * sizeof(char *));
    for (int i = 0; i < num_stacks; ++i)
    {
        stacks[i] = malloc(100 * sizeof(char));
    }
    size_t *size = malloc(9 * sizeof(size_t));

    // Now read the first 8 lines and get the data
    size_t line_num = 0;
    while (line_num != des_line)
    {
        // Get the line
        read = getline(&line, &len, fp);

        // Read across the line looking for chars
        for (int i = 0; i < read; ++i)
        {
            if (line[i] >= 'A' && line[i] <= 'Z')
                stacks[i / 4][size[i / 4]++] = line[i];
        }

        ++line_num;
    }

    // We put them in backwards, reverse the lists
    for (int i = 0; i < num_stacks; ++i)
    {
        char *rev_stack = malloc(100 * sizeof(char));
        for (size_t j = 0; j <= size[i]; ++j)
            rev_stack[j] = stacks[i][size[i] - j - 1];
        free(stacks[i]);
        stacks[i] = rev_stack;
        free(rev_stack);
    }

    // Push the line twice to get to the right spot
    getline(&line, &len, fp);
    getline(&line, &len, fp);

    // Now we need to parse the rest of the lines
    while (getline(&line, &len, fp) != -1)
    {
        // Move to first number
        size_t idx;
        for (idx = 1; line[idx - 1] != ' '; ++idx)
            ;

        // Get first number
        size_t num_idx = 0;
        char  *num     = malloc(3 * sizeof(char));
        for (; line[idx] != ' '; ++idx)
            num[num_idx++] = line[idx];
        const size_t moving = atoi(num);

        // Move to second
        idx += 2;
        for (; line[idx - 1] != ' '; ++idx)
            ;

        // Get second number
        num_idx = 0;
        num     = malloc(3 * sizeof(char));
        for (; line[idx] != ' '; ++idx)
            num[num_idx++] = line[idx];
        const size_t origin = atoi(num) - 1;

        // Move to third
        idx += 2;
        for (; line[idx - 1] != ' '; ++idx)
            ;

        // Get third number
        num_idx = 0;
        num     = malloc(3 * sizeof(char));
        for (; line[idx] != '\n'; ++idx)
            num[num_idx++] = line[idx];
        const size_t destination = atoi(num) - 1;

        // Perform the action
        for (size_t action = 0; action < moving; ++action)
        {
            stacks[destination][size[destination]++] = stacks[origin][(size[origin]--) - 1];
        }
    }

    // Store top stacks in return
    char *ret = malloc(num_stacks * sizeof(char));
    for (int i = 0; i < num_stacks; ++i)
        ret[i] = stacks[i][size[i] - 1];

    // Clear the memory
    for (int i = 0; i < num_stacks; ++i)
        free(stacks[i]);
    free(stacks);
    free(size);

    return ret;
}

char *two(FILE *fp)
{
    // Prep the input
    char   *line = NULL;
    ssize_t read;
    size_t  len = 0;

    // Read until the newline
    size_t des_line   = 0;
    int    num_stacks = 0;
    while ((read = getline(&line, &len, fp)) != 1)
    {
        // Our desired line guaranteed starts with a space
        if (line[0] == ' ')
        {
            // Get the number of stacks
            size_t num_idx = 0;
            char  *num     = malloc(3 * sizeof(char));
            for (int idx = read - 2; line[idx] != ' '; --idx)
                num[num_idx++] = line[idx];
            num_stacks = atoi(num);
            break;
        }
        ++des_line;
    }

    // This resets the file to start reading from the beginning
    fseek(fp, 0, 0);

    // Allocate the storage
    char **stacks = malloc(num_stacks * sizeof(char *));
    for (int i = 0; i < num_stacks; ++i)
    {
        stacks[i] = malloc(100 * sizeof(char));
    }
    size_t *size = malloc(9 * sizeof(size_t));

    // Now read the first 8 lines and get the data
    size_t line_num = 0;
    while (line_num != des_line)
    {
        // Get the line
        read = getline(&line, &len, fp);

        // Read across the line looking for chars
        for (int i = 0; i < read; ++i)
        {
            if (line[i] >= 'A' && line[i] <= 'Z')
                stacks[i / 4][size[i / 4]++] = line[i];
        }

        ++line_num;
    }

    // We put them in backwards, reverse the lists
    for (int i = 0; i < num_stacks; ++i)
    {
        char *rev_stack = malloc(100 * sizeof(char));
        for (size_t j = 0; j <= size[i]; ++j)
            rev_stack[j] = stacks[i][size[i] - j - 1];
        free(stacks[i]);
        stacks[i] = rev_stack;
        free(rev_stack);
    }

    // Push the line twice to get to the right spot
    getline(&line, &len, fp);
    getline(&line, &len, fp);

    // Now we need to parse the rest of the lines
    while (getline(&line, &len, fp) != -1)
    {
        // Move to first number
        size_t idx;
        for (idx = 1; line[idx - 1] != ' '; ++idx)
            ;

        // Get first number
        size_t num_idx = 0;
        char  *num     = malloc(3 * sizeof(char));
        for (; line[idx] != ' '; ++idx)
            num[num_idx++] = line[idx];
        const size_t moving = atoi(num);

        // Move to second
        idx += 2;
        for (; line[idx - 1] != ' '; ++idx)
            ;

        // Get second number
        num_idx = 0;
        num     = malloc(3 * sizeof(char));
        for (; line[idx] != ' '; ++idx)
            num[num_idx++] = line[idx];
        const size_t origin = atoi(num) - 1;

        // Move to third
        idx += 2;
        for (; line[idx - 1] != ' '; ++idx)
            ;

        // Get third number
        num_idx = 0;
        num     = malloc(3 * sizeof(char));
        for (; line[idx] != '\n'; ++idx)
            num[num_idx++] = line[idx];
        const size_t destination = atoi(num) - 1;

        // Perform the action
        for (size_t action = 0; action < moving; ++action)
        {
            stacks[destination][size[destination]++]
                = stacks[origin][(size[origin] - moving) + action];
        }
        size[origin] -= moving;
    }

    // Store top stacks in return
    char *ret = malloc(num_stacks * sizeof(char));
    for (int i = 0; i < num_stacks; ++i)
        ret[i] = stacks[i][size[i] - 1];

    // Clear the memory
    for (int i = 0; i < num_stacks; ++i)
        free(stacks[i]);
    free(stacks);
    free(size);

    return ret;
}

int main(void)
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
