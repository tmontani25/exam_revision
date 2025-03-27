
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int ft_popen(const char *file, const char *argv[], char type)
{
    pid_t pid;
    int fd[2];

    if (!file || !argv || (type != 'w' && type != 'r'))
        return (-1);
    
    if (pipe(fd) == -1) {
        perror("pipe");
        return -1;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    }

    if (pid == 0) // Processus enfant
    {
        if (type == 'r') {
            close(fd[0]); // Ferme la lecture dans le fils
            dup2(fd[1], STDOUT_FILENO); // Redirige stdout vers le write du pipe
            close(fd[1]);
        }
        else if (type == 'w') {
            close(fd[1]); // Ferme l'écriture dans le fils
            dup2(fd[0], STDIN_FILENO); // Redirige stdin vers le pipe
            close(fd[0]);
        }
        execvp(file, (char *const*)argv); // Exécute la commande
        perror("execvp"); // Si execvp échoue
        exit(1);
    }
    else // Processus parent
    {
        if (type == 'r') {
            close(fd[1]); // Ferme l'écriture dans le parent
            return fd[0]; // Retourne le descripteur de lecture
        }
        if (type == 'w') {
            close(fd[0]); // Ferme la lecture dans le parent
            return fd[1]; // Retourne le descripteur d'écriture
        }
    }
    return -1;
}

int main()
{
    char buffer[128];
    ssize_t bytes_read;

    // === Créer le pipe pour écrire ===
    int fd = ft_popen("cat", (const char *[]){"cat", "-n", NULL}, 'w'); 
    if (fd == -1) {
        perror("ft_popen");
        return 1;
    }

    // === Écrire dans le pipe ===
    write(fd, "test\n", 5);
    write(fd, "hello world\n", 12);

    // === Fermer le descripteur d'écriture ===
    close(fd);

    // === Créer un nouveau pipe pour lire le résultat ===
    int fd_1 = ft_popen("cat", (const char *[]){"cat", "-n", NULL}, 'r'); 

    if (fd == -1) {
        perror("ft_popen");
        return 1;
    }

    // === Lire le contenu depuis le pipe ===
    while ((bytes_read = read(fd_1, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }

    close(fd_1);

    return 0;
}

