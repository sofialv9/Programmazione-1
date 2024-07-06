#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// A
// definisce la struct contenente i parametri
struct Parameters {
    float n;
    char inputFileName[100]; // funziona anche con l'allocazione dinamica
};

// Decodifica i parametri in input
struct Parameters decodeParameters(int argc, char *argv[]) {
    struct Parameters params;

    // controlla che i parametri in input siano 2
    if (argc != 3) {
        fprintf(stderr, "Uso: %s n input.dat\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // salva nella struct params n e controlla che sia un intero decimale
    char *endptr;
    params.n = strtol(argv[1], &endptr, 10);

    if (*endptr) {
        fprintf(stderr, "Errore: Il primo parametro deve essere un intero valido.\n");
        exit(EXIT_FAILURE);
    }
    
    // salva il nome del file di input nella struct params, controlla che la sua lunghezza sia compresa tra 5 e 20 (inclusi) e che abbia estensione .dat
    strcpy(params.inputFileName, argv[2]); //ERRORE-> avevo dimenticato di scriverlo e h avuto un segmentation fault

    if (params.n < 5 || params.n > 20) {
        fprintf(stderr, "Errore: n deve essere compreso tra 5 e 20.\n");
        exit(EXIT_FAILURE);
    }
    
    // altro modo per controllare l'estensione di un file
    const char *extension = strrchr(params.inputFileName, '.');
    if (extension == NULL || strcmp(extension, ".dat") != 0) {
        fprintf(stderr, "Errore: il file deve avere estensione .dat.\n");
        exit(EXIT_FAILURE);
    }

    return params;
}


// B

int *readInput(const char *fileName, int *size) {
    // apre il file di input
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Errore: Impossibile aprire il file %s\n", fileName);
        exit(EXIT_FAILURE);
    }
    
    //ERRORE -> NON RICORDAVO TUTTA QUESTA PARTE
    //Descrizione: prende in input il nome del file e l'indirizzo della variabile che indica la lunghezza dell'array. Imposta una lunghezza iniziale per l'array e lo alloca dinamicamente. Imposta una variabile per salvare il dato letto dal file e imposta l'indirizzo dereferenziato della lunghezza a 0. In un ciclo che controlla se fscanf legge ancora elementi (cioè se ritorna 1) si mette un if che controlla se la lunghezza della stringa ha raggiunto la lunghezza iniziale, se è così raddoppia la lunghezza iniziale e rialloca l'array dinamicamente. Come istruzione salva nell'elemento dell'array con indice la lunghezza reale con autoincremento il dato letto dal file. 

    // alloca dinamicamente un array di interi
    int capacity = 10; // dimensione iniziale dell'array da ottenere
    int *array = (int *) malloc(capacity * sizeof(int));
    if (array == NULL) {
        fclose(file);
        fprintf(stderr, "Errore di allocazione memoria.\n");
        exit(EXIT_FAILURE);
    }

    int num; // numero in input dal file
    *size = 0; // inizializzazione dimensione del file (= numero di elementi presenti nel file)
    // legge i dati dal file di input
    // fscanf ritorna il numero di elementi letti - il while legge dal file finché vi sono elementi da leggere
    while (fscanf(file, "%d", &num) == 1) {
        // se il numero di elementi del file raggiunge la lunghezza dell'array allocato precedentemente quest'ultima l'array viene riallocato con la lunghezza pari al doppio di quella precedente
        if (*size == capacity) {
            capacity *= 2;
            array = (int *)realloc(array, capacity * sizeof(int));
            if (array == NULL) {
                fclose(file);
                fprintf(stderr, "Errore di allocazione memoria.\n");
                exit(EXIT_FAILURE);
            }
        }
        // aggiorna la dimensione dell'array in base alla quantità di numeri letti dal file e inserisce l'intero estratto dalla pila nell'array
        array[(*size)++] = num;
    }
    
    // chiude il file di input e ritorna l'array A
    fclose(file);
    return array;
}

// stampa l'array
void printArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d\n", array[i]);
    }
}

// C

// crea la struct che simboleggia un nodo della pila
struct stackNode {
    float data;
    struct stackNode *next;
};
typedef struct stackNode StackNode;

