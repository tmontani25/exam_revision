#include <stdio.h>
#include <math.h>

//mettre a jour en float pour utliser sqrtf

double	calculate_distance(double x0, double x1, double y0, double y1)
{
	double	dx = x1 - x0;
	double	dy = y1 - y0;   // calcule de la distance entre 2 points

	return sqrtf(dx * dx + dy * dy); // racine de (dx^2 + d^2)   formule
}

void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	find_shortest_path(int *perm, int start, int len, double x[], double y[], double *min_distance)
{
	int	i;
	double	total_distance;

	total_distance = 0;
	if (start == len - 1) // condition de fin de recursion len - 1 est l'indice du dernier point
	{                       //sera atteinte pour chaque permutation possible avec un point start donné
		i = 0;
		while (i < len - 1) // on parcours tout le tableau de points
		{
			total_distance += calculate_distance(x[perm[i]], x[perm[i + 1]], y[perm[i]], y[perm[i + 1]]); // ordre actuel des points perm = index
			i++;
		}
		total_distance += calculate_distance(x[perm[len - 1]], x[perm[0]], y[perm[len - 1]], y[perm[0]]); // relie le dernier point au point de depart
		if (total_distance < *min_distance)
			*min_distance = total_distance; //update la distance minimale si une distance plus courte a ete trouvee
	}
	else
	{
		i = start;  // permet d'incrementer i a chaque fois qu'une nouvelle fonction est appellee
		while (i < len) // boucle de recursion 
		{               // la premiere boucle permet de tester tous les swap avec perm[0] (point 0) la deuxieme avec perm[1] (point 1)...
			swap(&perm[start], &perm[i]);
			find_shortest_path(perm, start + 1, len, x, y, min_distance); // test une fois que le swap a ete fait 
			swap(&perm[start], &perm[i]);  //backtracking remet comme avant de swap pour tester une autre possibilite
			i++;
		}
	}
}

int	main()
{
	int		len; // nombre de points 
	int		perm[11];
	double	x[11];
	double	y[11];
	double	min_distance;

	len = 0;
	while (fscanf(stdin, "%lf, %lf", &x[len], &y[len]) == 2)// recupere les coordonees de chaque point
	{
		perm[len] = len; // stock les indices des points (pour permuter ensuite)
		len++;
	}
	min_distance = 1e308;
	find_shortest_path(perm, 0, len, x, y, &min_distance);
	printf("shortest total distance is: %.2f\n", min_distance);
	return (0);
}