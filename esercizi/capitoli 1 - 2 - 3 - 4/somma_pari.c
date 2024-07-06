// calcola la somma dei numeri interi pari da 2 a 30

#include <stdio.h>

int main (void) {

    int sum = 0;

    for (unsigned int num = 2; num <= 30; num += 2) {
        sum += num;
    }

    printf ("La somma è: %d \n", sum);
}