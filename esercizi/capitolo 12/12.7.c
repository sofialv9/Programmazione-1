// Fonde due liste ordinate di interi in una singola lista ordinata di interi

#include <stdio.h>
#include <stdlib.h>

// definizione della struttura ListNode
struct ListNode {
    int data; // dato del nodo
    struct ListNode* nextPtr; // puntatore al nodo successivo
};

typedef struct ListNode ListNode;
typedef struct ListNode* ListNodePtr;

void insert(ListNodePtr *sPtr, int value);
void printList(ListNodePtr currentPtr);
ListNodePtr merge(ListNodePtr a, ListNodePtr b);

int main() {
    ListNodePtr list1Ptr = NULL; // puntatore alla prima lista

    for(int i = 2; i < 11; i += 2) {
        insert(&list1Ptr, i);
    }

    printf("%s", "List 1 is: ");
    printList(list1Ptr); // 2 - 4 - 6 - 8 - 10

    ListNodePtr list2Ptr = NULL; // puntatore alla seconda lista

    for(int i = 1; i < 10; i += 2) {
        insert(&list2Ptr, i);
    }

    printf("%s", "List 2 is: ");
    printList(list2Ptr); // 1 - 3 - 5 - 7 - 9

    // fondi entrambe le liste e stampa i risultati
    ListNodePtr list3Ptr = merge(list1Ptr, list2Ptr);
    printf("%s", "The merged list is: ");
    printList(list3Ptr); // 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - 10
}

// fondi due liste di interi
ListNodePtr merge(ListNodePtr a, ListNodePtr b) {
    ListNodePtr c = NULL; // puntatore alla lista unita
    ListNodePtr currentPtr1 = a; // imposta currentPtr1 alla prima lista
    ListNodePtr currentPtr2 = b; // imposta currentPtr2 alla seconda lista

    // finché currentPtr1 non è uguale a NULL
    while(currentPtr1) {
        // confronta currentPtr1 e currentPtr2 e inserisce il nodo più piccolo
        if (currentPtr2 == NULL || currentPtr1->data < currentPtr2->data) {

            // inserisci il nodo currentPtr1
            insert(&c, currentPtr1->data);
            currentPtr1 = currentPtr1->nextPtr;
        }
        else {
            // inserisci il nodo currentPtr2
            insert(&c, currentPtr2->data);
            currentPtr2 = currentPtr2->nextPtr;
        }
    }

    // inserisci i nodi rimanenti nella lista currentPtr2
    while(currentPtr2 != NULL) {
        insert(&c, currentPtr2->data);
        currentPtr2 = currentPtr2->nextPtr;
    }

    return c; // restituisci la lista fusa
}

void insert(ListNodePtr *sPtr, int value) {
    // allocazione dinamica della memoria
    ListNodePtr newPtr = malloc(sizeof(ListNode));

    // se newPtr non è uguale a NULL
    if (newPtr) {
        newPtr->data = value;
        newPtr->nextPtr = NULL;

        ListNodePtr previousPtr = NULL;
        ListNodePtr currentPtr = *sPtr; // imposta currentPtr all'inizio della lista

        // ripeti per trovare la locazione corretta nella lista
        while(currentPtr != NULL && value > currentPtr->data) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        // inserisci all'inizio della lista
        if(previousPtr == NULL) {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        }
        else { // inserisci un nodo tra previousPtr e currentPtr
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }
    }
    else {
        printf("%c not inserted. No memory available.\n", value);
    }
    
}

// stampa la lista
void printList(ListNodePtr currentPtr) {
    // se la lista è vuota
    if(!currentPtr) {
        puts("List is empty.\n");
    }
    else {
        // ripeti finché currentPtr non è uguale a NULL
        while(currentPtr) {
            printf("%d ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
        puts("*\n");
    } 
}