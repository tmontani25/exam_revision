#include "get_next_line.h"

char *get_next_line(int fd)
{
    
}
int main(void)
{
    int fd;
    char *path;
    char *result;

    path = "gnl.txt";
    fd = open(path, O_RDONLY);
    result = get_next_line(fd);
    free(result);
    printf("line: %s\n", result);
}