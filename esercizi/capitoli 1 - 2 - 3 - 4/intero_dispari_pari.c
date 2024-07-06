//Legge un intero e stabilisce se è dispari o pari

#include <stdio.h>

int main (void)
{
    printf("Enter an integer: \n");
    int x;
    scanf("%d", &x);
    if (x%2==0) printf("%d è pari \n", x);
    else printf("%d è dispari \n",x);
}