#define MAXLEN 255
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

struct parameters {
    char filename[MAXLEN];
    int n;
};

struct record {
    int numeroConto;
    char nome[MAXLEN];
    char cognome[MAXLEN];
    double balance;
};

struct node {
    struct record data;
    struct node* next;
};

typedef struct record Record;
typedef struct parameters Parameters;
typedef struct node Node;

void insertRecord(Node** head, Record record) {
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Errore di allocazione della memoria");
    }

    newNode->data = record;
    newNode->next = NULL; //ERRORE-> dimenticato di scrivere

    return newNode;

    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void printRecords(Node* head) {
    Node* current = head;

    while (current != NULL) {
        Record r = current->data;
        printf("%d %s %s %.2f\n", r.numeroConto, r.nome, r.cognome, r.balance);
        current = current->next;
    }
}

int listlen(Node* head) {
    Node* current = head;
    int i = 0;

    while (current != NULL) { 
        i++;
        current = current->next;
    }

    return i;
}

Parameters decodeParameters(int argc, char *argv[]) {
    Parameters p;

    if(argc != 3) {
        fprintf(stderr, "Errore, il numero di parametri deve essere uguale a 2\n");
        exit(-1);
    }

    strcpy(p.filename, argv[1]);

    int i = strlen(p.filename)-4;

    if(strcmp(p.filename+strlen(p.filename)-4, ".bin")!=0) {
        fprintf(stderr, "Errore, il nome del file non termina con '.bin'\n");
        exit(-1);
    }

    char *end;
    p.n = (int) strtol(argv[2], &end, 10);

    if(*end) {
        fprintf(stderr, "Errore: n non è un intero valido.\n");
        exit(-1);
    }

    if(p.n<3 || p.n>5) {
        fprintf(stderr, "Errore: n deve essere compreso tra 3 e 5.\n");
        exit(-1);
    }

    return p;
}

// Dichiara un array X di struct Record e copia i record della lista L in X.
Record* getArray(Node *head) {
    Record* X = calloc(listlen(head), sizeof(Record));
    Node *ptr = head;
    int i = 0;

    while(ptr) {
        X[i++] = ptr->data;
        ptr = ptr->next;
    }
    return X;
}

void printArray(Record *X, int len) {
    for(int i=0; i<len; i++) {
        printRecord(X[i]);
    }
}

Record readRecord() {
    Record r;
    scanf("%d %s %s %lf", &r.numeroConto, r.nome, r.cognome, &r.balance);
    return r;
}

// Chiede all'utente di inserire un numer arbitrario di record bancari separati da caratteri di invio. Ciascun record viene inserito in una struct e in una lista concatenata. L'inserimento termina con l'invio del carattere EOF.
void loadRecords(Node **head) {
    bool end = false;
    while (!end) {
        Record r = readRecord();
        if (feof(stdin)) {
            end = true;
            break;
        }
        insertRecord(head, r);
    }
}

// Ordina gli elementi dell'array di Record in ordine ascendente rispetto al valore (saldo[i] - m) * (saldo[i] - m). Dove saldo[i] è il saldo dell'i-esimo elemento di X e m è il saldo medio.
void sort(Record* X, int n) {
    // Calcola il saldo medio - somma i saldi di tutte le struct Record e divide il risultato per la lunghezza dell'array
    double m = 0;
    for (int i = 0; i < n; i++) {
        m += X[i].balance;
    }

    m /= n;

    // selectionsort
    // iterazione per n - 1 volte (cioè si fanno n - 1 passate)
    for(int pass = 0; pass < n - 1; pass++) {
        // imposta come elemento minore quello selezionato nella passata corrente
        int idx_min = pass;
        // iterazione attraverso gli elementi successivi
        for(int i = pass + 1; i < n; i++) { 
            // se si verifica questa condizione uno degli elementi successivi diventa quello minimo
            if((X[i].balance - m)*(X[i].balance - m) < (X[idx_min].balance - m)*(X[idx_min].balance - m))
                idx_min = i;
        }
        
        // l'elemento della passata corrente viene scambiato con il minore tra i successivi elementi (se questo è minore del 1°)
        Record tmp = X[pass];
        X[pass] = X[idx_min];
        X[idx_min] = tmp;
    }
}

// Inserisce gli elementi di X in un file binario.
void saveToFile(Record X[], char filename[], int n) {
    FILE *cfPtr = NULL;

    if ((cfPtr = fopen(filename, "wb")) == NULL) {
        fprintf(stderr, "Impossibile aprire il file.");
        exit(-1);
    }

    for(int i = 0; i<n; i++){
        // frwite prende in input un puntatore al primo elemento dell'array da scrivere, la dimensione degli elementi da scrivere, il numero di elementi da scrivere e un puntatore al file su cui scrivere gli elementi. Ritorna il numero di elementi scritti.
        fwrite(&X[i], sizeof(Record), 1, cfPtr); //ERRORE-> ho usato fprintf
    }
    fclose(cfPtr);
}

// Crea un ordine random come array di interi casuali.
int* getRandomOrder(int n) {
    int* order = calloc(n, sizeof(int));

    for(int i=0; i<n; i++) order[i]=i;

    for(int i=0; i<n; i++) {
        int j = get_random()%n;
        int tmp = order[i];
        order[i] = order[j];
        order[j] = tmp;
    }

    return order;
}

// Legge in ordine casuale e stampa i primi 5 elementi del file.
void showFileContent(char filename[], int n) {
    FILE *cfPtr = NULL;

    int* order = getRandomOrder(n);

    if ((cfPtr = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "Impossibile aprire il file.");
        exit(-1);
    }

    for(int i=0; i<n; i++) {
        // Sposta il puntatore di lettura del file alla posizione indicata dall'ordine casuale scorrendo i vari Record del file.
        fseek(cfPtr, order[i] * sizeof(Record), SEEK_SET);
        Record r;
        size_t result = fread(&r, sizeof(Record), 1, cfPtr);
        // Se l'istruzione è riuscita a leggere un record (cioè fread ha come output 1) lo stampa
        if(result != 0)
            printRecord(r);
    }

    fclose(cfPtr);
}

int main(int argc, char *argv[]) {
    Parameters p = decodeParameters(argc, argv);

    printf("PUNTO A - valori dei parametri presi in input:\n");
    printf("filename = %s\n", p.filename);
    printf("n = %d\n", p.n);

    Node* L = NULL;

    loadRecords(&L);

    printf("\nPUNTO B - Contenuto di L:\n");
    printRecords(L);

    Record* X = getArray(L);

    sort(X, listlen(L));
    printf("\nPUNTO C - Contenuto di X dopo l'ordinamento:\n");
    printArray(X, listlen(L));

    saveToFile(X, p.filename, listlen(L));
    printf("\nPUNTO D - Contenuto del file binario in ordine casuale:\n");
    showFileContent(p.filename, p.n);
}