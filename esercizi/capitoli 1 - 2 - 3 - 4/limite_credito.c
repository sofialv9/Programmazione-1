#include <stdio.h>

int main () {
    int conto = 0;
    int limite = 0;
    int saldo = 0;
    int counter = 0;

    while (++counter <= 3) {
        printf ("Inserire il proprio numero di conto: ");
        scanf ("%d", &conto);
        printf ("Inserire il proprio limite di credito: ");
        scanf ("%d", &limite);
        printf ("Inserire il proprio saldo di credito: ");
        scanf ("%d", &saldo);

        printf ("Il nuovo limite di credito è: $%d\n", limite/2);
        if (saldo > (limite/2)) {
            printf ("Hai superato il nuovo limite di credito.\n");
        }

    }

}