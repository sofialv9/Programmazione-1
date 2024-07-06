#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct parameters{
    int n;
    int m;
    int p;
} Parameters;

Parameters readInput(int argc, char* argv[]){
    Parameters p;
    if(argc != 4){
        fprintf(stderr, "Uso: %s n m p.\n", argv[0]);
        exit(-1);
    }

    char* end;
    p.n = strtol(argv[1], &end, 10);
    if(p.n < 0){
        fprintf(stderr, "Errore: n deve essere un intero positivo.\n");
        exit(-1);
    }
    p.m = strtol(argv[2], &end, 10);
    if(p.m < 0){
        fprintf(stderr, "Errore: m deve essere un intero positivo.\n");
        exit(-1);
    }
    p.p = strtol(argv[3], &end, 10);
    if(p.p < 0){
        fprintf(stderr, "Errore: p deve essere un intero positivo.\n");
        exit(-1);
    }

    return p;
}

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

int** initB(int*** A, int n, int m, int p){
    int** B = calloc(n, sizeof(int*));
    for(int i = 0; i < n; i++){
        int* max = &A[i][0][0];
        for(int j = 0; j < m; j++){
            for(int k = 0; k < p; k++){
                if(A[i][j][k] > *max){
                    max = &A[i][j][k];
                }
            }
        }
        B[i] = max;
    }
    return B;
}

typedef struct node{
    int data;
    struct node* next;
} Node;

bool isEmpty(Node* head){
    return head == NULL;
}

void insertNode(Node** head, int n){

    if(isEmpty(*head)){
        *head = malloc(sizeof(Node));
        (*head)->data = n;
        (*head)->next = NULL;
    }

    Node* new = malloc(sizeof(Node));
    new->data = n;
    new->next = *head;
    *head = new;
}

Node** initStack(int** B, int n){
    Node** head = malloc(sizeof(Node*));
    *head = NULL;

    for(int i = 0; i < n; i++){
        insertNode(head, *B[i]);
    }

    return head;
}

int pop(Node** head){
    if(isEmpty(*head)){
        fprintf(stderr, "Errore: la pila è vuota.\n");
        exit(-1);
    }

    int out = (*head)->data;
    Node* tmp = *head;
    *head = (*head)->next;
    free(tmp);
    return out;
}

void saveStack(char* fname, Node** head){
    FILE* fPtr = fopen(fname, "w");
    if(!fPtr){
        fprintf(stderr, "Errore: impossibile aprire il file %s.\n", fname);
        exit(-1);
    }

    while(!isEmpty(*head)){
        fprintf(fPtr, "%d\n", pop(head));
    }

    fclose(fPtr);
}


int main(int argc, char* argv[]){
    Parameters p = readInput(argc, argv);
    
    int*** A = initArray(p.n, p.m, p.p);

    int** B = initB(A, p.n, p.m, p.p);

    Node** head = initStack(B, p.n);

    saveStack("out.txt", head);
}