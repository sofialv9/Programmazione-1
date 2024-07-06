#include <stdio.h>

int main (void) {

    unsigned int fattoriale = 1;
    unsigned int i = 1;
    
    for (unsigned int num = 1; num <= 5; num++) {
        
        while (i <= num) {
            fattoriale *= i;
            i++;
        }
        printf ("%d \t", fattoriale);
    }
    
    puts ("");
    
    }
