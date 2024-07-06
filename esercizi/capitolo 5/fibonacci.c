//Esercizio 5.35

#include <stdio.h>

int main ()
{
    unsigned long long int fibonacci (unsigned int x1, unsigned int x2, unsigned long long int x3);
    unsigned int x1 = 0;
    unsigned int x2 = 1;
    unsigned long long int x3 = 0;
    fibonacci(x1,x2,x3);

}

unsigned long long int fibonacci (unsigned int x, unsigned int y, unsigned long long int z)
{
    printf("%u\n%u\n", x, y);
    for (unsigned int i = 2; ; i++) {
        z = x + y;
        printf("%llu\n", z);
        x = y;
        y = z;
    }
}