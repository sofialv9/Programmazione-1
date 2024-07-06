//Stampa la somma, la media, il prodotto, il minore e il maggiore tra tre interi diversi

#include <stdio.h>

int main (void)
{
    printf ("Enter three different integers: \n");
    int x, y, z;
    scanf ("%d%d%d", &x, &y, &z);
    printf ("The sum is: %d \n", x+y+z);
    printf ("The median is: %d \n", (x+y+z)/3);
    printf ("The product is: %d \n", x*y*z);
    int min, max;
    min = x;
    if (min>=y) min=y;
    if (min>=z) min=z;
    printf ("The minimum is: %d \n", min);
    max = x;
    if (max<=y) max=y;
    if (max<=z) max=z;
    printf ("The maximum is: %d \n", max);
}