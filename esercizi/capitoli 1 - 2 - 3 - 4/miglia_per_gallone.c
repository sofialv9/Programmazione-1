//Calcola e stampa le miglia per gallone percorse per ogni pieno

#include <stdio.h>

int main (void)
{
    unsigned int counter = 0;

    float gallons;
    float miles;
    float average;
    float total_miles = 0;
    float total_gallons = 0;
    float overall_average;
    
    printf ("%s", "Enter the gallons used (-1 to end): ");
    scanf ("%f", &gallons);

    while (gallons != -1) {
        printf ("%s", "Enter the miles driven: ");
        scanf ("%f", &miles);
        average = (float) miles / gallons;
        printf ("The miles/gallon for this tank was %f \n", average);
        counter++;
        total_miles += miles;
        total_gallons += gallons;
        printf ("%s", "Enter the gallons used (-1 to end): ");
        scanf ("%f", &gallons);
    }
    
    if (counter != 0) {
        overall_average = (float) total_miles/total_gallons;
        printf ("The overall average miles/gallon was %f \n", overall_average);
    }
    
}