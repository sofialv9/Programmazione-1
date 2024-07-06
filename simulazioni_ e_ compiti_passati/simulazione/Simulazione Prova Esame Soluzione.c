#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

// B - per creare una lista di struct crea una struct Riga contenente un array di 100 caratteri e un intero count e una struct Node contenente una struct Riga e un puntatore a Node
// Struttura che simboleggia una riga del file di input
typedef struct {
    char word[100]; // prima parola
    int count; // occorrenze della prima parola nella riga
} Riga;

// Nodo della lista di struct
struct node {
    Riga data;
    struct node *next;
};
typedef struct node Node;

// inserisce un nodo in testa alla lista
bool insertHead(Node **head, Riga r) {

    Node *newNode = malloc(sizeof(Node));

    if(newNode==NULL)
        return false;

    newNode->data = r;
    newNode->next = *head;
    *head = newNode;

    return true;
}

// inserisce un nodo in coda alla lista
bool insertTail(Node **head, Riga r) {
    // se la lista è vuota inserisce il nodo all'inizio
    if(*head == NULL) {
        return insertHead(head, r);
    }
    
    // va avanti fino alla fine della lista
    Node *ptr = *head;
    while(ptr->next) {
        ptr = ptr->next;
    }

    // aggiunge il nuovo nodo alla fine della lista
    Node *newNode = malloc(sizeof(Node));
    if(newNode == NULL)
        return false;

    newNode->data = r;
    newNode->next = NULL;
    ptr->next = newNode;

    return true;
}

// Crea una lista a partire da un file. Apre il file in lettura e imposta una variabile stringa di 1000 caratteri e un bool a false. Mentre il bool è false legge una stringa dal file e la salva nella variabile. Se la stringa non è NULL separa la prima parola e imposta count a 0. Continua a dividere le parole della riga e controlla se sono uguali alla prima parola, se è così aumenta count. Inizializza una struct Riga e salva la prima parola e count. Inserisce la struct nella lista. Se la string è NULL imposta il bool a true. Ritorna un riferimento alla testa della lista.
Node* readFile(char *name) {
    Node **head = malloc(sizeof(Node*));
    *head = NULL; // crea una testa (inizialmente vuota)
    
    FILE *f = fopen(name, "r");
    char s[1000]; // riga del file di testo
    bool done = false;
    
    // OPPURE fare un do while che controlli che out sia diverso da NULL
    // fino alla fine del file
    while(!done) {
        // legge una riga dal file di testo
        char *out = fgets(s, 1000, f);

        if(out != NULL) {
            // separa la prima parola
            char *tok = strtok(s, " \n");
            char *firstTok = tok;
            int count = 0;
            
            // se la parola successiva è uguale alla prima aumenta il contatore (viene sempre aumentato la prima volta)
            do {
                if(strcmp(firstTok, tok) == 0) {
                    count++;
                }
            } while((tok = strtok(NULL, " \n")));

            // crea una struct riferita a quella riga e salva la prima parola della riga e il suo numero di occorrenze
            Riga r;
            r.count = count;
            strcpy(r.word, firstTok);
            // aggiunge la struct alla fine della lista (si può aggiungere anche in testa)
            insertTail(head, r);

        } else {
            done = true; // è stata raggiunta la fine del file di testo
        }
    }
    return *head;
}

// Stampa le parole presenti nella lista con il relativo numero di occorrenze (D)
void printList(Node *head) {
    Node *ptr = head;

    while(ptr) {
        // ottiene il puntatore alla riga come indirizzo del membro data del nodo puntato da ptr. 
        Riga *r = &ptr->data;
        printf("%s %d\n", r->word, r->count);
        ptr = ptr->next;
    }
}

// Elimina dalla lista le parole con un numero di occorrenze inferiori a n (C)

// Cancella il nodo in testa alla lista
bool deleteHead(Node **head) {
    if(*head) {
        Node *tmp = *head;
        *head = (*head)->next;
        free(tmp);
        return true;
    } else {
        return false;
    }
}

// Elimina i nodi con count minore di n
void filterList(Node **head, int n) {
    // se la lista è vuota
    if(*head == NULL) {
        return;
    }
    
    // imposta un puntatore al nodo corrente e a quello precedente
    Node *ptr = *head;
    Node *prevPtr = NULL;

    while(ptr) {
        if(ptr->data.count < n) {
            if(prevPtr == NULL) {
                // cancella il nodo in testa alla lista
                deleteHead(head);
                // imposta il puntatore corrente alla nuova testa
                ptr = *head;
                continue;

            } else {
                // cancella il nodo puntato da ptr
                Node *tmp = ptr;
                // imposta il successivo del precedente al successivo del corrente
                prevPtr->next = ptr->next;
                free(tmp);
                // imposta il nodo corrente a quello precedente
                ptr = prevPtr;
            }
        }
        // va avanti nella lista
        prevPtr = ptr;
        ptr = ptr->next;
    }
}

// Legge un intero da tastiera controllando che l'argomento in input sia uno solo e che il numero sia intero positivo. (A)
int readN(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Errore, bisogna passare un parametro intero da riga di comando.\n");
        exit(-1);
    }

    char **end = malloc(sizeof(char*));
    int n = (int) strtol(argv[1], end, 0);

    if(!end || n < 0) {
        fprintf(stderr, "Errore, il parametro passato deve essere intero positivo.\n");
        exit(-1);
    }

    return n;
}


int main(int argc, char *argv[]) {
// A - prende in input da tastiera un intero n
    int n = readN(argc, argv);

// B - legge un file di testo contenente sequenze di parole separate da spazi. Le parole hanno lunghezza massima di 100 caratteri, le righe di 1000 caratteri. Crea una lista di struct a partire dal contenuto del file. Ogni struct deve rappresentare una riga del file e deve contenere 2 campi: la stringa "word" che contiene la prima parola nella riga e l'intero "count" che contiene il numero di occorrenze di tale parola nella riga.
    Node **head = malloc(sizeof(Node*));
    *head = readFile("input.txt");

// C - elimina dalla lista le parole con un numero di occorrenze minore di n
    filterList(head, n);

// D - stampa a schermo le parole nella lista con il relativo numero di occorrenze
    printList(*head);
}