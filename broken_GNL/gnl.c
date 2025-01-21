#include "get_next_line.h"


int ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return (i);
}

char *ft_strdup(char *str)
{
    int i;
    char *dest;

    i = 0;
    dest = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
    if (!dest)
		return (NULL);
    while (str[i])
    {
        dest[i] = str[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char *get_next_line(int fd)
{
    char buffer;
    int b;
    char line[7000000];
    int i;

    i = 0;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    b = read(fd, &buffer, 1);
    while (b > 0)
    {
        line[i++] = buffer;
        if (buffer == '\n')
            break;
        b = read(fd, &buffer, 1);
    }
    line[i] = '\0';
    if (b <= 0 && i == 0)
        return(NULL);
    return(ft_strdup(line));
}

int main(void)
{
    int fd;
    char *path;
    char *result;

    path = "gnl.txt";
    fd = open(path, O_RDONLY);
    result = get_next_line(fd);

   printf("line: %s\n", result);
   free(result);
     result = get_next_line(fd);
        printf("line: %s\n", result);
   free(result);
   
}