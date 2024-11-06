#include "gnl_test.h"

char *get_next_line(int fd)
{
    char *buf;
    char *line;

    while (1)
    {
        buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
        if (!read(fd, buf, BUFFER_SIZE))
            puts("read error\n");
        line = strcat(line, buf);
        free(buf);


}

int main(void)
{
    int fd;
    char *path;
    char *result;

    path = "fichier.txt";
    fd = open(path, O_RDONLY);
    result = get_next_line(fd);
}