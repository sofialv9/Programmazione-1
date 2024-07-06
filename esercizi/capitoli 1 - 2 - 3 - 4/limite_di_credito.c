//Determina se un cliente di un grande magazzino ha superato il limite di credito sul suo conto di addebito

#include <stdio.h>

int main (void)
{
    int account_number;
    float beginning_balance;
    float total_charges;
    float total_credits;
    float credit_limit;
    float end_balance;

    printf ("Enter account number (-1 to end): ");
    scanf ("%d", &account_number);
    while (account_number != -1) {
        printf ("Enter beginning balance: ");
        scanf ("%f", &beginning_balance);
        printf ("Enter total charges: ");
        scanf ("%f", &total_charges);
        printf ("Enter total credits: ");
        scanf ("%f", &total_credits);
        printf ("Enter credit limit: ");
        scanf ("%f", &credit_limit);
        end_balance = beginning_balance + total_charges - total_credits;
        if (end_balance> credit_limit) {
            printf ("Account: %d \n", account_number);
            printf ("Credit limit: %.2f \n", credit_limit);
            printf ("Balance: %.2f \n", end_balance);
            printf ("%s", "Credit Limit Exceeded \n");
        }
        
        printf ("Enter account number (-1 to end): ");
        scanf ("%d", &account_number);

    }

}