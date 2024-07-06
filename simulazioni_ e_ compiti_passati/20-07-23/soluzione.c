#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Funzione per generare numeri casuali
unsigned int get_random() {
    static unsigned int m_w = 424242;
    static unsigned int m_z = 242424;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

// A
struct parameters {
    int n;
    int m;
};
typedef struct parameters Parameters;


Parameters decodeParameters(int argc, char *argv[]) {
    Parameters p;

    // controlla che i parametri inseriti siano 2
    if(argc != 3) {
        fprintf(stderr, "Errore, il numero di parametri deve essere uguale a 2\n");
        exit(-1);
    }

    // controlla che n e m siano interi e che siano compresi tra 3 e 7 (inclusi)
    char *end;
    p.n = (int) strtol(argv[1], &end, 10);

    if(*end) {
        fprintf(stderr, "Errore: n non è un intero valido.\n");
        exit(-1);
    }

    p.m = (int) strtol(argv[2], &end, 10);

    if(*end) {
        fprintf(stderr, "Errore: m non è un intero valido.\n");
        exit(-1);
    }

    if(p.n < 3 || p.n > 7 || p.m < 3 || p.m > 7) {
        fprintf(stderr, "Errore: n e m devono essere compresi tra 3 e 7.\n");
        exit(-1);
    }

    return p;
}

// B

// chiede all'utente di inserire un numero e controlla che sia compreso tra 10 e 100 (inclusi)
int getInput() {
    int x;
    printf("Inserisci un numero compreso tra 10 e 100:\n");
    scanf("%d", &x);

    if(x < 10 || x > 100)
        fprintf(stderr, "Errore, numero non compreso tra 10 e 100\n");

    return x;
}

// Crea una matrice di puntatori ad interi di dimensioni n * m.
int*** getRandomMatrix(int n, int m, int h) {
    int*** A = calloc(n, sizeof(int**));
    // inizializza le righe
    for(int i = 0; i < n; i++) {
        A[i] = calloc(m, sizeof(int*));
        // inizializza le colonne
        for (int j = 0; j < m; j++) {
            A[i][j] = malloc(sizeof(int)); //ERRORE-> non ho allocato la memoria

            // ogni elemento è un puntatore ad un numero intero casuale tra 0 e h.
            *A[i][j] = get_random() % (h + 1);
        }
    }
    return A;
}

// Stampa la matrice di puntatori A
int*** printMatrix(int ***A, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            // se il puntatore non è NULL si stampa l'elemento a cui punta
            if(A[i][j]) //ERRORE-> avevo messo l'asterisco e dava segmentation fault
                printf("%5d",*A[i][j]); 
            // se il puntatore è NULL si stampa un asterisco
            else
                printf("    *");
        }
        printf("\n");
    }
}

// C
// Rimuove il valore massimo in ciascuna colonna
//ERRORE -> dimenticato tutto
//Descrizione: imposta un valore iniziale al massimo, imposta la variabile di controllo a false e imposta il valore della riga in cui vi è il massimo con -1. Fa un ciclo lungo la colonna: se l'elemento non è un puntatore NULL controlla che la variabile di controllo sia false o che il valore puntato sia maggiore del massimo, se si verifica una delle condizioni aggiorna il massimo, mette la variabile di controllo a true e imposta il valore della riga in cui è presente il massimo con quello corrente. Infine controlla che il valore della riga sia maggiore o uguale a zero, libera la memoria puntata dall'elemento della matrice e lo imposta a NULL.

