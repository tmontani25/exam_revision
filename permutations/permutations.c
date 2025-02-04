
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
	while (i < size - 1) //
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
	if (idx == size) // condition de fin de recursion tout parcouru
	{
		tmp[idx] = '\0';
		puts(tmp);
		return ;
	}
	while (i < size)
	{
		if (!placed[i]) 
		{      
        	placed[i] = 1;                             
			tmp[idx] = set[i];                 
			process(set, size, tmp, placed, idx + 1);     //index suivant 
			placed[i] = 0;                                    
		}
		i++; // caractere suivant change le caractere a l'index 0
	}
}



int main(int argc, char **argv) 
{
	if (argc != 2)
		return (1);
	int	size;
	size = ft_strlen(argv[1]);

	char	set[size]; // tableau des caracteres
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
	bubble_sort(set, size); // sert a avoir la chaine dans l'ordre alphabetique
	process(set, size, tmp, placed, 0);
	return (0);
}