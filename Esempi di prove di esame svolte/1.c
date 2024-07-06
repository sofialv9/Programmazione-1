#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

typedef struct parameters{
    int k;
    char* w;
    int n;
    int m;
} Parameters;

Parameters readInput(int argc, char* argv[]){
    Parameters p;

    if(argc != 5){
        fprintf(stderr, "Uso: %s k w n m.\n", argv[0]);
        exit(-1);
    }

    char* end;
    p.k = (int) strtol(argv[1], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: k è un intero non valido.\n");
        exit(-1);
    }

    if(p.k < 10 || p.k > 15){
        fprintf(stderr, "Errore: k deve essere compreso tra 10 e 15 (estremi inclusi).\n");
        exit(-1);
    }

    // Controlla che argv[2] sia un carattere e non una stringa più lunga
    if(strlen(argv[2]) > 1){
        fprintf(stderr, "Errore: il secondo parametro deve essere un carattere.\n");
        exit(-1);
    }

    // Estrae il carattere all'interno di argv[2] e controlla che sia comrpeso tra 'a' e 'z'
    p.w = argv[2][0]; 
    if(p.w < 'a' || p.w > 'z'){
        fprintf(stderr, "Errore: w deve essere un carattere tra a e z.\n");
        exit(-1);
    }

    p.n = (int) strtol(argv[3], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: n è un intero non valido.\n");
        exit(-1);
    }

    p.m = (int) strtol(argv[4], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: m è un intero non valido.\n");
        exit(-1);
    }

    if(p.n < 4 || p.n > 8){
        fprintf(stderr, "Errore: n deve essere compreso tra 4 e 8 (estremi inclusi).\n");
        exit(-1);
    }

    if(p.m < 4 || p.m > 8){
        fprintf(stderr, "Errore: m deve essere compreso tra 4 e 8 (estremi inclusi).\n");
        exit(-1);
    }

    return p;
}

// Alloca una matrice di stringhe n x m
char*** allocateS(int n, int m){
    char*** S = calloc(n, sizeof(char**));
    for(int i = 0; i < n; i++){
        S[i] = calloc(m, sizeof(char*));
    }
    return S;
}

// Genera una stringa di caratteri casuali compresi tra a e z
char* genString(int lenght, char min, char max){
    char* out = calloc(lenght, sizeof(char));
    for(int i = 0; i < lenght; i++){
        out[i] = get_random() % (max - min + 1) + min;
    }
    return out;
}

// Riempie la matrice S con stringhe di lunghezza k composte da caratteri in [a,z]
void fillS(char*** S, int n, int m, int k){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            S[i][j] = calloc(k, sizeof(char));
            for(int l = 0; l < k; l++)
            S[i][j][l] = get_random() % ('z'-'a'+ 1) + 'a';
        }
    }
}

// void fillS(char*** S, int n, int m, int k){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            S[i][j] = genString(k, 'a', 'z');
        }
    }
//}

// Bubble sort - ordina ogni colonna in ordinamento lessografico (crescente)
void sortS(char*** S, int n, int m){
    // scorre le colonne
    for(int j = 0; j < m; j++){
        // fa n - 1 passate
        for(int pass = 0; pass < n - 1; pass++){
            // scorre gli elementi delle colonne ignorando quelli già ordinati dalle precedenti passate
            for(int i = 0; i < n - 1 - pass; i++){
                // confronta stringhe successive della colonna: se la precedente  maggiore della successiva le scambia
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
            printf("%s ", S[i][j]);
        }
        puts("");
    }
}

// Conta le occorrenze del carattere w nella stringa s
int conta(char* s, char w){
    int count = 0;
    for(int i = 0; i < strlen(s); i++){
        if(s[i] == w){
            count++;
        }
    }
    return count;
}

// Stampa la stringa con il numero di occorrenze del carattere w maggiore e sostituisce la w con un asterisco
void printMax(char*** S, int n, int m, char w){
    // inizializza gli indici di riga e colonna relativi alla stringa da ritornare e il valore di occorrenze massime del carattere w nella stringa
    int i_max = 0;
    int j_max = 0;
    int max = 0;

    // iterazione per riga e per colonna
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            // conta le occorrenze di w nella stringa corrente
            int count = conta(S[i][j], w);
            // se count è maggiore di max aggiorna gli indici e il numero di occorrenze massime
            if(count > max){
                max = count;
                i_max = i;
                j_max = j;
            }
        }
    }

    printf("\nStringa on %d occorrenze di '%c' trovata agli indici %d %d: ", max, w, i_max, j_max);

    // Itera lungo i caratteri della stringa con il numero massimo di occorrenze di w. Se è uguale a w stampa un asterisco, altrimenti stampa il carattere stesso
    for(int i = 0; i < strlen(S[i_max][j_max]); i++){
        // estrae un carattere dalla stringa
        char c = S[i_max][j_max][i];
        c = (c == w) ? '*' : c;
        printf("%c", c);
    }
    puts("");
}

//Unione delle due funzioni precedenti
void printMax(char*** S, int n, int m, char w){
    // inizializza indici di riga e colonna e numero di occorrenze di w
    int max = 0;
    int i_max = 0;
    int j_max = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            // azzera il contatore di occorrenze di w ad ogni colonna
            int count = 0;
            for(int k = 0; k < strlen(S[i][j]); k++){
                if(S[i][j][k] == w){
                    count++;
                }
            }
            // se il contatore è maggiore del massimo aggiorna il massimo
            if(count > max){
                    max = count;
                    i_max = i;
                    j_max = j;
            }
        }
    }

    // Sostituisce il carattere w con *
    for(int k = 0; k < strlen(S[i_max][j_max]); k++){
        if(S[i_max][j_max][k] == w){
            S[i_max][j_max][k] = '*';
        }
    }

    printf("La stringa con il maggior numero di occorrenze del carattere '%c' è stata trovata agli indici %d %d: %s.\n", w, i_max, j_max, S[i_max][j_max]);
}


int main(int argc, char* argv[]){
    // A
    Parameters p = readInput(argc, argv);
    // B
    char*** S = allocateS(p.n, p.m);
    // C
    fillS(S, p.n, p.m, p.k);
    // D
    sortS(S, p.n, p.m);
    // E
    printMatrix(S, p.n, p.m);
    // F
    printMax(S, p.n, p.m, p.w);
}