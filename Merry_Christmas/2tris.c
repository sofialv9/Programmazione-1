#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>

int main () {
    char* MATRICE[2][2] = {{"ciao", "balena"}, {"albero", "casa"}};
    int counter[2][2] = {0};

    // printf("%s %s\n", MATRICE[0][0], MATRICE[1][0]);
    for (unsigned int i = 0; i < 2; i++) {
        for (unsigned int j = 0; j < 2; j++) {
            for (unsigned int indice = 0; *(MATRICE[i][j] + indice) != '\0' && indice < strlen(MATRICE[i][j]); indice++){
                if (*(MATRICE[i][j] + indice) == 'a' || *(MATRICE[i][j] + indice) == 'e' || *(MATRICE[i][j] + indice) == 'i' || *(MATRICE[i][j] + indice) == 'o' || *(MATRICE[i][j] + indice) == 'u') {
                    counter[i][j]++;
                }
            }
        }
    }
    printf ("%d %d  %d %d %d\n", counter[0][0], counter[0][1], counter[1][0], counter[1][1]);

    for (unsigned int k = 0; k < 2; k++) {
        for (unsigned int z = 0; z < 2; z++) {
            if (counter[z][k] == counter[z + 1][k]) {
                printf("1\n");
            }
            
            
        }
        
    }
    

    /* for (unsigned int indice = 0; *(MATRICE[0][0] + indice) != '\0' && indice < strlen(MATRICE[0][0]); indice++) {
        if (*(MATRICE[0][0] + indice) == 'a' || *(MATRICE[0][0] + indice) == 'e' || *(MATRICE[0][0] + indice) == 'i' || *(MATRICE[0][0] + indice) == 'o' || *(MATRICE[0][0] + indice) == 'u') {
                    counter++;
        }
    }
    printf ("%d\n", counter);*/
}