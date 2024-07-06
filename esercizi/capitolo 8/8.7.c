// Converte 4 stringhe in interi e somma i 4 valori

#include <stdio.h>
#include <stdlib.h>

int main() {
    char string[80]; // stringa di interi inserita dall'utente
    int sum = 0; // risultato di 4 interi

    // converte string in un intero per 4 volte
    for (unsigned int i = 0; i < 4; i++) {
        printf("%s", "Enter an integer string: ");
        scanf("%s", string);
        sum += strtol(string, 0, 0);
    }

    printf("The total of the values is %d\n", sum);
}