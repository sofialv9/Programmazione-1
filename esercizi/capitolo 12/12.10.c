// Riceve in ingresso una riga di testo e usa una pila per stampare la riga in ordine inverso

#include <stdio.h>
#include <stdlib.h>

struct stackNode {
    char data;
    struct stackNode* nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode* StackNodePtr;

void push(StackNodePtr* topPtr, char info);
char pop(StackNodePtr* topPtr);
int isEmpty(StackNodePtr topPtr);

int main() {
    StackNodePtr stackPtr = NULL; // punta in cima alla pila
    char c; // carattere corrente del testo

    puts("Enter a line of text:");
    // legge ogni lettera e la inserisce nella pila con un push
    while((c = getchar()) != '\n') {
        push(&stackPtr, c);
    }

    puts("The line in reverse is:");
    // finché la pila non è vuota, elimina con una pop il carattere successivo
    while(!isEmpty(stackPtr)) {
        printf("%c", pop(&stackPtr));
    }
    puts(" ");
}

// Inserisce un nodo in cima alla pila
void push(StackNodePtr* topPtr, char info) {
    StackNodePtr newPtr = malloc(sizeof(StackNode));
    
    if(newPtr) {
        newPtr->data = info;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    }
    else {
        printf("%c not inserted. No memory available.\n", info);
    }
}

// Elimina un nodo in cima alla pila
char pop(StackNodePtr* topPtr) {
    StackNodePtr tempPtr = *topPtr;
    int popValue = (*topPtr)->data;
    *topPtr = (*topPtr)->nextPtr; // ripristina topPtr (ora la cima è il nodo precedente alla vecchia cima)
    free(tempPtr);

    return popValue; // restituisce il valore del nodo eliminato
}

// Verifica se la pila è vuota
int isEmpty(StackNodePtr topPtr) {
    return !topPtr; // restituisce NULL se la pila è vuota
}