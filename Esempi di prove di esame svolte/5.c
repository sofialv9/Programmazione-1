// NON FUNZIONA (matrice non contiene tutti i valori)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct parameters{
    char input[255];
    char output[255];
} Parameters;

Parameters readParameters(int argc, char* argv[]){
    Parameters p;
    if(argc != 3){
        fprintf(stderr, "Uso: %s input.txt output.txt\n", argv[0]);
        exit(-1);
    }

    strcpy(p.input, argv[1]);
    char* extension = strrchr(p.input, '.');
    if(strcmp(extension, ".txt") != 0){
        fprintf(stderr, "Errore: il file input deve avere estensione .txt.\n");
        exit(-1);
    }

    strcpy(p.output, argv[2]);
    extension = strrchr(p.output, '.');
    if(strcmp(extension, ".txt") != 0){
        fprintf(stderr, "Errore: il file output deve avere estensione .txt.\n");
        exit(-1);
    }

    return p;
}

// Crea una matrice A di puntatori a float dal file di input che contiene n righe di testo costituite da m valori separati da spazi. Le dimensioni n e m sono dedotte a partire dal file.
float*** createMatrix(char* fname, int* n, int* m){
    FILE* fPtr = fopen(fname, "r");
    if(!fPtr){
        fprintf(stderr, "Errore: impossibile aprire il file %s.\n", fname);
        exit(-1);
    }

    // Inizializza a zero le dimensioni della matrice
    *n = 0;
    *m = 0;

    char* end;
    char s[1000];

    //Il ciclo esterno conta il numero di righe del file
    do {
        end = fgets(s, 1000, fPtr);
        (*n)++; // aumenta il contatore delle righe
        char* tok;
        char* tmp = s;
        // Il ciclo interno conta il numero di parole del file
        do{
            tok = strtok(tmp, "\n");
            tmp = NULL;
            (*m)++; // aumenta il contatore delle colonne
        } while(tok);
    } while(end);

    (*n)--;
    (*m)--;

    // Torna all'inizio del file
    fseek(fPtr, 0, 0);

    // Alloca una matrice di puntatori a float
    float*** A = calloc(*n, sizeof(float**));
    for(int i = 0; i < *n; i++){
        A[i] = calloc(*m, sizeof(float*));
        for(int j = 0; j < *m; j++){
            A[i][j] = NULL;
        }
    }

    // Legge una riga dal file
    for(int i = 0; i < *n; i++){
        end = fgets(s, 1000, fPtr);
        char* tok;
        char* tmp = s;
        // Legge le parole di una riga
        for(int j = 0; j < *m; j++){
            tok = strtok(tmp, " \n");
            tmp = NULL; // nelle successive chiamate di strtok tmp deve essere NULL
            // Se la parola esiste la converte in float e la inserisce nella matrice
            if(tok){
                char** end = malloc(sizeof(char*));
                A[i][j] = malloc(sizeof(float));
                *(A[i][j]) = strtof(tok, end);
                free(end);
            }
        }
    }
    return A;
}

// Elimina dalla matrice i valori di A che sono superiori ai valori medi delle righe corrispondenti, fa puntare i puntatori relativi ai valori identificati a NULL e libera la relativa memoria.
void sparsify(float*** A, int n, int m){
    // scorre le righe
    for(int i = 0; i < n; i++){
        // inizializza la media della riga e il contatore di elementi non nulli
        float media = 0;
        int count = 0;
        for(int j = 0; j < m; j++){
            // se l'elemento non è NULL
            if(A[i][j]){
                // aggiorna la media e il contatore
                media += *A[i][j];
                count++;
            }
        }
        media /= count;
        
        // se gli elementi non sono NULL e sono superiori alla media della riga vengono fatti puntare a NULL e la memoria da essi occupata liberata.
        for(int j = 0; j < m; j++){
            if(A[i][j] && *A[i][j] > media){
                float* tmp = A[i][j];
                A[i][j] = NULL;
                free(tmp);
            }
        }
    }  
}

// Crea un array di float inserendo i valori puntati dai puntatori non NULL in A
float* collect(float*** A, int n, int m, int* size){
    *size = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            // calcola la dimensione dell'array come contatore degli elementi non NULL della matrice
            if(A[i][j]){
                (*size)++;
            }
        }
    }

    float* out = calloc(*size, sizeof(float));
    int c = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(A[i][j]){
                out[c++] = *A[i][j];
            }
        }
    }

    return out;
}

void writeToFile(char* fname, float* array, int size){
    FILE* fPtr = fopen(fname, "w");
    if(!fPtr){
        fprintf(stderr, "Errore: impossibile aprire il file %s.\n", fname);
        exit(-1);
    }

    for(int i = 0; i < size; i++){
        fprintf(fPtr, "%5.2f\n", array[i]);
    }
}

int main(int argc, char* argv[]){
    // A
    Parameters p = readParameters(argc, argv);
    // B
    int n, m;
    float*** A = createMatrix(p.input, &n, &m);

    // C
    sparsify(A, n, m);

    // D
    int size;
    float* array = collect(A, n, m, &size);
    
    // E
    writeToFile(p.output, array, size);
}