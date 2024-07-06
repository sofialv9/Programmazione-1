#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct parameters{
    int n;
    char* inputFileName;
} Parameters;

Parameters decodeParameters(int argc, char* argv[]){
    Parameters p;

    if(argc != 3){
        fprintf(stderr, "Uso: %s n inputFileName.\n", argv[0]);
        exit(-1);
    }

    char* end;
    p.n = (int) strtol(argv[1], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: n è un intero non valido.\n");
        exit(-1);
    }
    if(p.n < 5 || p.n > 20){
        fprintf(stderr, "Errore: n deve essere compreso tra 5 e 20 (estremi inclusi).\n");
        exit(-1);
    }

    p.inputFileName = argv[2];
    char* extension = strrchr(p.inputFileName, '.');
    if(strcmp(extension, ".dat") != 0){
        fprintf(stderr, "Errore: inputFileName deve avere estensione \".dat\".\n");
        exit(-1);
    }

    return p;
}

int* readInput(char* fname, int* size){
    FILE* fPtr = fopen(fname, "r");
    if(!fPtr){
        fprintf(stderr, "Erroe: impossibile aprire il file %s.\n", fname);
        exit(-1);
    }

    int capacity = 10;
    int* A = (int*) calloc(capacity, sizeof(int));
    if(!A){
        fclose(fPtr);
        fprintf(stderr, "Errore di allocazione della memoria.\n");
        exit(-1);
    }

    int num;
    *size = 0;
    while(fscanf(fPtr, "%d", &num) == 1){
        if(capacity == *size){
            capacity *= 2;
            A = (int*) realloc(A, capacity * sizeof(int));
            if(!A){
                fclose(fPtr);
                fprintf(stderr, "Errore di allocazione della memoria.\n");
                exit(-1); 
            }
        }
        A[(*size)++] = num;
    }

    fclose(fPtr);
    return A;
}

void printArray(int* A, int size){
    for(int i = 0; i < size; i++){
        printf("%d\n", A[i]);
    }
}

typedef struct node{
    float data;
    struct node* next;
} Node;

bool push(Node** head, float f){
    Node* newNode = malloc(sizeof(Node));
    if(!newNode){
        fprintf(stderr, "Errore di allocazione della memoria.\n");
        return false;
    }

    newNode->data = f;
    newNode->next = *head;
    *head = newNode;
    return true;
}

float pop(Node** head){
    Node* tmp = *head;
    float out = tmp->data;
    *head = tmp->next;
    free(tmp);
    return out;
}

Node** createStack(int* A, int size, int n){
    Node** head = malloc(sizeof(Node*));
    *head = NULL;

    for(int i = 0; i < size; i++){
        if(A[i] % n == 0){
            push(head, A[i]);
        } else {
            if(*head != NULL){
                float x = pop(head);
                float media = (x + A[i]) / 2;
                push(head, media);
            }
        }
    }

    return head;
}

void printStack(Node** head){
    Node* aux = *head;

    while(aux){
        printf("%.2f\n", aux->data);
        aux = aux->next;
    }
}

void findMinMaxMean(Node** head, float* min, float* max, float* mean){
    Node* aux = *head;
    *min = aux->data;
    *max = *min;
    *mean = *min;
    int count = 1;

    while(aux->next){
        aux = aux->next;
        float f = aux->data;
        if(f > *max){
            *max = f;
        }
        if(f < *min){
            *min = f;
        }
        *mean += f;
        count++;
    }

    *mean /= count;
}

int main(int argc, char* argv[]){
    // A
    Parameters p = decodeParameters(argc, argv);
    printf("Punto A - Parametri inseriti: n= %d,\ninputFileName=%s\n\n", p.n, p.inputFileName);

    // B
    int size;
    int* A = readInput(p.inputFileName, &size);
    printf("Punto B - Contenuto di A:\n");
    printArray(A, size);

    // C
    Node** P = createStack(A, size, p.n);
    printf("\nPunto C - Contenuto di P:\n");
    printStack(P);

    // D
    float min, max, mean;
    findMinMaxMean(P, &min, &max, &mean);
    printf("\nPunto D:\nValore minimo: %.2f\nValore massimo: %.2f\nValore medio: %.2f\n", min, max, mean);
}