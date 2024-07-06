#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct parametri{
    int n;
    int m;
    int p;
} Parametri;

Parametri readInput(int argc, char* argv[]){
    Parametri p;
    if(argc != 4){
        fprintf(stderr, "Uso: %s n m p.\n", argv[0]);
        exit(-1);
    }
    
    char* end;
    p.n = (int) strtol(argv[1], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: n deve essere un intero.\n");
        exit(-1);
    }
    if(p.n < 0){
        fprintf(stderr, "Errore: n deve essere un intero positivo.\n");
        exit(-1);
    }
    p.m = (int) strtol(argv[2], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: m deve essere un intero.\n");
        exit(-1);
    }
    if(p.m < 0){
        fprintf(stderr, "Errore: m deve essere un intero positivo.\n");
        exit(-1);
    }
    p.p = (int) strtol(argv[3], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: p deve essere un intero.\n");
        exit(-1);
    }
    if(p.p < 0){
        fprintf(stderr, "Errore: p deve essere un intero positivo.\n");
        exit(-1);
    }

    return p;
}

// Inizializza un array tridimensionale di puntatori ad intero
int*** initArray(int n, int m, int p){
    int*** A = calloc(n, sizeof(int**));
    for(int i = 0; i < n; i++){
        A[i] = calloc(m, sizeof(int*));
        for(int j = 0; j < m; j++){
            A[i][j] = calloc(p, sizeof(int));
            for(int k = 0; k < p; k++){
                scanf("%d", &A[i][j][k]);
            }
        }
    }
    return A;
}

// Crea un array di puntatori ad interi tale che i suoi elementi puntino al valore massimo contenuto nella matrice m x p individuata da A[i]
int** initB(int*** A, int n, int m, int p){
    int** B = calloc(n, sizeof(int*));
    for(int i = 0; i < n; i++){
        // inizializza il massimo come puntatore al primo valore della matrice m x p A[i]
        int* max = &A[i][0][0];// ERRORE-> ho inizializzato max a intero e non a puntatore a intero
        for(int j = 0; j < m; j++){
            for(int k = 0; k < p; k++){
                if(A[i][j][k] > *max){
                    max = &A[i][j][k];
                }
            }
        }
        // L'i-esimo elemento dell'array B è un puntatore al valore massimo trovato
        B[i] = max;
    }
    return B;
}

typedef struct node{
    int data;
    struct node* next;
} Node;

void push(Node** head, int n){
    Node* new = malloc(sizeof(Node));
    if(!new){
        fprintf(stderr, "Errore di allocazione della memoria.\n");
        exit(-1);
    }

    new->data = n;
    new->next = *head;
    *head = new;
}

// Inserisce gli elementi puntati da B in una pila
Node** initStack(int** B, int n){
    Node** head = malloc(sizeof(Node*));
    *head = NULL;

    for(int i = 0; i < n; i++){
        push(head, *(B[i]));
    }

    return head;
}

int pop(Node** head){
    int out = (*head)->data;
    Node* tmp = *head;
    *head = (*head)->next;
    free(tmp);
    return out;
}

// Scrive in un file di testo i valori puntati da B in senso inverso
void saveStack(char* fname, Node** head){
    FILE* fPtr = fopen(fname, "w");
    if(!fPtr){
        fprintf(stderr, "Errore: impossibile aprire il file %s.\n", fname);
        exit(-1);
    }

    while(*head){
        fprintf(fPtr, "%d\n", pop(head));
    }

    fclose(fPtr);
}

int main(int argc, char* argv[]){
    Parametri p = readInput(argc, argv);

    int*** A = initArray(p.n, p.m, p.p);

    int** B = initB(A, p.n, p.m, p.p);

    Node** head = initStack(B, p.n);

    saveStack("out.txt", head);
}