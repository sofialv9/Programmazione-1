//approssima un numero per difetto

#include <stdio.h>
#include <math.h>

int main ()
{
    float x;
    int y;
    printf("Inserire un numero da approssimare: ");
    scanf ("%f", &x);
    while (x != -1) {
        y = floor(x + .5);
        printf ("Il valore originario era: %.2f\n", x);
        printf ("Il valore approssimato è: %d\n", y);
        printf("Inserire un numero da approssimare: ");
        scanf ("%f", &x);
    }
}