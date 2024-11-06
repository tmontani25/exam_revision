#include <stdio.h>

char shift(unsigned char c)
{
    c = c << 1;

    return (c);
}

int main(void)
{
    unsigned char c;
    unsigned char b;
    
    c = 'c';

    b = shift(c);
    printf("new char: %i\n", b);
    
}