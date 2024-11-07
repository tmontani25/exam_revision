#include "gnl_test.h"


// garder les bytes lu dans une chaine
//verifier /n
//join les caracteres suivant
//

static char *ft_read(int fd, char *buf)
{
    int bytes_read;
    char *line;
    char *backup;
    

    bytes_read = read(fd, buf, BUFFER_SIZE);
    if (bytes_read == -1)
    {
        free(buf);
        return (NULL);
    }
    while (bytes_read > 0)
    {
        if (!backup)
            backup = strdup(buf);
        else if (backup)

        
    }
}
char *get_next_line(int fd)
{
    char *buf;
    char *line;
    
    buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    line = ft_read(fd, buf);




}

int main(void)
{
    int fd;
    char *path;
    char *result;

    path = "fichier.txt";
    fd = open(path, O_RDONLY);
    result = get_next_line(fd);
    printf("line: %s\n", result)
}