#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



int ft_strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

int picoshell(char ***cmds)
{
    // creer pipe 
    // forker
    // executer commande et rediriger les inputs et outputs

    int i;
    int prev_fd;
    pid_t pid;
    int fd[2];


    while (cmds[i])
    {
        if (cmds[i + 1])
            pipe(fd);
        pid = fork();
        if (pid == 0)
        {
            // verif cmd precedente
            if (prev_fd != 0)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (cmds[i + 1])// si il y a une cmd suivante
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        else // process parent
        if (prev_fd != 0)
            close(prev_fd);
        if (cmds[i + 1])
        {
            close(fd[1]);
            prev_fd = fd[0];
        }
        i++;

    }
    while(wait(NULL) > 0);
    return(0);
}
int main (int argc, char **argv)
{
    //malloc et remplir le tableau de cmds
    
    char ***cmds;
    int cmds_size;
    int i;
    int cmds_i;
    int ret;
    
    i = 0;
    // compter les commandes
    while (i < argc)
    {
        if (!ft_strcmp("|", argv[i]))
            cmds_size++;
        i++;
    }
    cmds = malloc(sizeof(char **) * (cmds_size + 1));
    if (!cmds)
	{
		dprintf(2, "Malloc error: %m\n");
		return 1;
	}
    // remplir le tableau
    cmds[0] = argv + 1;
    cmds_i = 1;
    i = 1;
    while (i < argc)
    {
        if (!ft_strcmp("|", argv[i]))
        {
            cmds[cmds_i] = argv[i + 1];
            argv[i] = NULL;
            cmds_i++;
        }
        i++;
    }
    ret = picoshell(cmds);
	if (ret)
		perror("picoshell");
	free(cmds);
	return ret;
}