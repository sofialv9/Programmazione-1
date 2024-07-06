//Stampa la somma, il prodotto, la differenza, il quoziente e il resto tra due interi

#include <stdio.h>

int main (void)
{
    printf ("Enter two integers: \n");
    int x,y;
    scanf ("%d%d", &x, &y);
    printf ("The sum is: %d\n", x+y);
    printf ("The product is: %d\n", x*y);
    printf ("The difference is: %d\n", x-y);
    printf ("The quotient is: %d\n", x/y);
    printf ("The remainder is: %d\n", x%y);
}