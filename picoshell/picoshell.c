#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
	int i;
	int prev_fd;
	pid_t pid;
	int fd[2];

	i = 0;
	prev_fd = 0;
	while(cmds[i])
	{
		if(cmds[i+1]) // si il y plusieurs commandes il y a un pipe
			pipe(fd);
		pid = fork();
		if(pid == 0) // child redirection stdin et stdout et execution de la commande
		{
			if(prev_fd !=0) // si ce nest pas la premiere commande
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if(cmds[i+1]) // si il y a plusieurs commandes
			{
				close(fd[0]);//ferme le read
				dup2(fd[1], STDOUT_FILENO);//redirige la sortie standard vers le write
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]); // execute la commande si ca marche ca exit le process enfant
			exit(1); // si ca ne marche pas on exit avec 1
		}
		else // parent sert a fermer les pipes
		{
			if(prev_fd !=0) // si ce nest pas la premiere commande
				close(prev_fd);
			if(cmds[i+1]) // si il y a plusieurs commandes
			{
				close(fd[1]); //ferme le write
				prev_fd = fd[0]; //prev_fd devient le read
			}
		}
		i++;
	}
	while(wait(NULL) > 0)
		;
	return (0);
}

int	main(int argc, char **argv)
{
	int	cmds_size = 1;
	for (int i = 1; i < argc; i++) //check le nombre de commandes et le stock
	{
		if (!strcmp(argv[i], "|")) // si il y a un pipe on incremente cmds_size
			cmds_size++;
	}
	char ***cmds = calloc(cmds_size + 1, sizeof(char **));
	if (!cmds)
	{
		dprintf(2, "Malloc error: %m\n");
		return 1;
	}
	cmds[0] = argv + 1; // premiere commande juste apres le ./a.out
	int cmds_i = 1;
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "|")) //parcours ligne de commande
		{
			cmds[cmds_i] = argv + i + 1; // permet de sauter le pipe i = index du pipe
			argv[i] = NULL;                 // permet de mettre un NULL a la place du pipe
			cmds_i++;
		}
	}
	int ret = picoshell(cmds);
	if (ret)
		perror("picoshell");
	free(cmds);
	return ret;
}