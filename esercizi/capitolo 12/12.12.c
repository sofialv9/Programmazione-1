// Non funziona
// Convertitore da infisso (operatore tra gli operandi) a postfisso (operatore dopo gli operandi)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXCOLS 100

typedef struct stackNode {
    char data;
    struct stackNode* nextPtr;
} StackNode;
typedef StackNode* StackNodePtr;

void convertToPostfix(char inFix[], char postFix[]);
int isOperator(char c);
int precedence(char operator1, char operator2);
void push(StackNodePtr* topPtr, char info);
char pop(StackNodePtr* topPtr);
char stackTop(StackNodePtr topPtr);
int isEmpty(StackNodePtr topPtr);
void printStack(StackNodePtr currentPtr);

int main() {
    char c; // carattere corrente dall'espressione
    char inFix[MAXCOLS]; // espressione in notazione infissa
    int pos = 0; // variabile di indicizzazione

    puts("Enter the infix expression.");

    // legge ciascun carattere
    while((c = getchar()) != '\n') {
        // elimina gli spazi
        if(c != ' ') {
            inFix[pos++] = c;
        }
    }

    inFix[pos] = '\0';
    char postFix[MAXCOLS]; // espressione in notazione postfissa

    // stampa l'espressione infissa, la converte in postfissa e la stampa nuovamente
    printf("%s\n%s\n", "The original infix expression is:", inFix);
    convertToPostfix(inFix, postFix);
    printf("The expression in postfix notation is:\n%s\n", postFix);
}

// Converte l'espressione infissa in postfissa
void convertToPostfix(char inFix[], char postFix[]) {
    StackNodePtr stackPtr = NULL; // puntatore alla cima della pila

    // inserisce una parentesi sinistra sulla pila
    push(&stackPtr,'(');
    printStack(stackPtr);

    // aggiunge una parentesi destra all'espressione infissa
    strcat(inFix, ")");
    
    int j;
    // converte l'espressione infissa in postfissa finché la pila non è vuota
    for(int i = 0, j = 0; stackTop(stackPtr); ++i) {
        // se il carattere corrente in inFix è una cifra si copia nel successivo elemento di postFix
        if(isdigit(inFix[i])) {
            postFix[j++] = inFix[i];
        }
        // se il carattere è una parentesi sinistra si inserisce con una push sulla pila
        else if(inFix[i] == '(') {
            push(&stackPtr, '(');
            printStack(stackPtr);
        }
        // se il carattere è un operatore si estraggono gli operatori (se ve ne sono) dalla cima della pila finché questi non hanno precedenza uguale o maggiore rispetto all'operatore corrente, si inseriscono gli operatori estratti in postfix e si inserisce il carattere corrente in infix nella pila
        else if(isOperator(inFix[i])) {
            int higher = 1; // usato per memorizzare il valore del test precedente

            // ripete finché l'operatore corrente non ha la precedenza più alta
            while(higher) {
                // se la cima della pila è un operatore
                if(isOperator(stackTop(stackPtr))) {
                    // confronta la precedenza degli operatori
                    if(precedence(stackTop(stackPtr), inFix[i])) {
                        postFix[j++] = pop(&stackPtr);
                        printStack(stackPtr);
                    }
                    else {
                        higher = 0; // ripristina il flag
                    }
                }
                else {
                    higher = 0; // ripristina il flag
                    }
            }
            push(&stackPtr, inFix[i]);
            printStack(stackPtr);
        }
        // se il carattere è una parentesi destra si estraggono gli operatori dalla cima della pila e si inseriscono in postfix finché non compare una parentesi sinistra in cima alla pila la quale viene poi eliminata
        else if (inFix[i] == ')') {
            char popValue; // valore del nodo eliminato

            // effettua pop sulla pila finché il valore eliminato non è una parentesi sinistra
            while((popValue = pop(&stackPtr)) != '(') {
                printStack(stackPtr);
                postFix[j++] = popValue;
            }
            printStack(stackPtr);
        }
    }
    postFix[j] = '\0';
}

// Controlla se c è un operatore
int isOperator(char c) {
    // se c è un operatore restituisce vero
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        return 1;
    }
    else {
        return 0;
    }
}

// Restituisce vero se la precedenza di operator1 è maggiore o uguale a quella di operator2
int precedence(char operator1, char operator2) {
    // confronta la precedenza dei due operatori
    if(operator1 == '^') {
        return 1;
    }
    else if(operator2 == '^') {
        return 0;
    }
    else if (operator1 == '*' || operator1 == '/'){
        return 1;
    }
    else if (operator1 == '+' || operator1 == '-'){
        if (operator2 == '*' || operator2  == '/') {
            return 0;
        }
        else {
            return 1;
        }
    }
    return 0; // default
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

// Elimina un nodo dalla cima della pila
char pop(StackNodePtr* topPtr) {
    StackNodePtr tempPtr = *topPtr;
    char popValue = (*topPtr)->data;
    *topPtr = (*topPtr)->nextPtr;
    free(tempPtr);

    return popValue; // restituisce il valore del nodo eliminato
}

// Visualizza l'elemento in cima alla pila
char stackTop(StackNodePtr topPtr) {
    // se la pila non è vuota
    if(!isEmpty(topPtr)) {
        return topPtr->data;
    }
    else {
        return 0;
    }
}

// Verifica se la pila è vuota
int isEmpty(StackNodePtr topPtr) {
    return !topPtr; // restituisce NULL se la pila è vuota
}

// Stampa la pila
void printStack(StackNodePtr currentPtr) {
    // se la pila è vuota
    if(currentPtr == NULL) {
        puts("The stack is empty.\n");
    }
    else {
        while(currentPtr != NULL) {
            printf("%c  ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
        puts("NULL");
    }
}