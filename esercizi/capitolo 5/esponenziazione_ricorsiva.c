//Esercizio 5.34

#include <stdio.h>

int main()
{
    unsigned int power(unsigned int base, unsigned int esponente);
    unsigned int x = 0;
    unsigned int y = 0;
    printf("Inserire la base e l'esponente: ");
    scanf("%d %d", &x, &y);
    printf("Il risultato dell'operazione è: %u\n", power(x, y));
}

unsigned int power(unsigned int base, unsigned int esponente)
{
    unsigned int result = base;
    for (unsigned int i = esponente; i > 1; i--) {
        result *= base;
    }
    return result;
}