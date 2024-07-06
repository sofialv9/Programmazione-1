#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

// A
// parametri in input
struct parametri {
    char* simboli;
    int n;
    char* output; // nome del file di output
};

struct node {
    char value[20];
    struct node *next;
};
typedef struct node Node;

struct parametri decodeParameters(int argc, char* argv[]) {
    // Controlla che il numero di parametri passati sia uguale a 3
    if(argc!=4) {
        fprintf(stderr, "Errore: il numero di parametri passati al programma deve essere pari a 3.\n");
        fprintf(stderr, "Uso corretto: %s simboli n output\n", argv[0]);
        exit(-1);
    }

    struct parametri p;
    
    // salva la stringa simboli e il nome del file di output
    p.simboli = argv[1];
    p.output = argv[3];

    // controlla che l'intero inserito sia decimale e compreso tra 8 e 18
    char *end;
    p.n = (int) strtol(argv[2], &end, 10);

    if(*end) {
        fprintf(stderr, "Errore: n non è un intero valido.\n");
        exit(-1);
    }

    if(p.n<8 || p.n>18) {
        fprintf(stderr, "Errore: n deve essere compreso tra 8 e 18 (inclusi).\n");
        exit(-1);
    }
    
    // controlla che la lunghezza della stringa simboli sia compresa tra 10 e 20 caratteri (inclusi)
    if(strlen(p.simboli)<10 || strlen(p.simboli)>20) {
        fprintf(stderr, "Errore: la lunghezza di simboli deve essere compresa tra 10 e 20 caratteri (inclusi).\n");
        exit(-1);
    }

    return p;
}

// B
// Crea un array di interi W contenente n elementi uguali al fattoriale del numero x inserito dall'utente
int* readInput(int n) {
    int* W = calloc(n, sizeof(int));
    int x;

    for(int i = 0; i<n; i++) {
        scanf("%d", &x);
        W[i] = fact(x);
    }

    return W;
}

// calcola il fattoriale di x
int fact(int x) {
    int y = 1;
    for(int i = 1; i <= x; i++) {
        y *= i;
    }
    return y;
}

// stampa l'array W
void stampaArray(int arr[], int N) {
    for(int i = 0; i < N; i++) {
        printf("%5d", arr[i]);
    }
}


// C

