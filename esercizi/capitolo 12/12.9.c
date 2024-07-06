// Crea una lista collegata di 10 caratteri e ne crea una copia in ordine inverso

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    char data;
    struct ListNode* nextPtr;
};

typedef struct ListNode ListNode;
typedef ListNode* ListNodePtr;

ListNodePtr reverseList(ListNodePtr currentPtr);
void insert(ListNodePtr *sPtr, char value);
void printList(ListNodePtr currentPtr);
void push(ListNodePtr *topPtr, char info);

int main() {
    ListNodePtr listPtr = NULL;

    // costruisce lista con i caratteri da A a J
    for(char i = 'A'; i < 'K'; ++i) {
        insert(&listPtr, i);
    }

    puts("The list is:");
    printList(listPtr);

    puts("The list in reverse is:");
    printList(reverseList(listPtr));
}

// crea una lista nell'ordine inverso della lista in argomento
ListNodePtr reverseList(ListNodePtr currentPtr) {
    ListNodePtr stack = NULL; // puntatore alla lista invertita

    // effettua un ciclo lungo la lista currentPtr
    while(currentPtr != NULL) {
        // inserisci con push l'elemento corrente sulla pila
        push(&stack, currentPtr->data);
        currentPtr = currentPtr->nextPtr;
    }

    return stack; // restituisce la lista invertita
}

// Inserisci un nuovo valore nella lista in ordine
void insert(ListNodePtr *sPtr, char value) {
    ListNodePtr newPtr = malloc(sizeof(ListNode));

    if(newPtr) {
        newPtr->data = value;
        newPtr->nextPtr = NULL;

        ListNodePtr previousPtr = NULL;
        ListNodePtr currentPtr = *sPtr;

        while(currentPtr != NULL && value > currentPtr->data) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if(previousPtr == NULL) {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        }
        else{
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }
    }
    else {
        printf("%c not inserted. No memory available.\n", value);
    }
}

// inserisce un nodo in cima alla pila
void push(ListNodePtr* topPtr, char info) {
    ListNodePtr newPtr = malloc(sizeof(ListNode));

    // se la memoria è stata allocata, inserisci un nodo all'inizio della lista
    if(newPtr){
        newPtr->data = info;
        newPtr->nextPtr = *topPtr; // la vecchia cima è ora il nodo precedente alla nuova cima
        *topPtr = newPtr;
    }
    else {
        printf("%c not inserted. No memory available.\n", info);
    }
}

void printList(ListNodePtr currentPtr) {
    if(!currentPtr) {
        puts("List is empty.\n");
    }
    else {
        while(currentPtr) {
            printf("%c ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        } 
    }
    puts("*\n");
}