void removeMax(int ***A, int n, int col){
    int max;
    bool init = false;
    int idxmax = -1; // riga in cui è presente il massimo
    // ciclo lungo la colonna
    for(int i = 0; i < n; i++) {
        // se A non è un puntatore NULL
        if(A[i][col]) {
            // se init non è true oppure il massimo è minore dell'elemento puntato dall'elemento corrente della matrice
            if(!init || max < *A[i][col]) { //ERRORE-> messo && al posto di ||
                // aggiorna il valore massimo
                max = *A[i][col];
                // salva la riga in cui è presente il valore massimo
                idxmax = i;
                init = true;
            }
        }
    }
    // libera la memoria occupata dall'intero puntato da A[i][j] e pone a NULL l'elemento A[i][j]
    if(idxmax >= 0) {
        free(A[idxmax][col]);
        A[idxmax][col] = NULL;
    }
}

// Cerca il massimo per 3 volte in ciascuna colonna e lo rimuove
void modifyMatrix(int*** A, int n, int m) {
    // ciclo attraverso le colonne
    for(int col = 0; col < m; col++) { 
        // Ripete 3 volte per ogni colonna
        for(int rep = 0; rep < 3; rep++)
            removeMax(A, n, col);
    }
}


// D
// Cerca la riga con il minor numero di valori NULL -> imposta il minimo al numero massimo di elementi (cioè il numero di colonne), imposta la riga cercata a -1 e fa un ciclo lungo le righe. Inizializza il contatore a 0, fa un ciclo lungo le colonne e aumenta il contatore quando nezessario. Alla fine del ciclo controlla se il contatore è minore del minimo e in caso aggiorna il minimo e il valore della riga cercata. Alla fine ritorna il valore della riga.

int rowMinNull(int*** A, int n, int m) {
    int min = m; // inizializza il minimo di valori NULL al massimo valore che questo può assumere (il numero di colonne, cioè degli elementi di una riga)
    int idxmin = -1; // riga con il minor numero di valori null
    // ciclo lungo le righe
    for(int i = 0; i < n; i++) {
        int numnull = 0; // inizializza il contatore di valori NULL
        // ciclo lungo le colonne
        for(int j = 0; j < m; j++){
            // se l'elemento è un puntatore NULL aumenta il contatore
            if(!A[i][j])
                numnull++;
        }
        // se il valore appena trovato è minore del precedente minimo aggiorna il valore minimo e la riga in ci questo è presente
        if(numnull < min) {
            min = numnull;
            idxmin = i;
        }
    }
    // ritorna la riga in cui è presente il minimo di valori NULL
    return idxmin;
}

// Stampa la riga con il minimo di valori NULL
void printRow(int*** A, int row, int m) {
    for(int i = 0; i < m; i++) {
        if(A[row][i])
            printf("%5d",*A[row][i]);
        else
            printf("    *");
    }
}

int main(int argc, char* argv[]) {
    // A - prende in input da riga di comando 2 parametri interi n e m compresi tra 3 e 7 e li stampa a schermo.
    Parameters p = decodeParameters(argc, argv);
    printf("Punto A - Parametri inseriti: n=%d, m=%d\n", p.n, p.m);
    
    // B - chiede all'utente di inserire un valore intero compreso tra 10 e 100 e crea una matrice A n*m di puntatori ad interi generati casualmente nell'intervallo [0, h] mediante la funzione get_random. Infine stampa la matrice A.
    int h = getInput();

    printf("\nPunto B - Contenuto di A:\n");
    int*** A = getRandomMatrix(p.n, p.m, h);
    printMatrix(A, p.n, p.m);

    // C - elimina in ciascuna colonna di A i 3 valori più grandi della colonna. Stampa la matrice ponendo degli asterischi in corrispondenza dei puntatori NULL.
    printf("\nPunto C - Contenuto di A dopo la modifica:\n");

    modifyMatrix(A, p.n, p.m);
    printMatrix(A, p.n, p.m);

    // D - Stampa i valori della riga con il numero minore di valori NULL. Qualora più righe avessero lo stesso numero di valori NULL è sufficiente stampare una qualsiasi i queste.
    printf("\nPunto D - Riga con minor numero di NULL:\n");
    int row = rowMinNull(A, p.n, p.m);
    printRow(A, row, p.m);
    printf("\n");
}
