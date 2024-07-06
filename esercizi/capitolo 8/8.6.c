// Stampa una riga di testo in lettere minuscole e maiuscole

#include <stdio.h>
#include <ctype.h>

int main () {
    char s[100];
    puts("Enter a line of text");
    fgets(s, 100, stdin);
    puts("\nThe line in uppercase is:");

    for(size_t i = 0; s[i] != '\0'; i++) {
        printf("%c", toupper(s[i]));
    }

    puts("\nThe line in lowercase is:");

    for(size_t i = 0; s[i] != '\0'; i++) {
        printf("%c", tolower(s[i]));
    }
}
