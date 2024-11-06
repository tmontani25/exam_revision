#include <stdio.h>
#include <unistd.h>


char    swap_bits(unsigned char c)
{
    unsigned char a;
    unsigned char b;
    unsigned char result;

    a = c >> 4;
    b = c << 4;
    result = (a | b);
    return (result);
}

// unsigned char	swap_bits(unsigned char octet)
// {
// 	return ((octet >> 4) | (octet << 4));
// }

int main(void)
{


    unsigned char result;
    result = swap_bits('c');
   printf("swapped: %d\n", result);

}