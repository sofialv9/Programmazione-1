// Concatena 2 liste collegate di caratteri

#include <stdio.h>
#include <stdlib.h>

// definizione della struttura ListNode
struct ListNode {
    char data; // dato del nodo
    struct ListNode* nextPtr; // puntatore al nodo successivo
}; // RICORDA IL PUNTO E VIRGOLA !!!

typedef struct ListNode ListNode;
typedef ListNode* ListNodePtr;

void concatenate(ListNodePtr a, ListNodePtr b);
void insert(ListNodePtr *sPtr, char value);
void printList(ListNodePtr currentPtr);


int main() {
    ListNodePtr list1Ptr = NULL; // puntatore alla prima lista

    // assegna le lettere da A a C nella prima lista
    for (char i = 'A'; i < 'D'; ++i) {
        insert(&list1Ptr, i);
    }

    printf("%s", "List 1 is: ");
    printList(list1Ptr); // A B C

    ListNodePtr list2Ptr = NULL; // puntatore alla seconda lista

    // assegna le lettere da D a F nella seconda lista
    for(char i = 'D'; i < 'G'; ++i) {
        insert(&list2Ptr, i);
    }

    printf("%s", "List 2 is: ");
    printList(list2Ptr); // D E F

    concatenate(list1Ptr, list2Ptr);
    printf("%s", "The concatenated list is: ");
    printList(list1Ptr); // A B C D E F
}

void concatenate(ListNodePtr a, ListNodePtr b) {
    ListNodePtr currentPtr = a; // imposta currentPtr alla prima lista collegata

    // finché currentPtr non è uguale a NULL
    while(currentPtr->nextPtr != NULL) {
        currentPtr = currentPtr->nextPtr;
    }

    currentPtr->nextPtr = b; // concatena le due liste
}

void insert(ListNodePtr *sPtr, char value) {
    // allocazione dinamica della memoria
    ListNodePtr newPtr = malloc(sizeof(ListNode));

    // se newPtr non è uguale a NULL
    if(newPtr) {
        newPtr->data = value;
        newPtr->nextPtr = NULL;

        ListNodePtr previousPtr = NULL;
        ListNodePtr currentPtr = *sPtr; // imposta currentPtr all'inizio della lista

        // effettua un ciclo per trovare la locazione corrente nella lista
        while(currentPtr != NULL && value > currentPtr->data) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        // inserisci all'inizio della lista
        if (previousPtr == NULL) {
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
        // effettua un ciclo finché currentPtr non è uguale a NULL
        while (currentPtr) {
            printf("%c ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }

        puts("*\n");
    }
}