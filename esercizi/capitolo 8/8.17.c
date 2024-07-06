// Conta le occorrenze di una sottostringa

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main () {
    char text[3][80]; // array per tenere il testo inserito dal'utente
    puts("Enter three lines of text:");

    // legge in 3 righe di testo
    for (size_t i = 0; i < 3; i++) { 
        fgets(&text[i][0], 80, stdin);
    }
    
    // converte tutti i caratteri in minuscolo
    for (size_t i = 0; i < 3; i++) { // ciclo attraverso le righe di testo
        for (size_t j = 0; text[i][j] != '\0'; j++) { // ciclo per i singoli caratteri delle righe di testo
        text[i][j] = tolower(text[i][j]);
        }
    }
    
    puts("Enter a search string:");
    char search[20];
    scanf("%19s", search);
    int counter = 0; // occorrenze della stringa cercata
    

    // searchPtr --> 1° carattere 1° riga --> 1° occorrenza della parola --> 2° --> 3°...
    for (size_t i = 0; i < 3; i++) { // ciclo attraverso le righe di testo
        char* searchPtr = &text[i][0]; // imposta il puntatore al primo carattere della riga selezionata
        
        while (searchPtr = strstr(searchPtr, search)) { // ripete finché strstr non restituisce NULL
            counter++;
            ++searchPtr;
        }
    }

    printf("The total occurences of \"%s\" in the text is %d.\n", search, counter);
}