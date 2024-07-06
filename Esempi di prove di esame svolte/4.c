#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

typedef struct parameters{
    int n;
    float x;
    float y;
} Parameters;

Parameters readInput(int argc, char* argv[]){
    Parameters p;

    if(argc != 4){
        fprintf(stderr, "Errore: il numero di argomenti deve essere pari a 3.\nUso: %s n, x, y.\n", argv[0]);
        exit(-1);
    }

    char** end = malloc(sizeof(char*));
    p.n = (int) strtol(argv[1], end, 10);
    if(!end){
        fprintf(stderr, "Errore: n deve essere un intero.\n");
        exit(-1);
    }
    if(p.n < 10 || p.n > 20){
        fprintf(stderr, "Errore: n deve essere compreso tra 10 e 20 (estremi inclusi).\n");
        exit(-1);
    }

    p.x = strtof(argv[2], end);
    if(!end){
        fprintf(stderr, "Errore: x deve essere un float.\n");
        exit(-1);
    }
    if(p.x < 5 || p.x > 30){
        fprintf(stderr, "Errore: x deve essere compreso tra 5.0 e 30.0.\n");
        exit(-1);
    }

    p.y = strtof(argv[3], end);
    if(!end){
        fprintf(stderr, "Errore: y deve essere un float.\n");
        exit(-1);
    }
    if(p.y < 5 || p.y > 30){
        fprintf(stderr, "Errore: y deve essere compreso tra 5.0 e 30.0.\n");
        exit(-1);
    }

    return p;
}

// Genera un double random tra x e y
double genDouble(float x, float y){
    return ((double) get_random() / UINT_MAX) * (y - x) + x;
}

// Genera una matrice di double con double random
double** genMatrix(int n, float x, float y){
    double** W = calloc(n, sizeof(double*));
    for(int i = 0; i < n; i++){
        W[i] = calloc(n, sizeof(double));
        for(int j = 0; j < n; j++){
            W[i][j] = genDouble(x, y);
        }
    }
    return W;
}

// Calcola il minimo della diagonale principale, il massimo della diagonale secondaria e il numero di elementi della matrice compresi tra questi 2 valori
int computeMinMax(double** W, int n, double* minp, double* maxd){
    // inizializza il minimo della diagonale principale e il massimo della diagonale secondaria al 1° elemento delle rispettive diagonali
    *minp = W[0][0];
    *maxd = W[n - 1][0];

    for(int i = 0; i < n; i++){
        if(W[i][i] < *minp){
            *minp = W[i][i];
        }
        if(W[i][n - 1 - i] > *maxd){
            *maxd = W[i][n - 1 - i];
        }
    }

    int count = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(W[i][j] <= *maxd && W[i][j] >= *minp){
                count++;
            }
        }
    }
    return count;
}

// Crea una array di double che contiene tutti gli elementi della matrice W nell'intervallo [minp, maxd]
double* createArray(double** W, int n, int count, double minp, double maxd){
    double* out = calloc(count, sizeof(double));

    int k = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(W[i][j] <= maxd && W[i][j] >= minp){
                out[k++] = W[i][j];
            }
        }
    }
    return out;
}

// Ordina l'array con il selection sort
void sort(double* array, int n){
    // selection sort
    for(int i = 0; i < n - 1; i++){
        int smallest = i;
        for(int j = i + 1; j < n; j++){
            if(array[j] < array[smallest]){
                smallest = j;
            }
        }

        double tmp = array[i];
        array[i] = array[smallest];
        array[smallest] = tmp;
    }
}

// Stampa l'array di double e la media aritmetica dei suoi elementi
void printArray(double* array, int n){
    double media = 0;
    for(int i = 0; i < n; i++){
        printf("%.f\n", array[i]);
        media += array[i];
    }
    media /= n;
    
    printf("Media: %.f\n", media);
    
}

int main(int argc, char* argv[]){
    Parameters p = readInput(argc, argv);

    double** W = genMatrix(p.n, p.x, p.y);

    double minp, maxd;
    int count = computeMinMax(W, p.n, &minp, &maxd);

    double* A = createArray(W, p.n, count, minp, maxd);

    sort(A, count);
    printArray(A, count);
}

