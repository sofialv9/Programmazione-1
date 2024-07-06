#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // INT_MAX e INT_MIN

// definisce il valore massimo e minimo che n e m possono assumere in modo definitivo
#define MAX_N 7
#define MIN_N 3
#define MAX_M 7
#define MIN_M 3

// parametri di input
struct parametri {
    int n;
    int m;
    char* filename; // file di input con estensione .txt
};

// Prende in input il numero argc e il vettore argv ricevuti in input dalla funzione main, controlla la presenza e i requisiti degli argomenti e li inserisce in una struct da restituire alla funzione main. Deve gestire gli errori relativi a input non corretti.
struct parametri decodeParameters(int argc, char *argv[]) {
    struct parametri p;

    // controlla che gli argomenti in input siano 4
    if (argc != 4) {
        fprintf(stderr, "Usage: %s n m file.txt\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // converte i primi due parametri in interi e li memorizza nei membri n e m della struct p
    p.n = atoi(argv[1]);
    p.m = atoi(argv[2]);

    // controlla che i numeri n e m siano interi decimali
    char *end;
    p.n = (int) strtol(argv[1], &end, 10);

    // se end non è un puntatore a NULL dà errore
    if(*end) { //ERRORE: dimenticato asterisco
        fprintf(stderr, "Errore: n non è un intero valido.\n");
        exit(-1);
    }

    p.m = (int) strtol(argv[2], &end, 10);

    if(*end) {
        fprintf(stderr, "Errore: m non è un intero valido.\n");
        exit(-1);
    }

    // salva il 3° parametro nel membro filename della struct p
    p.filename = argv[3];

// controlla che n e m siano interi compresi tra 3 e 7 e che il nome del file di input abbia come estensione .txt
    if (p.n < MIN_N || p.n > MAX_N || p.m < MIN_M || p.m > MAX_M) {
        fprintf(stderr, "Error: n and m must be integers between %d and %d.\n", MIN_N, MAX_N);
        exit(EXIT_FAILURE);
    }

    if (strcmp(p.filename + strlen(p.filename) - 4, ".txt") != 0) {
        fprintf(stderr, "Error: file must have .txt extension.\n");
        exit(EXIT_FAILURE);
    }

    return p;
}

// stampa i parametri
void printParameters(struct parametri p) {
    printf("======Stampa Parametri======\n");
    printf("n = %d\n", p.n);
    printf("m = %d\n", p.m);
    printf("filename = %s\n", p.filename);
    puts("\n");
}

// legge il contenuto del file di testo e lo inserisce in una matrice X di double di dimensioni n * m
double **readFile(char *filename, int n, int m) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: cannot open file %s.\n", filename);
        exit(EXIT_FAILURE);
    }
    
    // allocazione dinamica di una matrice di double di dimensioni n * m
    double **X = (double**) malloc(n * sizeof(double *)); // ERRORE: scordato di scrivere "n *" prima di sizeof
    for (int i = 0; i < n; i++) {
        // crea le righe di numero i come array di lunghezza m
        X[i] = (double*) malloc(m * sizeof(double));
        // iterazione attraverso le colonne
        for (int j = 0; j < m; j++) {
            fscanf(fp, "%lf,", &X[i][j]);
        }
    }
    fclose(fp);

    return X;
}

// stampa la matrice X
void printMatrix(double **X, int n, int m, const char *name) {
    printf("======Stampa %s======\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%5.2f ", X[i][j]);
        }
        printf("\n");
    }
    puts("\n");
}

// definisce un array Y di interi 
int* getArray(double **X, int n, int m) {
    int *Y = (int*) calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) { // righe
        double q = 0;
        // imposta il massimo e il minimo della riga ai valori limite degli interi
        double max = INT_MIN; //ERRORE: messo int al posto di double
        double min = INT_MAX; //ERRORE: messo int al posto di double
        for (int j = 0; j < m; j++) {
            q += X[i][j];
            if(X[i][j] < min)
                min = X[i][j];
            if(X[i][j] > max)
                max = X[i][j];
        }
        q = q / m; // valore medio della riga (somma degli elementi di una riga diviso il numero di colonne)

        float a = q - (max-min)*0.3;
        float b = q + (max-min)*0.3;
        Y[i] = 0;
        // in Y[i] si inserisce il numero di elementi della riga i-esima di X che hanno un valore compreso tra b e a esclusi gli estremi
        for (int j = 0; j < m; j++) {
            if (X[i][j] > a && X[i][j] < b) { //ERRORE: messo <= e >=; messo || al posto di &&
                Y[i] += 1;
            }
        }
    }
    return Y;
}

// stampa l'array Y
void printArray(int *array, int n, const char *name) {
    printf("======Stampa %s======\n", name);
    for(int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    puts("\n");
}

// ordina l'array Y con l'algoritmo insertion sort
void insertionSort(int *Y, int n) {
    // iterazione per n - 1 volte - ad ogni iterazione si inserisce un elemento nella posizione corretta tra gli elementi ordinati fino a quel punto
    for (int i = 1; i < n; i++) {
        int key = Y[i]; // inizia con key = Y[1]
        int j = i - 1; // Y[0]
        
        while (j >= 0 && Y[j] > key) {
            Y[j + 1] = Y[j];
            j--; // dimenticato questo
        }
        Y[j + 1] = key;
    }
}

// Crea un nuovo array Z a partire da Y tale che Z[i] = sommatoria da 0 a i di Y[i]
int *getCumulative(int *Y, int n) {
    int *Z = (int*) malloc(n * sizeof(int));
    Z[0] = Y[0];
    for (int i = 1; i < n; i++) {
        Z[i] = Z[i - 1] + Y[i];
    }

    return Z;
}

int main(int argc, char *argv[]) {
    // decodifica i parametri ottenuti in input e li stampa
    struct parametri p = decodeParameters(argc, argv);
    printParameters(p);
    
    // Salva il contenuto del file di input in una matrice X  (n x m) e stampa la matrice
    double **X = readFile(p.filename, p.n, p.m);
    printMatrix(X, p.n, p.m, "X");

    // crea l'array Y e lo stampa
    int *Y = getArray(X, p.n, p.m);
    printArray(Y, p.n, "Y");
    
    // ordina Y e lo stampa d nuovo
    insertionSort(Y, p.n);
    printArray(Y, p.n, "Y ordinato");

    // crea l'array Z e lo stampa
    int *Z = getCumulative(Y, p.n);
    printArray(Z, p.n, "Z");
}
