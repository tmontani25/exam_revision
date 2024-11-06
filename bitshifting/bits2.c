
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
bool    shift(int nb, int pos)
{
    int move; 

    move = 8 - pos;
    if (nb >> move & 1)
        return (true);
    else
    return(false);

}

int main (void)
{
    int c;
    bool activated = true;

    c = 0;
    activated = shift(c, 3);
    printf("La valeur du booléen est : %s\n", activated ? "true" : "false");
}