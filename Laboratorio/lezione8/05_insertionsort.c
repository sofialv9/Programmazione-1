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

// Suppone che la parte di sinistra dell'array sia ordinato e seleziona un elemento dalla parte non ordinata e lo pone nella posizione corretta nella parte ordinata verificando se gli elementi di quest'ultimo sono maggiori dell'elemento da inserire. Fa passate da 1 a n.
void insertionSort(int a[], int n) {
    // scorri tutte le sottosequenze ordinate che iniziano con zero 
    for(int i = 1; i < n; i++) {
        // Data la sottosequenza che inizia in zero e finisce in i-1, l'obiettivo è di
        // inserire il valore a[i] nella posizione corretta della sottosequenza ordinata
        int val = a[i]; // copia del valore di a[i] (lo sovrascriveremo)
        int j = i - 1; // parto dall'ultimo elemento della sottosequenza
        while(j >= 0 && a[j] > val){ //finché val è più piccolo dell'elemento corrente
            a[j + 1] = a[j]; //sposto l'elemento "in avanti"
            j--;
        }
        a[j + 1] = val; //inserisco val nella posizione corretta

        printf("\n\n");
        printf("Inserisco %d\n", val);
        printArray(a,n);

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

    insertionSort(array, SIZE);

    printf("\nArray ordinato:\n");
    printArray(array, SIZE);
}