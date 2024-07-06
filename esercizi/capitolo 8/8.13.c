// Trasforma frasi in inglese in latino maccheronico (sposta la prima lettera alla fine della parola e aggiunge "ay")

#include <stdio.h>
#include <string.h>

void printLatinWord(char *word);

int main() {
    
    char sentence[80];
    puts("Enter a sentence: ");
    fgets(sentence, 80, stdin);
    puts("\nThe sentence in pig Latin is: ");

    char *tokenPtr = strtok(sentence, " \n");

    // se tokenPtr non è uguale a NULL
    while(tokenPtr) {
        // passa il token alla funzione e riceve il token successivo
        printLatinWord(tokenPtr);
        tokenPtr = strtok(NULL, " \n");
        // stampa uno spazio se token non è NULL
        if (tokenPtr) {
           printf("%s", " ");
        }
    }
    
    puts(".");
}

// Converte la parola in inglese in latino maccheronico
void printLatinWord(char *word) {
    for (size_t i = 1; i < strlen(word); i++) {
        printf("%c", word[i]); // stampa la parola a partire dalla seconda lettera
    }

    printf("%c%s", word[0], "ay"); // aggiunge la 1a lettera + ay all'inizio della frase
}