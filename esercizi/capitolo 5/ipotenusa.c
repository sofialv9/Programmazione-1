#include <stdio.h>
#include <math.h>

double hypotenuse (double a, double b);

int main ()
{
    double x, y;
    printf("Inserire la lunghezza del primo cateto: ");
    scanf("%lf", &x);
    printf("Inserire la lunghezza del secondo cateto: ");
    scanf("%lf", &y);
    printf("La lunghezza dell'ipotenusa è: %.2f\n", hypotenuse (x, y));
}

double hypotenuse (double a, double b)
{
    return sqrt (pow (a, 2) + pow (b, 2));
}