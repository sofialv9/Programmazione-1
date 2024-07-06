//esercizio 5.23 - calcola i secondi trascorsi tra 2 orari

#include <stdio.h>
#include <stdlib.h>

int calcoloSecondi(int a, int b, int c, int d, int e, int f);

int main()
{
    int ore1, minuti1, secondi1, ore2, minuti2, secondi2;
    printf("Inserire il primo orario nel formato ore minuti secondi: ");
    scanf("%d %d %d", &ore1, &minuti1, &secondi1);
    printf("Inserire il secondo orario nel formato ore minuti secondi: ");
    scanf("%d %d %d", &ore2, &minuti2, &secondi2);
    if (ore1 < 12 && ore2 < 12) {
        printf("Secondi trascorsi tra i due orari: %d\n", calcoloSecondi(ore1, minuti1, secondi1, ore2, minuti2, secondi2));
    }
    else {
        printf("Inserire un valore delle ore minore di 12.\n");
        main();
    }
}

int calcoloSecondi(int a, int b, int c, int d, int e, int f)
{
    int orario1 = c + (b * 60) + (a * 3600);
    int orario2 = f + (e * 60) + (d * 3600);
    return abs(orario2-orario1);
}