// funzione per la generazione dei numeri casuali già fornita
unsigned int get_random() {
    static unsigned int m_w = 424242;
    static unsigned int m_z = 242424;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

char* sampleString(char* simboli, int h) {
    // allocazione dinamica di una stringa
    char* out = calloc(h + 1, sizeof(char));
    int L = strlen(simboli);
    // iterazione tra gli elementi della stringa che sono uguali a un carattere scelto casualmente tra quelli contenuti nella stringa simboli
    for(int i = 0; i < h; i++) {
        out[i] = simboli[get_random()%L];
    }
    out[h] = 0; // carattere nullo per terminare la stringa
    return out;
}

char **getStringArray(int *W, int n, char* simboli) {
    int L = strlen(simboli);
    // allocazione dinamica di un array di stringhe
    char **Q = calloc(n, sizeof(char*));
    // genera n-1 stringhe da inserire nell'array di stringhe
    for(int i = 0; i < n; i++) {
        // genera una stringa di lunghezza (W[i] mod L) e composta da caratteri casuali estratti da quest'ultima
        Q[i] = sampleString(simboli, W[i] % L);
    }
    return Q;
}
void stampaStringArray(char** arr, int N) {
    for(int i = 0; i < N; i++) {
        // stampa le N - 1 stringhe
        printf("%s\n", arr[i]);
    }
}


// D

// Controlla se la pila è vuota
bool isEmpty(Node *head){
    return head==NULL;
}

// aggiunge un nodo alla pila
bool push(Node **head, char *value) {
    Node *newNode = malloc(sizeof(Node));
    // ritorna false se non riesce ad allocare il nodo
    if(newNode == NULL)
        return false;
    // se riesce ad allocare la memoria copia il valore value nel nodo
    strcpy(newNode->value, value);
    // se la lista è vuota inserisce il nuovo nodo come cima della pila
    if(isEmpty(*head)) {
        newNode->next = NULL;
        *head = newNode;
        return true;
    }
    // altrimenti inserisce il nodo come nuova cima (dopo la cima precedente)
    newNode->next = *head;
    *head = newNode;
    return true;
}

// Estrae un nodo dalla pila
char* pop(Node **head) {
    // se la lista è vuota ritorna NULL
    if(isEmpty(*head))
        return NULL;
    // sposta la cima all'elemento successivo nella pila
    Node *tmp = *head;
    *head = tmp->next;
    // salva e restituisce il valore del nodo estratto e libera la memoria non più occupata
    char* out = tmp->value;
    char* copy = calloc(strlen(out), sizeof(char));
    strcpy(copy, out);
    free(tmp);
    return copy;
}

// crea una stringa contenente i caratteri di Q[i] contenuti nella stringa estratta
char* common(char *a, char *b) {
    // allocazione dinamica di una stringa
    char* out = calloc(strlen(a), sizeof(char)); // ERRORE: messo strlen(a) + 1
    int h = 0; // lunghezza della nuova stringa
    // ciclo lungo la stringa a (Q[i]) e la stringa b (quella estratta)
    for(int i = 0; i < strlen(a); i++) {
        for(int j = 0; j < strlen(b); j++) {
            // se i caratteri corrispondenti nelle 2 stringhe coincidono il carattere viene copiato nella nuova stringa
            if(a[i] == b[j]) {
                out[h++] = a[i];
                // con il break si esce dal for più interno
                break; // ERRORE: l'ho dimenticato
            }
        }
    }
    return out;
}

Node ** getStack(char **Q, int n) {
    Node **head = malloc(sizeof(Node*));

    // inserisce il primo elemento di Q (la prima stringa) nello stack
    push(head, Q[0]);

    for(int i = 1; i < n; i++) {
        char *to_insert;
        // se la lunghezza della stringa Q[i] è pari la stringa da inserire coincide con Q[i]
        if(strlen(Q[i]) % 2 == 0)
            to_insert = Q[i];
        // altrimenti estrae la stringa attualmente in cima nello stack e la stringa da inserire è quella contenente i caratteri di Q[i] che appaiono nella stringa estratta (nell'ordine in cui appaiono in Q[i])
        else {
            char *top = pop(head); // stringa estratta
            to_insert = common(Q[i], top); // stringa da inserire
        }
        // inserisce la stringa da inserire in cima alla pila
        push(head, to_insert);
    }

    return head;
}

// stampa la pila
void stampaStack(Node **head) {
    Node *aux = *head;

    while(aux) {
        printf("%s\n", aux->value);
        aux = aux->next;
    }
}


// E

void writeStackToFile(Node **head, char* output) {
    FILE *f = fopen(output, "w");
    // se non riesce ad aprire il file dà errore
    if(f == NULL) {
        fprintf(stderr, "Errore nell'apertura del file %s.\n", output);
        exit(-1);
    }

    // stampa la pila sul file di output e chiude il file
    Node *aux = *head;
    while(aux) {
        fprintf(f, "%s\n", aux->value);
        aux = aux->next;
    }
    fclose(f);
}


////////////////////   FUNZIONE MAIN   /////////////////////////

int main(int argc, char* argv[]) {
    // decodifica i parametri in input e li stampa
    struct parametri p = decodeParameters(argc, argv);
    printf("Punto A - Parametri: simboli = %s, output=%s, n = %d\n", p.simboli, p.output, p.n);
    
    // crea e stampa un array W di lunghezza n contenente i fattoriali dei numeri dati in input dall'utente
    int* W = readInput(p.n);
    printf("\nPunto B - Contenuto di W:\n");
    stampaArray(W, p.n);
    
    // costruisce e stampa un array di stringhe Q di lunghezza n in cui Q[i] è una stringa di lunghezza W[i] mod L costituita da caratteri casuali estratti dalla stringa simboli e dove L è la lunghezza della stringa simboli.
    char **Q = getStringArray(W, p.n, p.simboli);
    printf("\n\nPunto C - Contenuto di Q:\n");
    stampaStringArray(Q, p.n);
    
    // inizializza una pila vuota, scorre gli elementi dell'array Q e se la stringa ha lunghezza (h) pari o se si tratta del primo inserimento della pila inserisce la stringa in cima alla pila, se h è dispari il programma estrae (pop) la stringa a in cima alla pila e inserisce la stringa b contenente i caratteri di Q[i] che appaiono in a nell'ordine in cui appaiono in Q[i]. Stampa la pila.
    Node **head = getStack(Q, p.n);
    printf("\n\nPunto D - Contenuto della pila:\n");
    stampaStack(head);

    // salva il contenuto della pila sul file di output
    writeStackToFile(head, p.output);
}