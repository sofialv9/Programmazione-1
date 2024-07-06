#include <stdio.h>
int integerPower (int base, unsigned int exponent);

int main ()
{
    int x;
    unsigned int y;
    printf("Inserire la base: ");
    scanf("%d", &x);
    printf("Inserire l'esponente: ");
    scanf("%u", &y);
    printf("La base elevata all'esponente è: %d\n", integerPower(x, y));
}

int integerPower (int base, unsigned int exponent)
{
    int y = base;
    for (unsigned int i = 1; i < exponent; i++)
    {
        base = y * base;
    }
    return base;
}