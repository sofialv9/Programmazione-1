// Usa una pila per determinare se una stringa è un palindromo (si legge allo stesso modo in avanti e all'indietro) ignorando spazi e punteggiatura.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

struct stackNode {
    char data;
    struct stackNode* nextPtr;
};

typedef struct stackNode stackNode;
typedef stackNode* stackNodePtr;

void push(stackNodePtr* topPtr, char info);
char pop(stackNodePtr* topPtr);
int isEmpty(stackNodePtr topPtr);

int main() {
    stackNodePtr stackPtr = NULL; // punta in cima alla pila
    char c; // carattere corrente del testo
    char line[50]; // testo inserito dall'utente
    char condensedLine[50]; // testo con le sole lettere
    int j = 0; // lunghezza della riga
    int i = 0; // lunghezza della riga senza spazi e punteggiatura

    puts("Enter a line of text:");

    // legge ogni lettera e la aggiunge alla riga
    while((c = getchar()) != '\n') {
        line[j++] = c;

        // elimina tutti gli spazi e la punteggiatura
        if(isalpha(c)) {
            condensedLine[i++] = tolower(c);
            push(&stackPtr, tolower(c));
        }
    }
    line[j] = '\0';
    bool palindrome = true; // risultato del test di palindromi

    // effettua un ciclo lungo condensedLine
    for(j = 0; j < i; ++j) {
        // se condensedLine non corrisponde alla pila
        if(condensedLine[j] != pop(&stackPtr)) {
            palindrome = false;
            break; // esce dal ciclo
        }
    }

    // se il testo è un palindromo
    if(palindrome) {
        printf("\"%s\" is a palindrome\n", line);
    }
    else {
        printf("\"%s\" is not a palindrome\n", line);
    }
}

// Inserisce un nodo in cima alla pila
void push(stackNodePtr* topPtr, char info) {
    stackNodePtr newPtr = malloc(sizeof(stackNode));

    if(newPtr) {
        newPtr->data = info;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    }
    else {
        printf("%c not inserted. No memory available.", info);
    }
}

// Elimina un nodo dalla pila
char pop(stackNodePtr* topPtr) {
    stackNodePtr tempPtr = *topPtr;
    int popValue = (*topPtr)->data;
    *topPtr = (*topPtr)->nextPtr;
    free(tempPtr);

    return popValue;
}

int isEmpty(stackNodePtr topPtr) {
    return !topPtr;
}