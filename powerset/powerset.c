#include <stdio.h>
#include <stdlib.h>

// chaque appel recursif cree une boucle de recursion et 
void	find_subsets(int *arr, int size, int target, int *subset, int subset_size, int start, int sum)
{
	int	i;
	int	j;

	if (sum == target && subset_size > 0)
	{
		i = 0;
		while (i < subset_size)
		{
			printf("%d ", subset[i]);
			i++;
		}
		printf("\n");
	}
	if (start >= size) // condition qui permet d'arreter toutes les boucles de recursion
		return ;        //lorsqu'elles ont atteint toutes les possibilites
	j = start;
	while (j < size) // boucle de recursion plusieurs comme ceci sont crees
	{
		subset[subset_size] = arr[j]; 
		find_subsets(arr, size, target, subset, subset_size + 1, j + 1, sum + arr[j]);
		j++;
	}
}

int main(int argc, char **argv) 
{
	int	i;
	int	size;
	int	target;
	int	*arr;
	int	*subset;

	if (argc < 3)
		return (1);
	i = 0;
	size = argc - 2; // enlever argv[0] et argv[1] et compter les nb
	target = atoi(argv[1]);
	arr = malloc(sizeof(int) * size);
	subset = malloc(sizeof(int) * size);
	if (!arr || !subset)
	{
		free(arr);
		free(subset);
		return (1);
	}
	while (i < size)
	{
		arr[i] = atoi(argv[i + 2]); // commence a argv[2]
		i++;
	}
	find_subsets(arr, size, target, subset, 0, 0, 0);
	free(arr);
	free(subset);
	return (0);
}