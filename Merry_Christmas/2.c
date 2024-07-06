/*Due stringhe si dicono sorelle se hanno lo stesso numero di vocali. Scrivere una funzione che prenda in input una matrice A di puntatori a stringhe, e restituisca un boolean che indichi se esiste una colonna di A in cui sono puntate almeno due stringhe sorelle.*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

unsigned int N = 2;
unsigned int M = 3;

int main () {
    bool CheckIfSisters (char* A[N][M], int count[N][M]);
    char* MATRICE[2][3] = {{"ciao", "aiuola", "blu"}, {"albero", "balena", "rosso"}};
    int count[2][3] = {{0,0,0},{0,0,0}};

    printf("%d", CheckIfSisters(MATRICE, count)); 
}

bool CheckIfSisters (char* A[N][M], int count[N][M]) {
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < M; j++) {
            for (unsigned int indice = 0; (*(A[i][j] + indice)) != '\0' && indice < strlen(A[i][j]); indice++) {
                if ((*(A[i][j] + indice)) == 'a' || (*(A[i][j] + indice)) == 'e' || (*(A[i][j] + indice)) == 'i' || (*(A[i][j] + indice)) == 'o' || (*(A[i][j] + indice)) == 'u') {
                    count[i][j]++;
                }
            }
        }
    }
    printf("%d %d %d %d %d %d\n", count[0][0], count[0][1], count[0][2], count[1][0], count[1][1], count[1][2]);

    for (unsigned int k = 0; k < 3; k++) {
        for (unsigned int z = 0; z < 1; z++) {
            if (count[z][k] == count[z + 1][k])
            puts("1");
            break;
        }
    }
} 
