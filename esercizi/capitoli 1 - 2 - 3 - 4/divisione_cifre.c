#include <stdio.h>

int main (void) {
    int number = 0;
    printf ("Inserisci un numero di 5 cifre: ");
    scanf ("%d", &number);
    if (number < 100000) {
        int cifra_1 = number/10000;
        number = number%10000;
        int cifra_2 = number/1000;
        number = number%1000;
        int cifra_3 = number/100;
        number = number%100;
        int cifra_4 = number/10;
        number = number%10;
        int cifra_5 = number%10;
        printf ("%d \t %d \t %d \t %d \t %d \t", cifra_1, cifra_2, cifra_3, cifra_4, cifra_5);
        if (cifra_1 == cifra_5 && cifra_2 == cifra_4){
        printf ("Il numero è palindromo! \n");
        }
    }
    else {
        printf("Il numero inserito è troppo grande \n");
    }

   

    /* for (int cifre = 0; cifre < 5; cifre++) {
        printf ("%d \t", number%10);
        number = number/10;
    } stampa il numero al contrario */

    
}