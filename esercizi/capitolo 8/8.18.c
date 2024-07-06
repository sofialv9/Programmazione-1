// Calcola il totale dele volte in cui un carattere compare in 4 righe di testo

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[4][100];
    puts("Enter four lines of text:");

    for (size_t i = 0; i < 4; ++i) {
        fgets(&text[i][0], 100, stdin);
    }
    
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; text[i][j] != '\0'; ++j) {
            text[i][j] = tolower(text[i][j]);
        }
    }

    char key;
    puts("Enter a search character:");
    key = getchar();
    int counter = 0;

    for (size_t i = 0; i < 4; ++i) {
        char* strPtr = &text[i][0];
        while (strPtr = strchr(strPtr, key)) {
            ++counter;
            ++strPtr;
        }
    }
    
    printf("The total occurences of the character '%c' in the text are %d\n", key, counter);
}