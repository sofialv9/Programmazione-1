#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

/*Si scriva un programma C che:
    A. Prenda in input da riga di comando un parametro stringa “input” che contenga il nome di un file con estensione “txt” (ad esempio “file_di_input.txt”), e un parametro stringa “output” che contenga il nome di un file con estensione “txt” (ad esempio “file_di_output.txt”). Il programma controlla che l’utente abbia specificato il numero corretto di parametri e che i nomi dei file abbiano effettivamente estensione “txt”. Se i parametri passati non rispettano i requisiti richiesti, il programma stampa un messaggio di errore sullo standard error e termina la sua esecuzione con un appropriato codice di terminazione.*/

// main: prende in input da riga di comando 2 parametri, cioè 2 stringhe
int main(int argc, char* argv[]) {
    // Parametri in input (nomi dei file di input e output)
    Parameters p = readInput(argv, argc);

    // salva il contenuto del file di input in una lista concatenata
    Node **A = readFile(p.input);

    // numero di elementi letti dal file
    int n = len(A);
    
    // determina il cliente con il più alto valore di x con m saldo massimo contenuto nella lista concatenata
    for(int i = 0; i < n/2; i++) {
        float m = getMax(*A);
        removeAccount(A, m);
    }
        
    writeFile(A, p.output);
}

// definisce la struttura in cui memorizzare i parametri in input
struct parameters {
    char input[255];
    char output[255];
};
typedef struct parameters Parameters;

// controlla che i 2 parametri in input abbiano estensione .txt
bool checkExt(char* s) {
    return (strlen(s)>=4) && (s[strlen(s)-1]=='t') && (s[strlen(s)-2]=='x') && (s[strlen(s)-3]=='t') && (s[strlen(s)-4]=='.');
}

// Legge i parametri in input controllando che siano 2 e che abbiano estensione .txt
Parameters readInput(char *argv[], int argc) {
    if(argc!=3) {
        fprintf(stderr, "Errore: il numero di parametri deve essere pari a 3.\n");
        fprintf(stderr, "Uso corretto: %s input.txt output.txt\n", argv[0]);
        exit(-1); // codice di terminazione
    }

    if(!checkExt(argv[1]) || !checkExt(argv[2])) {
        fprintf(stderr, "Errore: i nomi dei file devono avere estensione \".txt\".\n");
        exit(-1);
    }

// crea una struttura di tipo parametri e salva il nome del file di input e quello del file di output
    Parameters p;

    strcpy(p.input, argv[1]);
    strcpy(p.output, argv[2]);

    return p;
}

/*B. Legga il contenuto del file e salvi i dati relativi in una lista concatenata A. Il file di testo contiene diverse righe relative a clienti di una banca nel seguente formato: nome cognome numero_conto anno_apertura saldo. Ciascun dato contenuto nella lista concatenata deve essere una struct. Si assuma che nome e cognome siano delle stringhe di lunghezza massima 255 caratteri, numero_conto e anno_apertura (anno di apertura del conto) siano due interi e saldo un numero in virgola mobile a singola precisione. I dati vanno inseriti nella lista in ordine di anno di apertura del conto.*/

// dato della lista concatenata
struct data {
    char nome[255];
    char cognome[255];
    int numero_conto;
    int anno_apertura;
    float saldo;
};
typedef struct data Data;

// nodo della lista concatenata
struct node {
    Data data;
    struct node *next;
};
typedef struct node Node;

// controlla se la lista è vuota
bool isEmpty(Node *head) {
    return head==NULL;
}

// se la lista è vuota o l'anno di apertura è minore di quello del dato attualmente all'inizio della lista
void insertHead(Node **head, Data d) {
    Node *new = malloc(sizeof(Node));
    new->data = d;
    new->next = *head;
    *head = new;
}

// inserisce un nodo dopo un altro nodo dato come parametro
void insertAfter(Node *node, Data d) {
    Node *new = malloc(sizeof(Node));
    new->data = d;
    new->next = node->next;
    node->next = new;
}

// 
void insertOrdered(Node **head, Data d) {
    if(isEmpty(*head) || d.anno_apertura < (*head)->data.anno_apertura) {
        insertHead(head, d);
        return;
    }

    Node *tmp = *head;
    Node *prev = NULL;

    // cerca la posizione corretta in cui inserire il nodo (la lista è in ordine rispetto all'anno di apertura del conto)
    while(tmp->next && tmp->data.anno_apertura < d.anno_apertura) {
        prev = tmp;
        tmp = tmp->next;
    }

    // se prev è diverso da NULL inserisce il nodo dopo prev, altrimenti lo inserisce dopo la testa della lista
    if(prev)
        insertAfter(prev, d);
    else
        insertAfter(tmp, d);
}

