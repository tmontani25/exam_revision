#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
    // check des erreurs
	// fork
	pid_t pid;
	int fd[2];


	if (!file || !argv || (type != 'w' && type != 'r'))
		return (-1);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (type == "r")
		{
			// retourner la partie readeable du pipe
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		else if(type == "w")
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		execvp(file, (char *const*)argv);
		perror("error execvp\n");
		exit(1);
	}
	else
	



}
int	main() {
	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	char	*line;
	while ((line = get_next_line(fd)))
		ft_putstr(line);
}