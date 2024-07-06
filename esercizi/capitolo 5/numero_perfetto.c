#include <stdio.h>

//Esercizio 

int main (){
    int numero_perfetto (int n);
    
    for (int n = 1; n <= 1000; n++) {
        if (numero_perfetto (n) == 1) {
            printf("%d è un numero perfetto!\n", n);
        }
        else {
            // printf("%d non è un numero perfetto.\n", n);
        }
    }
}

int numero_perfetto (int n)
{
    int sum = 0;
    for (unsigned int i = 1; i < n && i != n; i++) {
        if ((n % i) == 0){
            sum += i;
        }
        if (i == (n - 1) && sum == n) {
            return 1;
        }
    }
    
}