//Calcola lo stipendio lordo di ciascun impiegato

#include <stdio.h>

int main (void)
{
    int hours_worked = 0;
    float hourly_rate = 0, salary = 0;

    printf ("Enter # of hours worked (-1 to end): ");
    scanf ("%d", &hours_worked);
    while (hours_worked != -1){
         printf ("Enter hourly rate of the worker ($00.00): ");
         scanf ("%f", &hourly_rate);
         if (hours_worked <= 40 ) {
             salary = hours_worked * hourly_rate;
             /* printf ("Salary is: $%.2f \n", salary);
             printf ("Enter # of hours worked (-1 to end): ");
             scanf ("%d", &hours_worked); */
         }
         else
         {
             salary = (40 * hourly_rate) + ((hours_worked - 40) * (hourly_rate * 3/2));
             /* printf ("Salary is: $%.2f \n", salary);
             printf ("Enter # of hours worked (-1 to end): ");
             scanf ("%d", &hours_worked); */
         }
         printf ("Salary is: $%.2f \n", salary);
         printf ("Enter # of hours worked (-1 to end): ");
         scanf ("%d", &hours_worked);
    }
   
}
