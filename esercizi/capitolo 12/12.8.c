// Inserisce a caso 25 interi da 0 a 100 in ordine in una lista collegata e calcola la somma e la media in virgola mobile degli elementi.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ListNode {
    int data;
    struct ListNode* nextPtr;
} ListNode;

typedef ListNode* ListNodePtr;

int sumList(ListNodePtr a);
double averageList(ListNodePtr a);
void insert(ListNodePtr *sPtr, int value);
void printList(ListNodePtr currentPtr);

int main() {
    srand(time(NULL));
    
    ListNodePtr listPtr = NULL;
    
    // costruisce una lista con 25 numeri casuali da 0 a 100
    for (int i = 1; i < 26; ++i) {
        insert(&listPtr, rand() % 101);
    }

    puts("The list is:");
    printList(listPtr);

    // calcola e stampa la somma e la media dei valori della lista
    printf("The sum is %d\n", sumList(listPtr));
    printf("The average is %.2f\n", averageList(listPtr));
}

// somma gli interi di una lista
int sumList(ListNodePtr a) {
    int total = 0; // somma dei valori del nodo
    ListNodePtr currentPtr = a; // imposta currentPtr alla lista a

    // effettua un ciclo lungo la lista
    while (currentPtr != NULL) {
        // aggiungi il valore del nodo al totale
        total += currentPtr->data;
        currentPtr = currentPtr->nextPtr;
    }

    return total;
}

// calcola la media degli interi di una lista
double averageList(ListNodePtr a) {
    double total = 0.0; // somma dei valori del nodo
    int count = 0; // numero dei nodi della lista
    ListNodePtr currentPtr = a;

    while(currentPtr != NULL) {
        ++count;
        total += currentPtr->data;
        currentPtr = currentPtr->nextPtr;
    }

    return total / count;
}

// inserisce un nuovo valore nella lista in ordine
void insert(ListNodePtr *sPtr, int value) {
    // allocazione dinamica della memoria
    ListNodePtr newPtr = malloc(sizeof(ListNode));

    // se newPtr non è uguale a NULL
    if(newPtr) {
        newPtr->data = value;
        newPtr->nextPtr = NULL;

        ListNodePtr previousPtr = NULL;
        ListNodePtr currentPtr = *sPtr;

        // ripeti per trovare la locazione corretta nella lista
        while(currentPtr != NULL && value > currentPtr->data) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        // inserisci all'inizio dela lista
        if(previousPtr == NULL) {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        }
        else {
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }
    }
    else {
        printf("%c not inserted. No memory available.\n", value);
    }
}

void printList(ListNodePtr currentPtr) {
    if(!currentPtr) {
        puts("List is empty.\n");
    }
    else {
        while(currentPtr) {
            printf("%d ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }

        puts("*\n");
    }
}