// inserisce un nuovo nodo nella pila e ritorna true se ha successo
bool push(StackNode **top, float data) {
    StackNode *newNode = malloc(sizeof(StackNode));

    if(newNode==NULL)
        return false;

    newNode->data = data;
    newNode->next = *top; // la vecchia cima è il nodo successivo a quello appena inserito

    *top = newNode; // il nodo inserito è la nuova cima
    return true;
}

// estrae un elemento dalla pila
float pop(StackNode **top) {
    StackNode *tmp = *top;
    float data = tmp->data;
    *top = tmp->next;
    free(tmp); 
    return data;
}

bool isEmpty(StackNode *top) {
    return top==NULL;
}

StackNode* createStack(int *array, int size, int n) {
    StackNode *top = NULL;

    // scorre l'array A
    for (int i = 0; i < size; i++) {
        // se l'elemento dell'array è un multiplo di n viene inserito nello stack
        if (array[i] % n == 0) {
            push(&top, array[i]);
            // altrimenti, se la pila non è vuota, si estrae il valore in cima alla pila e si inserisce nella pila la media tra il valore estratto e il valore dell'elemento dell'array
        } else {
            if (!isEmpty(top)) {
                float x = pop(&top); // valore estratto
                float avg = (x + array[i]) / 2; // media
                push(&top, avg);
            }
        }
    }

    return top;
}

// stampa la pila
void printStack(StackNode *top) {
    StackNode *aux = top;
    while (aux) {
        float data = aux->data;
        printf("%0.2f\n", data);
        aux = aux->next;
    }
}


// D

// Trova il valore massimo, quello minimo e quello medio tra quelli contenuti nella pila
void findMinMaxMean(struct stackNode *top, float *min, float *max, float *mean) {
    //ERRORE-> avevo dimenticato questa struttura di controllo
    if (isEmpty(top)) {
        fprintf(stderr, "Error: Stack is empty.\n");
        return;
    }
    
    // inizializza minimo, massimo al valore contenuto nel nodo in cima allo stack
    *min = top->data;
    *max = *min;
    float sum = *min; // somma dei valori nello stack
    int count = 1; // contatore elementi dello stack

    StackNode *aux = top;
    aux = aux->next; // passa al nodo successivo alla cima

    while (aux) {
        int value = aux->data;
        sum += value; // aggiorna somma dei valori dello stack
        count++; // aumenta contatore elementi dello stack
        
        // se necessario aggiorna massimo e minimo
        if (value < *min) {
            *min = value;
        } else if (value > *max) {
            *max = value;
        }
        aux = aux->next; // passa al nodo successivo
    }
    
    // calcola la media
    *mean = sum / count;
}


////////////////////   FUNZIONE MAIN   /////////////////////////

int main(int argc, char *argv[]) {
// Prende in input da riga di comando un parametro intero n (compreso tra 5 e 20 inclusi) e un parametro stringa che indica il nome del file di input
    struct Parameters params = decodeParameters(argc, argv);

    printf("Punto A - Parametri inseriti: n=%d, inputFileName=%s\n", params.n, params.inputFileName);

// Legge gli interi contenuti nel file di input 2 volte: la prima per creare un array A della dimensione corretta e la seconda per inserire gli interi in A. Infine stampa l'array A.
    int size; // dimensione dell'array
    int *array = readInput(params.inputFileName, &size);

    printf("\nPunto B - Contenuto di A:\n");
    printArray(array, size);

// Inizializza una pila di float P, scorre gli elementi di S e controlla che ogni elemento sia multiplo del parametro n. Se è così S[i] viene inserito in cima alla pila, altrimenti si estrae l'elemento attualmente in cima alla pila (x) e si inserisce nella pila la media aritmetica tra x e A[i]. Infine stampa la pila S.
    StackNode *S = createStack(array, size, params.n);

    printf("\nPunto C - Contenuto di S:\n");
    printStack(S);

// Stampa il valore massimo, il valore minimo e il valore medio contenuti nella pila.
    float min, max, mean; // definisce le variabili nel main

    findMinMaxMean(S, &min, &max, &mean); // passa gli indirizzi delle variabili alla funzione (passaggio per riferimento)

    printf("\nPunto D:\n");
    printf("Valore minimo: %.2f\n", min);
    printf("Valore massimo: %.2f\n", max);
    printf("Valore medio: %.2f\n", mean);

    free(array); // libera lo spazio occupato dall'array allocato dinamicamente

    return 0;
}
