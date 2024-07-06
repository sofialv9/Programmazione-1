//Calcolo dell'interesse composto

#include <stdio.h>
#include <math.h>

int main () {
    int principal = 100000;
    float rate = 0.05;

    printf ("%4s%21s\n", "Year", "Amount on deposit");

    for (unsigned int year = 1; year <= 10; ++year) {

        int amount = principal * pow(1 + rate, year);
        int amount_dollars = amount / 100;
        int amount_centesimi = amount % 100;
        printf ("%4u%18d.%d\n", year, amount_dollars, amount_centesimi);

    }

    
}