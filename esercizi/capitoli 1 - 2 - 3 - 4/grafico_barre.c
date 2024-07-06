#include <stdio.h>

int main () {
    int num = 0;
    int counter = 0;

    while (++counter <= 5) {
        printf ("Inserisci un numero tra 1 e 30: ");
        scanf ("%d", &num);
        
        for (int i = 1; i <= num; i++) {
            printf ("*");
        }

        puts ("");
    }

}
    