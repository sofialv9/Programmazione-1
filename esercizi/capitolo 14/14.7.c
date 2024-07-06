// Riceve 2 argomenti dalla riga di comando che sono 2 nomi di file, legge i caratteri del primo file e li scrive in ordine inverso sul secondo --> ./14.7 ciao come

#include <stdio.h>

void reverseFile(FILE *inPtr, FILE *outPtr);

int main(int argc, char** argv) {
    if (argc != 3) {
        puts("Usage: copy infile outfile");
    }
    else {
        FILE *inFilePtr;
        if((inFilePtr = fopen(argv[1], "r")) != NULL) {
            FILE* outFilePtr;
            if((outFilePtr = fopen(argv[2], "w")) != NULL) {
                reverseFile(inFilePtr, outFilePtr);
            }
            else {
                printf("File \"%s\" could not be opened\n", argv[2]);
            }
        }
        else {
            printf("File \"%s\" could not be opened\n", argv[1]);
        }
    }
}

void reverseFile(FILE* inPtr, FILE* outPtr) {
    int c; // carattere corrente

    // se non è la fine del file
    if((c = fgetc(inPtr)) != EOF) {
        reverseFile(inPtr, outPtr);
    }
    fputc(c, outPtr); // scrive il carattere sul file di output
}