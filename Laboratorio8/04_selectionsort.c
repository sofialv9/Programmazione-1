#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 10
#define MAX 100

void printArray(int a[], int n) {
    for(int i=0; i<n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// Si ha una parte (sinistra) dell'array ordinata e una parte non ordinata. A ogni passata si sceglie il minimo dalla parte non ordinata. Fa da 0 a n - 1 passate.
void selectionSort(int a[], int n) {
    // Ad ogni passata seleziona il minimo della sequenza che va dall'indice pass alla fine e scambia l'elemento all'indice pass con il minimo.
    for(int pass = 0; pass < n - 1; pass++) {
        // inizializziamo l'indice del minimo
        int idx_min = pass;
        for(int i = pass + 1; i < n; i++) { // ricerca del minimo nella parte destra dell'array
            // in cui conserviamo l'indice del minimo
            if(a[i] < a[idx_min])
                idx_min = i; // aggiorno il minimo
        }
        // scambiamo i valori agli indici pass e idx_min

        printf("\n\n");
        printArray(a, n);
        printf("Scambio %d con %d\n", a[pass], a[idx_min]);
        // si potrebbe mettere if(pass != idx_min) come ottimizzazione per fare lo swap dei 2 elementi solo se i 2 indici sono diversi
        int tmp = a[pass];
        a[pass] = a[idx_min];
        a[idx_min] = tmp;
    }
}

int main() {
    int array[SIZE];

    srand(time(NULL));

    for(int i=0; i<SIZE; i++) {
        array[i] = rand()%(MAX+1);
    }

    printf("Array non ordinato:\n");
    printArray(array, SIZE);

    selectionSort(array, SIZE);

    printf("\nArray ordinato:\n");
    printArray(array, SIZE);
}