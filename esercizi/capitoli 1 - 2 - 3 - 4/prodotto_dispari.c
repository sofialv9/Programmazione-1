//calcola il prodotto degli interi dispari da 1 a 15

#include <stdio.h>

int main (void) {
    int prodotto;
    prodotto = 1;
    
    for (unsigned int num = 1; num <= 15; num += 2) {
        prodotto *= num;
    }
   
    printf ("Il prodotto è: %d \n", prodotto);

}