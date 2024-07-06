#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
        fprintf(stderr, "Uso: %s n s1 s2 c.\n", argv[0]);
        exit(-1);
    }
    
    char* end;
    p.n = (int) strtol(argv[1], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: n deve essere un intero.\n");
        exit(-1);
    }
    
    strcpy(p.s1, argv[2]);
    if(strlen(p.s1) > p.n){
        fprintf(stderr, "Errore: la stringa s1 deve avere una lunghezza pari a %d.\n", p.n);
        exit(-1);
    }
    strcpy(p.s2, argv[3]);
    if(strlen(p.s2) > p.n){
        fprintf(stderr, "Errore: la stringa s2 deve avere una lunghezza pari a %d.\n", p.n);
        exit(-1);
    }

    if(strlen(argv[4]) > 1){
        fprintf(stderr, "Errore: c deve essere un carattere.\n");
        exit(-1);
    }
    p.c = argv[4][0];

    return p;
}

char* replaceChar(char* s1, char* s2, char c){
    char* out = calloc(strlen(s1), sizeof(char));
    for(int i = 0; i < strlen(s1); i++){
        if(s1[i] == c){
            out[i] = s2[i];
        } else {
            out[i] = s1[i];
        }
    }
    return out;
}

char* invertString(char* s){
    char* out = calloc(strlen(s), sizeof(char));
    for(int i = 0; i < strlen(s); i++){
        out[strlen(s)- i - 1] = s[i];
    }
    return out;
}

// insertion sort
void sort(char* s){
    for(int i = 1; i < strlen(s); i++){
        char key = s[i];
        int j = i - 1;
        while(j >= 0 && s[j] > key){
            s[j + 1] = s[j];
            j--;
        }
        s[j + 1] = key;
    }
}

void printResult(char* s){
    for(int i = 0; i < strlen(s); i++){
        int n = (int) s[i];
        if(n % 2 == 1){
            printf("*");
        } else {
            printf("%c", s[i]);
        }
    }
}

int main(int argc, char* argv[]){
    Parameters p = readInput(argc, argv);

    char* s3 = replaceChar(p.s1, p.s2, p.c);

    char* s4 = invertString(p.s2);

    char* s5 = strcat(s3, s4);
    sort(s5);

    printResult(s5);
}