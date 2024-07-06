#include <stdio.h>
#include <stdlib.h>

int main() {
    
    // stampa le scelte per l'utente
    printf("%s%s\n%s\n%s", "1 Read from standard input; ", "write to standard output", "2 Read from a file; write to file", "Enter choice: ");
    char choice[2]; // scelta di menù dell'utente
    scanf("%s", choice);

    // finché l'utente non inserisce una scelta valida
    while (choice[0] != '1' && choice[0] != '2') {
        printf("%s", "Invalid choice. Choose again: ");
        scanf("%s", choice);
    }

    FILE* infilePtr; // puntatore al file di input
    FILE* outfilePtr; // puntatore al file di output

    // se l'utente sceglie l'opzione 2
    if (choice[0] == '2') {
        printf("%s", "Enter input file name: ");
        char input[20];
        scanf("%s", input);

        printf("%s", "Enter output file name: ");
        char output[20];
        scanf("%s", output);

        // esce dal programma se non puoi aprire il file di input
        if ((infilePtr = fopen(input, "r")) == NULL) {
            printf("Unable to open %s\n", input);
            exit(1);
        }

        // esce dal programma se non puoi aprire il file di output
        if ((outfilePtr = fopen(output, "r")) == NULL) {
            printf("Unable to open %s\n", output);
            fclose(infilePtr);
            exit(1);
        }
    }
    else { // se l'utente sceglie l'opzione 1
        infilePtr = stdin;
        outfilePtr = stdout;
    }

    // se l'utente sceglie l'opzione 1
    if (choice[0] == '1') {
        // richiede all'utente il testo
        puts("Enter a line of text: ");
        scanf(" "); // Elimina spazi e newline all'inizio dello stream di input
    }

    char c; // carattere corrente
    char sentence[80]; // testo dell'utente o del file di input
    unsigned int i = 0; // contatore caratteri

    // leggi ciascun carattere usando fgetc
    while ((c = fgetc(infilePtr)) != '\n' && !feof(infilePtr)) {
        sentence[i++] = c;
    }

    // aggiungi il carattere di terminazione e stampa il testo con fputs
    sentence[i] = '\0';
    fputs("\nThe line entered was:\n", outfilePtr);
    fputs(sentence, outfilePtr);

    // chiudi i puntatori ai file
    if (choice[0] == '2') {
        fclose(infilePtr);
        fclose(outfilePtr);
    }
}