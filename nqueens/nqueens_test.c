#include <stdio.h>
#include <stdlib.h>


int is_safe(int line, int col, int *board)
{
    int i;

    i = 0;
    while (i < col)
    {
        if (board[i] == line || board[i] - line == i - col || board[i] - line == col - i)
            return (0);
        i++;
    }
    return (1);
}
void    solve_n_queens(int *board, int col, int n)
{
    int i;

    i = 0;
    if (col == n)
    {
        while (i < n)
        {
            fprintf(stdout, "%d", board[i]);
            if (i < n -1)
                fprintf(stdout, " ");
            i++;
        }
        fprintf(stdout, "\n");
        return ;
    }
    i = 0;
    while (i < n)
    {
        if (is_safe(i , col, board))
        {
            board[col] = i;
            solve_n_queens(board, col + 1, n);
        }
        i++;
    }

}
int main(int argc, char **argv)
{
    int n;

    if (argc != 2)
    {
        return(1);
    }
    n = atoi(argv[1]);
    if (n <= 0)
        return(1);
    int board [n];
    solve_n_queens(board, 0, n);
    return(0);
}