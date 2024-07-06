#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stringcomp.h"
#include "filemngt.h"
#include "helpers.h"

// il main restituisce un valore che indica se il programma è stato eseguito correttamente
// return 0 - termina prematuramente l'esecuzione del programma
// return -1 - termina in caso di errore

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if (argc != 5) {
        // scriviamo su standard error
        fprintf(stderr, "Uso: %s outfile alfabeto n k\n", argv[0]);
        return -1; //usciamo restituendo un codice di terminazione diverso da zero
    } else {
        char *outfile, *alfabeto;
        int n;
        short k;

        readInput(argv, &outfile, &alfabeto, &n, &k);
        char** array = getArray(alfabeto, n, k);
        if(!writeToFile(outfile, array, n)){
            fprintf(stderr, "Errore nella scrittura del file\n");
            return -1;
        }
    }
}