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

typedef struct parameters{
    int n;
    char w;
} Parameters;

Parameters readInput(int argc, char* argv[]){
    Parameters p;
    if(argc != 3){
        fprintf(stderr, "Uso: %s n w.\n", argv[0]);
        exit(-1);
    }

    char* end;
    p.n = (int) strtol(argv[1], &end, 10);
    if(*end){
       fprintf(stderr, "Errore: n è un intero non valido.\n");
        exit(-1); 
    }
    if(p.n < 10 || p.n > 20){
        fprintf(stderr, "Errore: n deve essere compreso tra 10 e 20 (estremi inclusi).\n");
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

bool isEmpty(Node* head){
    return head == NULL;
}

// Genera una stringa di una lunghezza casuale tra 5 e 15 e con caratteri casuali tra a e z
char* genString(){
    int L = get_random() % 11 + 5;
    char* out = calloc(L, sizeof(char));
    for(int i = 0; i < L; i++){
        out[i] = get_random() % ('z' - 'a' + 1) + 'a';
    }
    return out;
}

void insertHead(Node** head, char* string){
    Node* newNode = malloc(sizeof(Node));
    if(!newNode){
        fprintf(stderr, "Errore di allocazione della memoria.\n");
    }
    newNode->data = string;

    // se la lista è vuota
    if(*head == NULL){
        *head = newNode;
        (*head)->next = NULL;
    // se la lista non è vuota ma il nodo deve essere inserito in testa
    } else {
        newNode->next = *head;
        *head = newNode;
    }
}

// Inserisce la stringa nella lista
void insertString(Node** head, char* string){
    // Se la lista è vuota la inserisce in testa
    if(isEmpty(*head)){
        insertHead(head, string);
        return;
    }

    Node* ptr = *head;
    Node* prev = NULL;

    // inserisce la stringa in ordine lessografico ascendente
    while(ptr && strcmp(ptr->data, string) < 0){
        prev = ptr;
        ptr = ptr->next;
    }

    // se non si è entrati nel ciclo (prev==NULL) vuol dire che la stringa deve essere inserita in testa (prima di ptr)
    if(!prev){
        insertHead(head, string);
        return;
    }
    
    // inserisce la stringa tra prev e ptr
    Node* newNode = malloc(sizeof(Node));
    if(!newNode){
        fprintf(stderr, "Errore di allocazione della memoria.\n");
    }
    newNode->data = string;
    prev->next = newNode;
    newNode->next = ptr;
}

// Crea la lista formata da stringhe
Node** genList(int n){
    Node** head = malloc(sizeof(Node*));
    *head = NULL;

    for(int i = 0; i < n; i++){
        // genera la stringa con caratteri e lunghezza casuale
        char* string = genString();
        // inserisce la stringa nella lista
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

// Stampa le occorrenze di un carattere nelle stringhe all'interno della lista
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
    printf("Le occorrenze del carattere '%c' nella lista sono %d.\n", w, count);
}

int main(int argc, char* argv[]){
    // A
    Parameters p = readInput(argc, argv);

    // B - genera una lista concatenata ordinata in modo crescente contenente N stringhe con caratteri tra a e z e con una lunghezza nell'intervallo [5, 15]
    Node** L = genList(p.n);

    // C
    printList(L);

    // D
    printOcc(L, p.w);
}