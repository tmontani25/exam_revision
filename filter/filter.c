#include <stdio.h>
#include <string.h>
#include <unistd.h>


char *ft_strcpy(char *s1, char *s2)
{
    int i;

    i = 0;
    while(s1[i])
    {
        s2[i] = s1[i];
        i++;
    }
    s2[i] = s1[i];
    return (s2);
}
void filter(char *str)
{
    char *buf;
    int bytes_read;
    char *line;

    buf = (char *)malloc(sizeof(char) * 1000);
    bytes_read = read(STDIN_FILENO, buf, 20);
    
    line = ft_strcpy(buf, line);

}
int main(int argc, char *argv)
{
    if (argc != 2)
        return (0);
    filter(argv[1]);
}