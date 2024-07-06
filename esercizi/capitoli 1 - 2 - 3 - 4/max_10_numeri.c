//Legge una serie di 10 numeri e determina il maggiore dei numeri

#include <stdio.h>

int main (void)
{
    int counter = 0;
    unsigned int number, largest;
    number = 0;
    largest = 0;
    while (counter < 10) {
        printf ("Enter an integer: ");
        scanf ("%u", &number);
        if (number > largest)
            largest = number;
        ++counter;
    }
    printf ("The largest number is: %u \n", largest);
}