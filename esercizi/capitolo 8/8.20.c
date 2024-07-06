// Conta il numero totale di parole contenute in 3 righe di testo

#include <stdio.h>
#include <string.h>

int main() {
    char text[3][80];

    puts("Enter 3 lines of text:");

    for (size_t i = 0; i < 3; ++i) {
        fgets(&text[i][0], 80, stdin);
    }
    
    int counter = 0;

    for (size_t i = 0; i < 3; ++i) { // ripete il ciclo per le 3 righe di testo
        char* tokenPtr = strtok(&text[i][0], " \n"); // ottiene il 1° token

        while(tokenPtr) { // finchè tokenPtr non è uguale a NULL
            ++counter;
            tokenPtr = strtok(NULL, " \n"); // riceve il token successivo
        }
    }
    
    printf("\nThe total number of words is: %d\n", counter);
}