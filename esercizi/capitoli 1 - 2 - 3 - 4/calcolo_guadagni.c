//Legge le vendite lorde di ogni addetto alle vendite di una compagnia chimica nell'ultima settimana e calcola i guadagni di quell'addetto

#include <stdio.h>

int main (void)
{
    float sales, salary;
    printf ("Enter sales in dollars (-1 to end): ");
    scanf ("%f", &sales);
    while (sales != -1) {
        salary = 200 + (sales * 9 /100);
        printf ("Salary is: $%.2f \n", salary);
        printf ("Enter sales in dollars (-1 to end): ");
        scanf ("%f", &sales);
    }
}