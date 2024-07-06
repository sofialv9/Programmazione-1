//conta vocali di una parola
#include <stdio.h>
#include <string.h>

int main () {
    char* s = "ciao";
    int counter = 0;
    for (unsigned int indice = 0; (s[0 + indice] ) != '\0' && indice < strlen(s); indice++) {
        if (s[0 + indice] == 'a' || s[0 + indice] == 'e' || s[0 + indice] == 'i' || s[0 + indice] == 'o' || s[0 + indice] == 'u') {
            counter++;
        }
    }
    printf ("%d\n", counter);
}