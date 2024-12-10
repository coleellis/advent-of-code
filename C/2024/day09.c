#include "advent.h"

int main(void)
{
    char *data = get_data(9, 2024);
    printf("%s\n", data);
    free(data);
    return 0;
}
