#include <stdio.h>

int main (void){
    int number = 1;
    int counter = 0;
    printf ("N \t 10*N \t 100*N \t 1000*N \n");
    while (++counter <= 10) {
        printf ("%d \t %d \t %d \t %d \n", number, number*10, number*100, number*1000);
        number++;
    }
}