#include <stdio.h>

int main (void) {
    unsigned int counter;
    int sum = 0;
    int number = 0;

    printf ("%s", "Inserire il numero di cifre da sommare: ");
    scanf ("%u", &counter);

    for (unsigned int i = 1; i <= counter; ++i) {
        printf ("%s", "Inserire un numero intero: ");
        scanf ("%d", &number);
        sum += number;
    }
    
    printf ("The sum is: %d \n", sum);

}