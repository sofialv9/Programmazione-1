// Lege da tastiera una riga di testo e una stringa da ricercare e cerca nella riga la prima occorrenza della stringa.

#include <stdio.h>
#include <string.h>

int main() {
    char text[100];
    char key[20];
    puts("Enter a line of text: ");
    fgets(text, 100, stdin);
    puts("Enter the sentence you are searching for: ");
    scanf("%20s", key);

    // Cerca la stringa di ricerca nel testo
    char* searchPtr = strstr(text, key);
    if (searchPtr) {
        printf("\n%s\n%s \"%s\":\n%s\n", "The remainder of the line beginning with", "the first occurence of", key, searchPtr);

        // cerca la seconda occorrenza
        searchPtr = strstr(searchPtr + 1, key);

        if (searchPtr) {
            printf("\n%s\n%s \"%s\":\n%s\n", "The remainder of the line beginning with", "the second occurence of", key, searchPtr);
        }
        else {
            puts("The sentence appears only once.");
        }
    }
    else {
        puts("Sentence not found.");
    }
    
}