#include <stdio.h>

int main (void) {
    int counter = 0;
    int numero = 0;

    printf ("Inserire il primo numero (uguale alla quantità dei successivi valori): ");
    scanf ("%d", &counter);
    int minimo = counter;

    for (unsigned int i = 1; i <= counter; i++) {
        printf ("Inserire il prossimo numero: ");
        scanf ("%d", &numero);
        if (numero < minimo) {
            minimo = numero;
        }
    }

    printf ("Il numero minore è: %d \n", minimo);

}