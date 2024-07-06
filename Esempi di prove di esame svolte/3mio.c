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
    int N;
    char w;
} Parameters;

Parameters readInput(int argc, char* argv[]){
    Parameters p;
    if(argc != 3){
        fprintf(stderr, "Uso: %s N w.\n", argv[0]);
        exit(-1);
    }

    char* end;
    p.N = (int) strtol(argv[1], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: N deve essere un intero.\n");
        exit(-1);
    }
    if(p.N < 10 || p.N > 20){
        fprintf(stderr, "Errore: N deve essere compreso tra 10 e 20 (estremi inclusi).\n");
        exit(-1);
    }

    if(strlen(argv[2]) != 1){
        fprintf(stderr, "Errore: w deve essere un carattere.\n");
        exit(-1);
    }
    p.w = argv[2][0];

    return p;
}

typedef struct node{
    char* data;
    struct node* next;
} Node;

char* genString(){
    int L = get_random() % 11 + 5;
    char* out = calloc(L, sizeof(char));
    for(int i = 0; i < L; i++){
        char c = get_random() % ('z' -'a' + 1) + 'a';
        out[i] = c;
    }
    return out;
}

bool isEmpty(Node* head){
    return head == NULL;
}

void insertHead(Node** head, char* s){
    if(isEmpty(*head)){
        *head = malloc(sizeof(Node));
        (*head)->data = s;
        (*head)->next = NULL;
    } else {
        Node* new = malloc(sizeof(Node));
        if(!new){
            fprintf(stderr, "Errore di allocazione della memoria.\n");
            exit(-1);
        }
        new->data = s;
        new->next = *head;
        *head = new;
    }
}

void insertString(Node** head, char* s){
    if(isEmpty(*head)){
        insertHead(head, s);
        return;
    }

    Node* ptr = *head;
    Node* prev = NULL;

    while(ptr && strcmp(s, ptr->data) > 0){
        prev = ptr;
        ptr = ptr->next;
    }
    if(!prev){
        insertHead(head, s);
        return;
    }

    Node* new = malloc(sizeof(Node));
    if(!new){
        fprintf(stderr, "Errore di allocazione della memoria.\n");
        exit(-1);
    }
    new->data = s;
    prev->next = new;
    new->next = ptr;
}

Node** genList(int n){
    Node** head = malloc(sizeof(Node*));
    *head = NULL;

    for(int i = 0; i < n; i++){
        char* string = genString();
        insertString(head, string);
    }
    return head;
}

void printList(Node** head){
    Node* aux = *head;
    while(aux){
        printf("%s\n", aux->data);
        aux = aux->next;
    }
}

void printOcc(Node** head, char w){
    Node* aux = *head;
    int count = 0;

    while(aux){
        char* s = aux->data;
        for(int i = 0; i < strlen(s); i++){
            if(s[i] == w){
                count++;
            }
        }
        aux = aux->next;
    }
    printf("Il numero totale di occorrenze di %c: %d\n", w, count);
}

int main(int argc, char* argv[]){
    Parameters p = readInput(argc, argv);

    Node** head = genList(p.N);
    printList(head);

    printOcc(head, p.w);
}