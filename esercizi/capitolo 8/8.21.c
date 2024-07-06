// Mette in ordine alfabetico una riga di stringhe

#include <stdio.h>
#include <string.h>

void bubbleSort(char a[][50]);

int main() {
    char array[10][50]; // 10 stringhe inserite dall'utente
    
    for (size_t i = 0; i < 10; i++) {
        puts("Enter a string:");
        scanf("%49s", &array[i][0]);
    }

    bubbleSort(array); // ordina l'array di stringhe

    puts("The strings in sorted order are:");
    
    //stampa le stringhe in ordine
    for (size_t i = 0; i < 10; i++) {
        printf("%s\n", &array[i][0]);
    }
}

void bubbleSort(char a[][50]) {
    char temp[50]; // array temporaneo

    //fa 9 passate
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            // scambia le stringhe se necessario
            if(strcmp(&a[j][0], &a[j+1][0]) > 0) {
                strcpy(temp, &a[j][0]);
                strcpy(&a[j][0], &a[j+1][0]);
                strcpy(&a[j+1][0], temp);
            }
        }
    }

}