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
    // n = nombre de colones et nb lignes et reines
	int	i;

	i = 0;
	if (col == n)  // si toutes les colonnes ont etees parcourues
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
		if (is_safe(board, i, col))  // la premiere boucle va verifier pour la colonne 0 les lignes safe
		{
			// si on peut placer une reine on la place et on rapelle la fonction avec cette reine placee
			board[col] = i; // dans la colonne je place la reine sur la ligne i
			solve_n_queens(n, col + 1, board); // envoie la colonne suivante pour verifier cette possibilite
		} 
		i++;// si la ligne n'est pas safe i++ essaye une autre ligne
	}
    // verifie si chaque position est ok
}
// l'appel recursif dans cette fonction n'est fait que si la position est valable pour aller trouver la position de la prochaine reine

int main(int argc, char *argv[])
{
	int	n; // taille echiquier
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