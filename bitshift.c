#include <stdio.h>

char shift(char c)
{
    c = c << 1;

    return (c);
}

int main(void)
{
    char c;
    char b;

    c = 'c';

    b = shift(c);
    printf("new char: %i\n", b);
    
}