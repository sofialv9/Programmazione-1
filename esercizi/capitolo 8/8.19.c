// Conta il totale delle volte in cui ogni lettera dell'alfabeto compare nelle righe di testo

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[3][80];

    puts("Enter 3 lines of text:");

    for (size_t i = 0; i < 3; ++i) {
        fgets(&text[i][0], 80, stdin);
    }

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; text[i][j] != '\0'; ++j) {
            text[i][j] = tolower(text[i][j]);
        }
    }

    char characters[26] = {0}; // totali per ciascuna lettera
    int count = 0; // totale per lettera corrente

    for (size_t i = 0; i < 26; ++i) { // ciclo attraverso l'alfabeto
        count = 0;
        for (size_t j = 0; j < 3; ++j) { // ciclo attraverso le righe di testo
            char *searchPtr = &text[j][0];

            while ((searchPtr = strchr(searchPtr, 'a' + i))) {
                ++count;
                ++searchPtr;
            }
        }

        characters[i] = count;
    }
    
    puts("\nTotal occurences of each character:");

    for (int i = 0; i < 26; ++i) {
        printf("%c : %3d\n", 'a' + i, characters[i]);
    }
}