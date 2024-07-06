#include <stdio.h>
#include <math.h>

//prototipi di funzioni
int roundToInteger (float x);
float roundToTenths (float x);
float roundToHundreths (float x);
float roundToThousands (float x);

float y; // variabile globale

int main ()
{
    float num;
    printf ("Inserire il numero da arrotondare: ");
    scanf ("%f", &num);
    printf ("Il valore originario era: %f\n", num);
    printf("Il numero arrotodato all'intero più vicino è: %d\n", roundToInteger(num));
    printf("Il numero arrotodato alla posizione dei decimi è: %.1f\n", roundToTenths(num));
    printf("Il numero arrotodato alla posizione dei centesimi è: %.2f\n", roundToHundreths(num));
    printf("Il numero arrotodato alla posizione delle migliaia è: %.3f\n", roundToThousands(num));
}

int roundToInteger (float x) {
    y = floor(x + .5);
    return y;
}
float roundToTenths (float x) {
    y = floor(x * 10 + .5)/10;
    return y;
}
float roundToHundreths (float x) {
    y = floor(x * 100 + .5)/100;
    return y;
}
float roundToThousands (float x) {
    y = floor(x * 1000 + .5)/1000;
    return y;
}