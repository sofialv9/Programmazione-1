#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

int readInput(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Uso: %s n.\n", argv[0]);
        exit(-1);
    }

    char* end;
    int n = (int) strtol(argv[1], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: n deve essere un intero.\n");
        exit(-1);
    }
    if(n < 0){
        fprintf(stderr, "Errore: n deve essere un intero positivo.\n");
        exit(-1);
    }

    return n;
}

typedef struct node{
    char data;
    struct node* next;
} Node;

bool isEmpty(Node* head){
    return head == NULL;
}

//ERRORE -> non ho fatto questa funzione
// Genera un carattere casuale da una stringa di caratteri
char getRandomChar(char* s){
    return s[get_random() % strlen(s)];
}

// Genera un carattere casuale scelto tra le vocali
char genVowel(){
    return getRandomChar("aeiouAEIOU");
}

// Genera una consonante casuale
char genConsonant(){
    return getRandomChar("bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ");
}

void push(Node** head, char c){
    Node* new = malloc(sizeof(Node));
    if(!new){
        fprintf(stderr, "Errore di allocazione della memoria.\n");
        return;
    }

    new->data = c;
    new->next = *head;
    *head = new;
}

char pop(Node** head){
    if(isEmpty(*head)){
        fprintf(stderr, "Errore: pila vuota.\n");
        exit(-1);
    }

    char c = (*head)->data;
    Node* tmp = *head;
    *head = (*head)->next;
    free(tmp);
    return c;
}

// Converte un carattere in un intero
int charToInt(char c){
    char tmp[2];
    tmp[0] = c;
    tmp[1] = 0;
    char* end = malloc(sizeof(char));
    int x = (int) strtol(tmp, &end, 0);
    return x;
}

// Genera una pila con n operazioni di inserimento (push); genera un carattere casuale x tra 1 e 9, se x è un numero in [1,4] procede a x operazioni di inserimento di una vocale casuale, altrimenti a x operazioni di inserimento di una consonante.
Node** fillStack(int n){
    Node** head = malloc(sizeof(Node*));
    *head = NULL;

    for(int i = 0; i < n; i++){
        // ERRORE -> ho usato solo get_random
        char x = getRandomChar("123456789");

        if(x >= '1' && x <= '4'){
            // ERRORE -> dimenticato di convertire x in un intero per usarlo come valore limite nel ciclo
            for(int i = 0; i < charToInt(x); i++){
                push(head, genVowel());
            }
            push(head, x);
        } else {
            for(int i = 0; i < charToInt(x); i++){
                char c = genConsonant();
                if(c == 'v'){
                    c = '*';
                } else if (c == 'w'){
                    c = '?';
                }
                push(head, c);
            }
            push(head, x);
        }
    }
    return head;
}

// Genera un array di stringhe di lunghezza n svuotando lo stack: per generare una stringa dell'array si estrae un carattere dalla pila e lo si converte in intero per usarlo come contatore per x operazioni di pop ottenendo i caratteri da inserire nelle stringhe.
char** emptyStack(Node** head, int n){
    char** A = calloc(n, sizeof(char*));
    int i = 0;

    while(!isEmpty(*head)){
        char c = pop(head);
        int x = charToInt(c);
        A[i] = calloc(x + 1, sizeof(char));
        for(int j = 0; j < x; j++){
            A[i][j] = pop(head);
        }
        i++;
    }
    
    return A;
}

void printArray(char** array, int n){
    for(int i = 0; i < n; i++){
        printf("%s\n", array[i]);
    }
}

int main(int argc, char* argv[]){
    int n = readInput(argc, argv);

    Node** head = fillStack(n);

    char** A = emptyStack(head, n);
    printArray(A, n);
}