#include <stdio.h>
#include <stdlib.h>

int is_safe(int *board, int line, int col)
{
	//il ne peut y avoir qu'une seule reine par colonne donc board[i] = la ligne sur laquelle est placee la reine sur la colonne i
	int	i;

	i = 0;
	while (i < col) // i les colonnes qui precede col
	{
		if (board[i] == line // si il y une reine sur la meme ligne pas ok
			|| (board[i] - line == i - col) // diagonale descendante
			|| (board[i] - line == col - i)) // diagonale montante
			return (0);
		i++;
	}
	return (1);
}

void solve_n_queens(int n, int col, int *board)
{
    // n = nombre de colones et nb lignes
	int	i;

	i = 0;
	if (col == n)
	{
		while (i < n)
		{
			fprintf(stdout, "%d", board[i]);
			if (i < n - 1)
				fprintf(stdout, " ");
			i++;
		}
		fprintf(stdout, "\n");
		return ;
	}
    // si la solution est complete on affiche et return


	i = 0;
	while (i < n) // on fait toutes les lignes
	{
		if (is_safe(board, i, col))  // premier passage col = 0; et i = 0; 
		{
			board[col] = i; // dans la colonne je place la reine sur la ligne i
			solve_n_queens(n, col + 1, board); // envoie la colonne suivante (va reverifier toutes les colonnes precedentes a chaque fois)
		}
		i++;
	}
    // verifie si chaque position est ok
}

int main(int argc, char *argv[])
{
	int	n;
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <n>\n", argv[0]);
		return (1);
	}
	n = atoi(argv[1]);
	if (n <= 0)
	{
		fprintf(stderr, "n must be a positive integer\n");
		return (1);
	}
	int	board[n];
	solve_n_queens(n, 0, board);
	return (0);
}