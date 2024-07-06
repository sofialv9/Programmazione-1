#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

typedef struct parameters{
    int N;
    float x;
    float y;
} Parameters;

Parameters readInput(int argc, char* argv[]){
    Parameters p;
    if(argc != 4){
        fprintf(stderr, "Uso: %s N x y.\n", argv[0]);
        exit(-1);
    }

    char* end;
    p.N = (int) strtol(argv[1], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: N deve essere un intero.\n");
        exit(-1);
    }
    if(p.N < 10 || p.N > 20){
        fprintf(stderr, "Errore: N deve essere compreso tra 10 e 20 (estremi inclusi).\n");
        exit(-1);
    }

    p.x = strtof(argv[2], &end);
    if(*end){
        fprintf(stderr, "Errore: x deve essere un float.\n");
        exit(-1);
    }
    if(p.x < 5 || p.x > 30){
        fprintf(stderr, "Errore: x deve essere compreso tra 5 e 30.\n");
        exit(-1);
    }

    p.y = strtof(argv[3], &end);
    if(*end){
        fprintf(stderr, "Errore: y deve essere un float.\n");
        exit(-1);
    }
    if(p.y < 5 || p.y > 30){
        fprintf(stderr, "Errore: y deve essere compreso tra 5 e 30.\n");
        exit(-1);
    }

    return p;
}

double genDouble(float x, float y){
    return ((double) get_random() / UINT_MAX) * (y - x) + x;
}

double** genMatrix(int N, float x, float y){
    double** A = calloc(N, sizeof(double*));
    for(int i = 0; i < N; i++){
        A[i] = calloc(N, sizeof(double));
        for(int j = 0; j < N; j++){
            A[i][j] = genDouble(x, y);
        }
    }
    return A;
}

int computeMinMax(double** A, int n, double* minp, double* maxd){
    int count = 0;
    *minp = A[0][0];
    *maxd = A[n - 1][0]; //ERRORE -> scambiato n - 1 con 0

    for(int i = 0; i < n; i++){
        if(A[i][i] < *minp){
            *minp = A[i][i];
        }
        if(A[i][n - i - 1] > *maxd){
            *maxd = A[i][n - i - 1];
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(A[i][j] <= *maxd && A[i][j] >= *minp)
                count++;
        }
    }
    
    return count;
}

double* createArray(double** A, int size, int n, double minp, double maxd){
    double* array = calloc(size, sizeof(double));
    int k = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(A[i][j] <= maxd && A[i][j] >= minp)
                array[k++] = A[i][j];
        }
    }
    return array;
}


void sortArray(double* array, int size){
    for(int i = 1; i < size; i++){
        double key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key){
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void printArray(double* array, int size){
    double media = 0;
    for(int i = 0; i < size; i++){
        printf("%lf\n", array[i]);
        media += array[i];
    }
    media /= size;
    printf("Media: %lf\n", media);
}

int main(int argc, char* argv[]){
    Parameters p = readInput(argc, argv);

    double** A = genMatrix(p.N, p.x, p.y);
    
    double minp, maxd;
    int count = computeMinMax(A, p.N, &minp, &maxd);

    double* array = createArray(A, count, p.N, minp, maxd);
    sortArray(array, count);

    printArray(array, count);
}