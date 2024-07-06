// Stampa i tken di una frase in ordine inverso

#include <stdio.h>
#include <string.h>

void reverseTokens(char *sentence);

int main() {
    char text[80];
    puts("Enter a line of text: ");
    fgets(text, 80, stdin);
    
    reverseTokens(text);
}

void reverseTokens(char *sentence) {
    // prende la prima parola della frase
    char *tokenPtr = strtok(sentence," \n");

    int count = 0; // contatore di token
    char *pointers[50]; // array per memorizzare l'intera frase

    while(tokenPtr) {
        // aggiunge la parola nell'array e riceve il token successivo
        pointers[count++] = tokenPtr;
        tokenPtr = strtok(NULL, " \n");
    }
    
    // effettua un ciclo attraverso l'array a ritroso
    puts("The tokens in reverse order are: ");
    for (int i = count - 1; i >= 0; --i) {
        printf("%s ", pointers[i]);
    }
    puts("");
}
