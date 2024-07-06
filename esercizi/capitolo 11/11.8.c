/*PROBLEMI:
    1 - Premendo CTRL-D come input dello scanf presente nella condizione del primo ciclo while viene     terminato l'intero programma e non solo l'input del 1° ciclo (vengono stampate le due righe relative al secondo file (puts e printf dopo il 1° fclose) ma non si entra mai nel secondo ciclo);
    2 - Il simbolo di percentuale prima del gruppo di scansione nella stringa di controllo del formato del 1° scanf è colorato di rosso come se vi fosse un errore.
*/

#include <stdio.h>

int main() {
    FILE *ofPtr = fopen("oldmast.dat", "w"); // puntatore al vecchio file principale
    FILE *tfPtr = fopen("trans.dat", "w"); // puntatore al file delle transazioni
    
    puts("Sample data for file oldmast.dat: ");
    printf("%s", "Enter account, name and balance (EOF to end): ");

    unsigned int account; // numero di conto
    char name[30]; // nome del conto
    double balance; // saldo del conto
    double amount; // ammontare della transazione
    int result;

    // qui segna il secondo % in rosso
    while (scanf("%d%[^0123456789-]%lf", &account, name, &balance) != EOF) {
        // scrive i dati sul vecchio file principale
        fprintf(ofPtr, "%d %s %.2f", account, name, balance);
        printf("%s", "Enter account, name and balance (EOF to end): ");
    }

    fclose(ofPtr); // chiude il puntatore al file
    
    // stampa queste due frasi ma non entra mai nel while
    puts("\nSample data for file trans.dat:");
    printf("%s", "Enter account and transation amount (EOF to end): ");

    while (scanf("%d%lf", &account, &amount) != EOF) {
        int counter = 1;
        // scrive i dati sul file delle transazioni
        fprintf(tfPtr, "%d %.2f", account, amount);
        printf("%s", "Enter account and transation amount (EOF to end): ");
    }

    fclose(tfPtr);
}