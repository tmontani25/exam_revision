
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	bubble_sort(char *set, int size)
{
	int 	i;
	int		j;
	char	tmp;

	i = 0;
	while (i < size - 1)
	{

		j = 0;
		while (j < size - 1 - i) //place l'element le plus grand a la fin a chaque fois que la boucle est executee
		{                        // puisque l'element le plus grand est a la fin plus besoin de le verifier donc -i   
			if (set[j] > set[j + 1])
			{
				tmp = set[j + 1];
				set[j + 1] = set[j];
				set[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void process(char *set, int size, char *tmp, int *placed, int idx)
{
	int	i;

	i = 0;
	if (idx == size)
	{
		tmp[idx] = '\0';
		puts(tmp);
		return ;
	}
	while (i < size)
	{
		if (!placed[i]) // si un caractere n'a pas encore ete place on le place
		{                                                   // si il n'a pas ete place on le place et on marque placed
        	placed[i] = 1;                                  // on rappelle la fonction avec l'index suivant dans temp
			tmp[idx] = set[i];                              //et comme le caractere a ete place placed[i] = 1 ca fait i++;
			process(set, size, tmp, placed, idx + 1);       // ce qui permet de checker le caractere suivant
			placed[i] = 0;                                                      //si il a deja ete place i++; caractere suivant
		}
		i++;
	}
}



int main(int argc, char **argv) // sert a avoir la chaine dans l'ordre alphabetique
{
	if (argc != 2)
		return (1);
	int	size;
	size = ft_strlen(argv[1]);

	char	set[size];
	char	tmp[size + 1]; // tableau pour les permutations
	int		placed[size]; // caracteres utilises
	int		i;

	i = 0;
	while (i < size)
	{
		set[i] = argv[1][i];
		placed[i] = 0;
		i++;
	}
	tmp[size] = '\0';
	bubble_sort(set, size);
	process(set, size, tmp, placed, 0);
	return (0);
}