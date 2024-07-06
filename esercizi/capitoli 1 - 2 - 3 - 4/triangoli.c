#include <stdio.h>

int main () {
    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j <= i; j++) {
            printf ("*");
        }
        puts ("");
    }

    for (int i = 10; i > -1; i--) {
        for (int j = 0; j <= i; j++) {
            printf ("*");
        }
        puts ("");
    }

    for (int i = 10; i > -1; i--) {
        for (int j = 10 - i; j > 0; j--) {
            printf (" ");
        }
        
        for (int j = 0; j <= i; j++) {
            printf ("*");
        }

        puts ("");
    }

    for (int i = 0; i <= 10; i++) {
        for (int j = 10 - i; j > 0; j--) {
            printf (" ");
        }
        
        for (int j = 0; j <= i; j++) {
            printf ("*");
        }

        puts ("");
    }
    

}