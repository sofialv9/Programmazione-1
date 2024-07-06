#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct parameters{
    int n;
    char s1[255];
    char s2[255];
    char c;
} Parameters;

Parameters readInput(int argc, char* argv[]){
    Parameters p;
    if(argc != 5){
        fprintf(stderr, "Uso %s n s1 s2 c\n", argv[0]);
        exit(-1);
    }

    char* end;
    p.n = (int) strtol(argv[1], &end, 10);

    strcpy(p.s1, argv[2]);
    if(strlen(p.s1) != p.n){
        fprintf(stderr, "Errore: s1 deve avere lunghezza %d\n", p.n);
        exit(-1);
    }

    strcpy(p.s2, argv[3]);
    if(strlen(p.s2) != p.n){
        fprintf(stderr, "Errore: s2 deve avere lunghezza %d\n", p.n);
        exit(-1);
    }

    p.c = argv[4][0];

    return p;
}

// Sostituisce un carattere di una stringa con il corrispondente in un'altra stringa
char* replaceChar(char* s1, char* s2, char c){
    char* out = calloc(strlen(s1), sizeof(char) + 1);
    for(int i = 0; i < strlen(s1); i++){
        if(s1[i] == c){
            out[i] = s2[i];
        } else {
            out[i] = s1[i];
        }
    }
    return out;
}

// Crea l'inverso di una stringa
char* invertString(char* s){
    char* out = calloc(strlen(s) + 1, sizeof(char));
    for(int i = 0; i < strlen(s); i++){
        out[strlen(s) - i - 1] = s[i];
    }
    out[strlen(s)] = 0;
    return out;
}

// Ordina una stringa in ordine lessografico ascendente (bubblesort)
void sort(char* s){
    for(int pass = 0; pass < strlen(s) - 1; pass++){
        for(int i = 0; i < strlen(s) - 1 - pass; i++){
            if(s[i] > s[i + 1]){
                char tmp = s[i];
                s[i] = s[i + 1];
                s[i + 1] = tmp;
            }
        }
    }
}

// Stampa la stringa sostituendo dei caratteri
void printResult(char* s){
    for(int i = 0; i < strlen(s); i++){
        if(s[i] % 2 == 1){
            printf("*");
        } else {
            printf("%c", s[i]);
        }
    }
    puts("");
}

int main(int argc, char* argv[]){
    // A
    Parameters p = readInput(argc, argv);

    // B - costruisce una nuova stringa s3 sostituendo tutte le occorrenze del carattere c in s1 con i caratteri che si trovano in s2 nelle posizioni corrispondenti.
    char* s3 = replaceChar(p.s1, p.s2, p.c);

    // C - crea una nuova stringa s4 invertendo l'ordine dei caratteri in s2.
    char* s4 = invertString(p.s2);

    // D - crea la stringa s5 concatenando le stringhe s3 e s4 e la ordina in ordine lessicografico ascendente.
    char* s5 = strcat(s3, s4);
    sort(s5);
    
    // E - stampa la strnga s5 sostituendo con * i caratteri i cui codici numerici relativi sono dispari.
    printResult(s5);
}