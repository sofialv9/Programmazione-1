//determina i 2 valori più grandi tra 10 numeri

#include <stdio.h>

int main (void){
    int number = 0;
    int largest = 0;
    int second_largest = 0;
    int counter = 0;
    while (++counter <= 10){
        printf ("Enter an integer: ");
        scanf ("%d", &number);
        if (number > largest){
            largest = number;
        }
        else if (number > second_largest){
            second_largest = number;
        }
        }
    printf ("The largest number is %d, the second largest is %d \n", largest, second_largest);

    }


