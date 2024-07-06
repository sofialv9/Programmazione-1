//Esercizio 5.32 - la funzione modifica si riferisce all'Esercizio 5.33
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
    void modifica(unsigned int counter); // prototipo
    srand(time(NULL));
    int n = 0;
    n = 1 + rand() % 1001;
    printf ("I have a number between 1 and 1000.\nCan you guess my number?\nPlease type your first guess.\n");
    int guess = 0;
    unsigned int counter = 0;
    scanf("%d", &guess);
    counter++;
    

    if (guess == n){ // risposta giusta al primo colpo
        modifica(counter);
        printf("Excellent! You guessed the number!\nWould you like to play again (y or n)? ");
        char choice = 0;
        scanf("%c", &choice);
        char y = 'y';

        if ((choice = getchar()) == y) {
            return main(); //ricomincia il programma
        }
        else {
            return 0;
        }
    }

    while (guess != n) { //risposta sbagliata

        if (guess < n) {
            printf("Too low. Try again.\n");
        }

        if (guess > n) {
            printf("Too high. Try again.\n");
        }
        
        scanf("%d", &guess);
        counter++;

        if (guess == n){
            modifica (counter);
            printf("Excellent! You guessed the number!\nWould you like to play again (y or n)? ");
            char choice = 0;
            scanf("%c", &choice);
            char y = 'y';
            if ((choice = getchar()) == y) {
               return main();
            }
            else {
                return 0;
            }
        }
        
    }
}

void modifica (unsigned int counter)
{
    if (counter < 10) {
        printf("Either you know the secret or you got lucky!\n");
    }

    if (counter == 10) {
        printf("Ahah! You know the secret!\n");
    }

    if (counter > 10) {
        printf("You should be able to do better!\n");
    }
}