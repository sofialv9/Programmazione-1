/*Scrivere una funzione che prenda in input un parametro formale matrice quadrata Q di interi ed un double w, e restituisca un valore booleano true se esiste almeno una colonna della matrice Q tale che il rapporto tra la somma degli elementi della colonna stessa e la somma degli elementi della diagonale secondaria di Q sia maggiore di w.*/

#include <stdio.h>
#include <stdbool.h>
unsigned int N;

int main () {
    bool funzione (int A[N][N], double w);
    int Q[10][10];
    
    for (unsigned int i = 0; i < 10; i++) {
        for (unsigned int j = 0; j < 10; j++) {
            Q[i][j] = j + i;
        }
    }

   /* for (unsigned int i = 0; i < 10; i++) {
        unsigned int counter = 0;
        for (unsigned int j = 0; j < 10; j++) {
            printf("%d\t", Q[i][j]);
            counter++;
            if (counter == 10)
            puts("");
        }
    } */

    printf("%d", funzione(Q, 0.5)); //RITORNA 0

}



bool funzione (int A[N][N], double w) {
    unsigned int sumDiagonaleSecondaria = 0;
    unsigned int sumColumn = 0; 
    double n = 0;
    int control = -1;   
    for (unsigned int i = 0; i < N; i++) {
        sumDiagonaleSecondaria += A[i][N - i - 1];
    }


    for (unsigned int j = 0; j < N; j++) {
        for (unsigned int i = 0; i < N; i++) {
            sumColumn += A[i][j];
        }
        
        n = ((double) sumColumn / sumDiagonaleSecondaria);

        if (n > w) {
           control = true;
        } 
    }
    return control;
    // return false;
}
