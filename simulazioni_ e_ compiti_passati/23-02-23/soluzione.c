#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

unsigned int get_random() {
    static unsigned int m_w = 424242;
    static unsigned int m_z = 242424;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

struct parametri {
    char* alfabeto;
    int n;
    char* output;
};


struct parametri decodeParameters(int argc, char* argv[]) {
    if(argc!=4) {
        fprintf(stderr, "Errore: il numero di parametri passati al programma deve essere pari a 3.\n");
        fprintf(stderr, "Uso corretto: %s alfabeto n output\n", argv[0]);
        exit(-1);
    }

    struct parametri p;

    p.alfabeto = argv[1];
    p.output = argv[3];

    char *end;
    p.n = (int) strtol(argv[2], &end, 10);

    if(*end) {
        fprintf(stderr, "Errore: n non è un intero valido.\n");
        exit(-1);
    }

    if(p.n<5 || p.n>20) {
        fprintf(stderr, "Errore: n deve essere compreso tra 5 e 20 (inclusi).\n");
        exit(-1);
    }

    if(strlen(p.alfabeto)<5 || strlen(p.alfabeto)>15) {
        fprintf(stderr, "Errore: la lunghezza di alfabeto deve essere compresa tra 5 e 15 caratteri (inclusi).\n");
        exit(-1);
    }

    return p;
}

// L'utente inserisce n interi x, il cui valore viene aggiornato con la formula x = min(max(1, x), L), che vengono inseriti all'interno di un array W di lunghezza n nello stesso ordine rispetto all'inserimento
int* readInput(int n, int L) {
    int* W = calloc(n, sizeof(int));

    int x;
    for(int i = 0; i<n; i++) {
        scanf("%d", &x);
        x = x>1? x : 1;
        x = x<L? x : L;
        W[i] = x;
    }

    return W;
}

// Crea una stringa d lunghezza h costituita da caratteri casuali estratti dalla stringa alfabeto.
char* sampleString(char* alfabeto, int h) {
    char* out = calloc(h+1, sizeof(char));
    int L = strlen(alfabeto);
    for(int i=0; i<h; i++) {
        out[i] = alfabeto[get_random()%L];
    }
    out[h] = 0;
    return out;
}

// Costruisce un array di stringhe di lunghezza n i cui elementi sono stringhe di lunghezza W[i] di caratteri casuali estratti dalla stringa alfabeto.
char **getStringArray(int *W, int n, char* alfabeto) {
    char **Q = calloc(n, sizeof(char*));
    for(int i=0; i<n; i++) {
        Q[i] = sampleString(alfabeto, W[i]);
    }
    return Q;
}

typedef struct node {
    char value[20]; //va bene anche la locazione dinamica
    struct node *next;
} Node;

bool isEmpty(Node *head){
    return head==NULL;
}

bool push(Node **head, char *value) {
    Node *newNode = malloc(sizeof(Node));
    if(newNode == NULL)
        return false;

    strcpy(newNode->value, value);
    if(isEmpty(*head)) {
        newNode->next = NULL;
        *head = newNode;
        return true;
    }

    newNode->next = *head;
    *head = newNode;
    return true;
}

char* pop(Node **head) {
    if(isEmpty(*head))
        return NULL;

    Node *tmp = *head;
    *head = tmp->next;
    char* out = tmp->value;
    char* copy = calloc(strlen(out), sizeof(char));
    strcpy(copy, out);
    free(tmp);
    return copy;
}

// Inizializza una pila vuota, scorre gli elementi di Q e li inserisce nella pila. Prima di ciascun inserimento (ad eccezione del primo) controlla se la stringa Q[i] da inserire ha lunghezza dispari, in tal caso estrae la stringa che si trova in cima alla pila, la concatena con Q[i] e inserisce il risultato nella pila.
Node ** getStack(char **Q, int n) {
    Node **head = malloc(sizeof(Node*));

    push(head, Q[0]); // ERRORE-> avevo impostato il valore contenuto nel nodo head uguale a Q[0]

    for(int i=1; i<n; i++) {
        char *to_insert;
        if(strlen(Q[i])%2!=0) {
            char *top = pop(head);
            to_insert = calloc(strlen(Q[i])+strlen(top)+1, sizeof(char)); // avevo dimenticato di allocare la stringa con la giusta lunghezza
            strcpy(to_insert, top);
            strcat(to_insert, Q[i]);
        } else {
            to_insert = Q[i];
        }
        push(head, to_insert);
    }

    return head;
}

// Salva il contenuto della pila in un file output
void writeStackToFile(Node **head, char* output) {
    FILE *f = fopen(output, "w");
    if(f==NULL) {
        fprintf(stderr, "Errore nell'apertura del file %s.\n", output);
        exit(-1);
    }

    Node *aux = *head;

    while(aux) { 
        fprintf(f, "%s\n", aux->value); //ERRORE-> avevo assegnato il valore di aux->value ad una variabile char*
        aux = aux->next;
    }
    fclose(f);
}

int main(int argc, char* argv[]) {
    struct parametri p = decodeParameters(argc, argv);
    int* W = readInput(p.n, strlen(p.alfabeto));
    char **Q = getStringArray(W, p.n, p.alfabeto);
    Node **head = getStack(Q, p.n);
    writeStackToFile(head, p.output);
}