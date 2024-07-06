#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

typedef struct parametri{
    int k;
    char w;
    int N;
    int M;
} Parametri;

Parametri readInput(int argc, char* argv[]){
    Parametri p;
    if(argc != 5){
        fprintf(stderr, "Uso: %s k w N M.\n", argv[0]);
        exit(-1);
    }

    char* end;
    p.k = (int) strtol(argv[1], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: k deve essere un intero.\n");
        exit(-1);
    }
    if(p.k < 10 || p.k > 15){
        fprintf(stderr, "Errore: k deve essere compreso tra 10 e 15 (estremi inclusi).\n");
        exit(-1);
    }

    if(strlen(argv[2]) != 1){
        fprintf(stderr, "Errore: w deve essere un carattere.\n");
        exit(-1);
    }
    p.w = argv[2][0];
    if(p.w < 'a' || p.w > 'z'){
        fprintf(stderr, "Errore: w deve essere un carattere tra a e z (estremi inclusi).\n");
        exit(-1);
    }

    p.N = (int) strtol(argv[3], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: N deve essere un intero.\n");
        exit(-1);
    }
    if(p.N < 4 || p.N > 8){
        fprintf(stderr, "Errore: N deve essere compreso tra 4 e 8 (estremi inclusi).\n");
        exit(-1);
    }

    p.M = (int) strtol(argv[4], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: M deve essere un intero.\n");
        exit(-1);
    }
    if(p.M < 4 || p.M > 8){
        fprintf(stderr, "Errore: M deve essere compreso tra 4 e 8 (estremi inclusi).\n");
        exit(-1);
    }
    return p;
}

char*** allocateS(int n, int m){
    char*** S = calloc(n, sizeof(char**));
    for(int i = 0; i < n; i++){
        S[i] = calloc(m, sizeof(char*));
    }
    return S;
}

void fillS(char*** S, int n, int m, int k){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            S[i][j] = calloc(k, sizeof(char));
            for(int l = 0; l < k; l++)
            S[i][j][l] = get_random() % ('z'-'a'+ 1) + 'a';
        }
    }
}

void sortS(char*** S, int n, int m){
    for(int j = 0; j < m; j++){
        for(int pass = 0; pass < n - 1; pass++){
            //ERRORE -> non ricordavo il ciclo più interno
            for(int i = 0; i < n - 1 - pass; i++){
                if(strcmp(S[i][j], S[i + 1][j]) > 0){
                    char* tmp = S[i][j];
                    S[i][j] = S[i + 1][j];
                    S[i + 1][j] = tmp;
                }
            }
        }
    }
}

void printMatrix(char*** S, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%s\n", S[i][j]);
        }
    }
}

void printMax(char*** S, int n, int m, char w){
    int max = 0;
    int i_max = 0;
    int j_max = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int count = 0;
            for(int k = 0; k < strlen(S[i][j]); k++){
                if(S[i][j][k] == w){
                    count++;
                }
            }
            if(count > max){
                    max = count;
                    i_max = i;
                    j_max = j;
            }
        }
    }

    for(int k = 0; k < strlen(S[i_max][j_max]); k++){
        if(S[i_max][j_max][k] == w){
            S[i_max][j_max][k] = '*';
        }
    }

    printf("La stringa con il maggior numero di occorrenze del carattere '%c' è stata trovata agli indici %d %d: %s.\n", w, i_max, j_max, S[i_max][j_max]);
}

int main(int argc, char* argv[]){
    Parametri p = readInput(argc, argv);

    char*** S = allocateS(p.N, p.M);
    fillS(S, p.N, p.M, p.k);
    sortS(S, p.N, p.M);
    printMatrix(S, p.N, p.M);
    printMax(S, p.N, p.M, p.w);
}