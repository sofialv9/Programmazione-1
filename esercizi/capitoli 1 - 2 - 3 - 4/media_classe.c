//sequenza EOF = ctrl D

#include <stdio.h>

int main () {
    unsigned int quantità_A;
    unsigned int quantità_B;
    unsigned int quantità_C;
    unsigned int quantità_D;
    unsigned int quantità_E;
    unsigned int quantità_F;
    float media;

    puts ("Inserire i voti (sequenza EOF per terminare):");
    int voto;
    

    while ((voto = getchar()) != EOF) {
        
        switch (voto) {

            case 'A':
            ++quantità_A;
            break;

            case 'B':
            ++quantità_B;
            break;

            case 'C':
            ++quantità_C;
            break;

            case 'D':
            ++quantità_D;
            break;

            case 'E':
            ++quantità_E;
            break;

            case 'F':
            ++quantità_F;
            break;

            case '\n':
            case '\t':
            case ' ':
            break;

            default:
            printf ("Inserire un voto valido.\n");
            break;
        }
    
    }
    
    media = (float) (10 * quantità_A + 9 * quantità_B + 8 * quantità_C + 7 * quantità_D + 6 * quantità_E + 5 * quantità_F) / (quantità_A + quantità_B + quantità_C + quantità_D + quantità_E + quantità_F);
    
    printf ("La media dei voti è: %.2f \n", media);

}