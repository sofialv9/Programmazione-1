//Calcola la somma dei numeri interi da 1 a 10

#include <stdio.h>

int main (void)
{
    unsigned int x = 1;
    unsigned int sum = 0;
    while (x <= 10) {
        sum += x;
        ++x;
    }
    printf ("The sum is: %u\n", sum);
}