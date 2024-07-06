#include <stdio.h>

int main (void) {
    int numero = 0;
    int somma = 0;
    unsigned int counter = 0;
    
    printf ("Inserire un numero (9999 per terminare): ");
    scanf ("%d", &numero);

    while (numero != 9999) {
        somma += numero;
        counter++;
        printf ("Inserire un numero (9999 per terminare): ");
        scanf ("%d", &numero);
    }

    printf ("La media è: %d \n", somma / counter);

}