#include "helpers.h"
#include "stringcomp.h"
#include <stdlib.h>
#include <stdio.h>

// legge gli argomenti da linea di comando
void readInput(char *argv[], char** file, char** alfabeto, int* n, short *k) {
   *file = argv[1]; // faccio puntare file alla stringa in argv[0] (argv[0] è un puntatore mentre file è un puntatore a un puntatore)
   *alfabeto =  argv[2]; // faccio puntare alfabeto alla stringa in argv[1]

   sscanf(argv[3], "%d", n); //leggo un intero da argv[3] e lo metto in n
   sscanf(argv[4], "%hi", k); //leggo un intero da argv[4] e lo metto in n
}


// crea un array di n stringhe casuali di lunghezza k
char** getArray(const char* alfabeto, int n, short k) {
    char** array = calloc(n, sizeof(char*));
    
    for(int i = 0; i<n; i++) {
        array[i] = sampleString(alfabeto, k);
    }

    return array;
}