// legge il contenuto del file di input, lo salva nella lista concatenata A e restituisce un riferimento alla testa della lista concatenata
Node **readFile(char* fname) {
    Node** head = malloc(sizeof(Node*));

    // apre il file di input
    FILE *f = fopen(fname, "r");

    // dà errore se non riesce ad aprire il file
    if(!f) {
        fprintf(stderr, "Errore: impossibile aprire il file %s.\n", fname);
        exit(-1);
    }

    while(!feof(f)) {
        Data d;
        fscanf(f, "%s %s %d %d %f", d.nome, d.cognome, &d.numero_conto, &d.anno_apertura, &d.saldo);
        if(!feof(f)){
            insertOrdered(head, d);
        }
    }
    fclose(f);

    return head;
}

/* D. L’operazione specificata al punto C deve essere eseguita ℎ volte, con ℎ = (n/2) dove 𝑛 è il numero di elementi letti dal file e n/2 rappresenta la parte intera di n/2 */
int len(Node **head) {
    Node *aux = *head;

    // contatore degli elementi della lista
    int i = 0;
    // finché non raggiunge la fine della lista
    while(aux) {
        // aumenta il contatore e passa all'elemento successivo
        i++;
        aux = aux->next;
    }
    return i;
}

/*C. Determini il cliente che presenta il più alto valore di 𝑥, con 𝑥 calcolato come segue:
𝑥 = min((2023 − 𝑎𝑛𝑛𝑜_𝑎𝑝𝑒𝑟𝑡𝑢𝑟𝑎) / 5), 1) * (𝑠𝑎𝑙𝑑𝑜 / 𝑚) dove 𝑚 è il saldo massimo contenuto nella lista concatenata. Una volta trovato il cliente, il programma lo rimuove dalla lista.*/

float getMax(Node *head) {
    // imposta come massimo il saldo contenuto nel nodo in testa
    float max = head->data.saldo;
    Node *aux = head;
    
    // finché non raggiunge la fine della lista
    while(aux) {
        // se aux non è NULL e il valore del saldo contenuto nel nodo puntato da aux è maggiore del massimo corrente aggiorna il max
        if(aux && aux->data.saldo > max) {
            max = aux->data.saldo;
        }
        aux = aux->next;
    }

    // ritorna il saldo massimo contenuto nella lista concatenata
    return max;
}

// calcola x
float computeX(Data d, float m) {
    float x = (float)(2023 - d.anno_apertura)/5;
    // calcola il minimo tra x e 1, quindi ritorna 1 se x > 1
    if (x > 1)
        x = 1;
    return x * d.saldo / m;
}

void delete(Node **head, Data d) {
    // se coincide con la testa questa viene eliminata
    if((*head)->data.numero_conto == d.numero_conto) {
        Node *tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }

    Node *tmp = *head;
    Node *prev = NULL;
    
    // se il numero di conto non coincide con quello della testa si va avanti lungo la lista
    while(tmp->next && tmp->data.numero_conto != d.numero_conto) {
        prev = tmp;
        tmp = tmp->next;
    }

    if(tmp && tmp->data.numero_conto == d.numero_conto) {
        prev->next = tmp->next;
        free(tmp);
    }
}

// elimina l'account nella lista concatenata che contiene il saldo massimo
void removeAccount(Node **A, float m) {
    Node *aux = *A;
    
    // imposta il più alto valore di x a quello calcolato facendo riferimento al primo nodo della lista
    float max = computeX(aux->data, m);

    Node *tmp = aux;

// d conserva la struct data del nodo da eliminare
    Data d;

// fino alla fine della lista aggiorna il valore massimo di x calcolando il valore di x per ogni nodo
    while(aux) {
        if(computeX(aux->data, m) > max) {
            max = computeX(aux->data, m);
            d = aux->data;
        }
        aux = aux->next;
    }

// elimina il nodo corrispondente al valore massimo di x
    delete(A, d);    
}

/*E. Salvi il contenuto della lista A sul file il cui nome è indicato dal parametro “output”. Il file di output dovrà seguire lo stesso formato del file di input.*/

void writeFile(Node **head, char* fname) {

    FILE *f = fopen(fname, "w");
    if(!f) {
        fprintf(stderr, "Errore: impossibile aprire il file %s.\n", fname);
    }

    Node *aux = *head;

    // fino alla fine della lista stampa sul file di output i dati di ogni nodo della lista
    while(aux) {
        Data d = aux->data;
        fprintf(f, "%s %s %d %d %.2f\n", d.nome, d.cognome, d.numero_conto, d.anno_apertura, d.saldo);
        aux = aux->next;
    }

    fclose(f);
}

