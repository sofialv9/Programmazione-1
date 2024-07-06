// esercizio 5.27

#include <stdio.h>
#include <math.h>

int main()
{
    unsigned int primo (unsigned int n);
    for (unsigned int n = 1; n <= 10000; n++)
    {
        if (primo (n) == 1)
        printf ("%d è un numero primo\n", n);
        
    }
    
}

unsigned int primo (unsigned int n)
{
    for (unsigned int d = 2; d < sqrt(n); d++) {
            if (n % d == 0) {
                return 0;
            }
    }
    return 1;
}