// Scrive frasi casuali in inglese

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int main () {
    // inizializza 4 array di stringhe (puntatori a char)
    char* article[] = {"the", "a", "one", "some", "any"};
    char* noun[] = {"boy", "girl", "dog", "town", "car"};
    char* verb[] = {"drove", "jumped", "ran", "walked", "skipped"};
    char* preposition[] = {"to", "from", "over", "under", "on"};
    char sentence[100] = ""; // frase compiuta

    // crea 20 frasi scegliendo a caso parti di frase
    for (size_t i = 0; i < 20; i++) {
        strcat(sentence, article[rand() % 5]);
        strcat(sentence, " ");
        strcat(sentence, noun[rand() % 5]);
        strcat(sentence, " ");
        strcat(sentence, verb[rand() % 5]);
        strcat(sentence, " ");
        strcat(sentence, preposition[rand() % 5]);
        strcat(sentence, " ");
        strcat(sentence, article[rand() % 5]);
        strcat(sentence, " ");
        strcat(sentence, noun[rand() % 5]);

        // converte in maiuscolo la prima lettera e stampa la frase
        putchar(toupper(sentence[0]));
        printf("%s.\n", &sentence[1]);
        sentence[0] = '\0'; // cancella la frase appena stampata per memorizzare la successiva
    }

}