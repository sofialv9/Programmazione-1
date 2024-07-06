#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

typedef struct parameters{
    char* filename;
    int n;
} Parameters;

Parameters decodeParameters(int argc, char* argv[]){
    Parameters p;

    if(argc != 3){
        fprintf(stderr, "Uso: %s filename n.\n", argv[0]);
        exit(-1);
    }

    p.filename = argv[1];
    char* extension = strrchr(p.filename, '.');
    if(strcmp(extension, ".bin") != 0){
        fprintf(stderr, "Errore: filename deve avere estensione \".bin\".\n");
        exit(-1);
    }

    char* end;
    p.n = strtol(argv[2], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: n è un intero non valido.\n");
        exit(-1);
    }

    if(p.n < 3 || p.n > 5){
        fprintf(stderr, "Errore: n deve essere compreso tra 3 e 5.\n");
        exit(-1);
    }

    return p;
}

typedef struct record{
    int numeroConto;
    char nome[255];
    char cognome[255];
    double saldo;
} Record;

typedef struct node{
    Record data;
    struct node* next;
} Node;

Record readRecord(){
    if(!feof(stdin)){
        Record r;
        scanf("%d %s %s %lf\n", &r.numeroConto, r.nome, r.cognome, &r.saldo);
        return r;
    } else {
        exit(-1);
    }
}

bool insertHead(Node** head, Record data){
    Node* newNode = malloc(sizeof(Node));
    if(!newNode){
        fprintf(stderr, "Errore di allocazione della memoria.\n");
        return false;
    }

    *head = newNode;
    newNode->data = data;
    newNode->next = NULL;
    return true;
}

bool insertNode(Node* node, Record data){
    Node* newNode = malloc(sizeof(Node));
    if(!newNode){
        fprintf(stderr, "Errore di allocazione della memoria.\n");
        return false;
    }

    newNode->data = data;
    newNode->next = node->next;
    node->next = newNode;
    return true;
}


Node** loadRecords(){
    Node** head = malloc(sizeof(Node*));
    *head = NULL;
    while(!feof(stdin)){
        Record r = readRecord();

        if(*head == NULL){
            insertHead(head, r);
        } else {
            Node* ptr = *head;
            while(ptr->next){
                ptr = ptr->next;
            }
            insertNode(ptr, r);
        }
    }
    return head;
}

void printList(Node** head){
    Node* aux = *head;
    while(aux){
        Record r = aux->data;
        printf("%d %s %s %.2f\n", r.numeroConto, r.nome, r.cognome, r.saldo);
        aux = aux->next;
    }
    puts("\n");
}

int listlen(Node** head){
    Node* aux = *head;
    int count = 0;
    while(aux){
        count++;
        aux = aux->next;
    }
    return count;
}

Record* getArray(Node** head, int lenght){
    Record* X = calloc(lenght + 1, sizeof(Record));
    if(!X){
        fprintf(stderr, "Errore di allocazione della memoria.\n");
        return 0;
    }

    Node* aux = *head;
    int i = 0;
    while(aux){
        X[i++] = aux->data;
        aux = aux->next;
    }
    return X;
}

// selection sort
void sort(Record* X, int lenght){
    float m = 0;
    for(int i = 0; i < lenght; i++){
        m += X[i].saldo;
    }
    m /= lenght;

    for(int i = 0; i < lenght - 1; i++){
        int smallest = i;
        for(int j = i + 1; j < lenght; j++){
            if((X[j].saldo - m) * (X[j].saldo - m) < (X[smallest].saldo - m) * (X[smallest].saldo - m)){
                smallest = j;
            }
        }
        Record tmp = X[i];
        X[i] = X[smallest];
        X[smallest] = tmp;
    }
}

void printArray(Record* X, int lenght){
    for(int i = 0; i < lenght; i++){
        Record r = X[i];
        printf("%d %s %s %.2f\n", r.numeroConto, r.nome, r.cognome, r.saldo);
    }
    puts("\n");
}

void saveToFile(Record* X, int lenght, char* fname){
    FILE* fPtr = fopen(fname, "wb");
    if(!fPtr){
        fprintf(stderr, "Errore: impossibile aprire il file %s.\n", fname);
        return;
    }

    for(int i = 0; i < lenght; i++){
        fwrite(&X[i], sizeof(Record), 1, fPtr);
    }

    fclose(fPtr);
}

int* randomOrder(int n){
    int* order = calloc(n, sizeof(int));

    for(int i = 0; i < n; i++){
        order[i] = i;
    }

    for(int i = 0; i < n; i++){
        int j = get_random() % n;
        int tmp = order[i];
        order[i] = order[j];
        order[j] = tmp;
    }

    return order;
}

void showFileContent(char* fname, int n){
    FILE* fPtr = fopen(fname, "rb");
    if(!fPtr){
        fprintf(stderr, "Errore: impossibile aprire il file %s.\n", fname);
        return;
    }

    int* order = randomOrder(n);
    for(int i = 0; i < n; i++){
        fseek(fPtr, order[i] * sizeof(Record), SEEK_SET);
        Record r;
        if(fread(&r, sizeof(Record), 1, fPtr) == 1){
            printf("%d %s %s %.2f\n", r.numeroConto, r.nome, r.cognome, r.saldo);
        }
    }
    
    fclose(fPtr);
}

int main(int argc, char* argv[]){
    Parameters p = decodeParameters(argc, argv);
    printf("Parametri:\n filename: %s\n n: %d\n\n", p.filename, p.n);

    Node** L = loadRecords();
    printf("Stampa L:\n");
    printList(L);

    Record* X = getArray(L, listlen(L));
    sort(X, listlen(L));
    printf("Contenuto di X dopo l'ordinamento:\n");
    printArray(X, listlen(L));
    

    saveToFile(X, listlen(L), p.filename);
    printf("Contenuto del file binario in ordine casuale:\n");
    showFileContent(p.filename, p.n);
}