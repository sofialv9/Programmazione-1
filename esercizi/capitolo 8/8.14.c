// Legge un numero di telefono come stringa e lo converte in numero

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[20];

    puts("Enter a telephone number in the form (555) 555-5555.");
    fgets(input, 20, stdin);

    // converte il token del prefisso in un intero
    int prefix = strtol(strtok(input, "()"), 0, 0);

    // prende i 2 token successivi e li copia in telephoneString
    char telephoneString[10] = {'\0'};
    strcat (telephoneString, (strtok(NULL, " - ")));
    strcat (telephoneString, (strtok(NULL, " \n")));

    // converte il resto del numero (dopo il prefisso) in un intero long
    long int telephoneNumber = strtol(telephoneString, 0, 0);
    printf("The phone number is: %d %ld\n", prefix, telephoneNumber);
}