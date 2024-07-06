#include <stdio.h>

void printArray(int a[][5]);
void printMinimum(int a[][5]);

int main()
{
    int t[2][5]; //= {0};
    
    //inizializza elementi a zero
    for(size_t i = 0; i <= 1; i++) { 
        for(size_t j = 0; j <= 4; j++) {
            printf ("Enter an integer: ");
            scanf("%d", &t[i][j]);
        }
    }
    printArray(t); //stampa array in formato tabellare (con indici di righe e colonne)
    printMinimum(t); //stampa valore minimo tra gli elementi dell'array

    //stampa i valori degli elementi della prima riga
    printf("Gli elementi della prima riga sono: "); 
    for(size_t j = 0; j <= 4; j++) {
        printf ("%d ", t[0][j]);
    }
    puts("");
    
    //stampa la somma degli elementi della quarta colonna
    printf("La somma degli elementi della quarta colonna è: ");
    int sum = 0;
    for(size_t i = 0; i <= 1; i++) {
        sum += t[i][3];
    }
    printf("%d", sum);
    puts("");
}



void printArray(int a[][5])
{
    printf("   1 2 3 4 5\n");
    for(size_t i = 0; i <= 1; i++) {
        printf ("%ld  ", i + 1);
        for(size_t j = 0; j <= 4; j++) {
            printf ("%d ", a[i][j]);
        }
        puts ("");
    }
}

void printMinimum(int a[][5])
{
    int min = a[0][0];
    for(size_t i = 0; i <= 1; i++) {
        for(size_t j = 0; j <= 4; j++) {
            if (a[i][j] < min) {
                min = a[i][j];
            }
        }
    }
    printf("Il minimo è: %d\n", min);
}