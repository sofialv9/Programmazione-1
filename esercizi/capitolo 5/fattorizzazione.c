#include <stdio.h>

int main()
{
    int n = 0;

    printf("Inserire il numero da scomporre in fattori: ");
    scanf("%d", &n);

    int j = 2;
    while (n > 1) {
        if (n % j == 0) {
            n /= j;
            printf (" %d *", j);
        }
        else {
            j++;
        }
    }
    printf(" 1\n");
    
}