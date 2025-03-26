#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
    // 
}
int	main() {
	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	char	*line;
	while ((line = get_next_line(fd)))
		ft_putstr(line);
}