#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



int picoshell(char ***cmds)
{

    int i = 0;
    int fds[2];
    int prev_fd;
    pid_t pid;

    // verifier si il y a des pipes
   while (cmds)
   {
        if (cmds[i +1]) // il y a un pipe
            pipe(fds);
        pid = fork();
        if (pid == 0)
        {
            // verifier si il ya une cmd precedente
            if (prev_fd != 0)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if(cmds[i + 1])// si il y a une cmds suivante
            {
                close(fds[0]);
                dup2(fds[1], STDOUT_FILENO);
                close(fds[1]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
		else // parent sert a fermer les pipes
		{
			if(prev_fd !=0) // si ce nest pas la premiere commande
				close(prev_fd);
			if(cmds[i+1]) // si il y a plusieurs commandes
			{
				close(fds[1]); //ferme le write
				prev_fd = fds[0]; //prev_fd devient le read
			}
		}
		i++; 
   }
}
int main (int argc, char **argv)
{
    // charger le tableau de cmds + allouer memoire

    char ***cmds;
    int cmds_size;
    int i;
    int cmds_i;

    i = 0;
    cmds_size = 1;
    while(i < argc)
    {
        if(!strcmp("|", argv[i]))
            cmds_size++;
    }
    cmds = (char ***)malloc(sizeof(char **) * cmds_size + 1);
    i = 0;
    //remplir le tableau

    cmds[0] = argv[1];
    cmds_i = 1;
    while (i < argc)
    {
        if (!strcmp("|", argv[i]))
            cmds[cmds_i] = argv + i + 1;
        cmds_i++;
        i++;
    }
    int ret = picoshell(cmds);
    if (ret)
		perror("picoshell");
	free(cmds);
	return ret;
}