#include <stdio.h>

int main() {
    FILE* ofPtr; // puntatore al vecchio file principale
    FILE* tfPtr; // puntatore al file delle transazioni
    FILE* nfPtr; // puntatore al nuovo file principale

    // termina l'applicazione se uno dei file non può essere aperto
    if ((ofPtr = fopen("oldmast.dat", "r")) == NULL || (tfPtr = fopen("trans.dat", "r")) == NULL || (nfPtr = fopen("newmast.dat", "r")) == NULL) {
        puts("Unable to open one of the files.");
    }
    
    // stampa il conto elaborato correntemente
    puts("Processing...");
    unsigned int transactionAccount; // conto del file delle transazioni
    double transactionBalance; // saldo del file delle transazioni
    fscanf(tfPtr, "%d%lf", &transactionAccount, &transactionBalance);

    unsigned int masterAccount; // conto del vecchio file principale
    char masterName[30]; // nome conto del vecchio file principale
    double masterBalance; // saldo conto del vecchio file principale

    // fino alla fine del file delle transazioni
    while(!feof(tfPtr)) {
        // leggi il record successivo del vecchio file principale
        fscanf(ofPtr, "%d%[^0-9-]%lf", &masterAccount, masterName, &masterBalance);
        
        // stampa i conti del file principale fino a raggiungere il nuovo conto
        while (masterAccount < transactionAccount && !feof(ofPtr)) {
            fprintf(nfPtr, "%d %s %.2f\n", masterAccount, masterName, masterBalance);
            printf("%d %s %.2f\n", masterAccount, masterName, masterBalance);

            fscanf(ofPtr, "%d%[^0-9-]%lf", &masterAccount, masterName, &masterBalance);
        }
        
        // se viene trovato un conto corrispondente, aggiorna il saldo e stampa le informazioni sul conto
        if(masterAccount == transactionAccount) {
            masterBalance += transactionBalance;
            fprintf(nfPtr, "%d %s %.2f\n", masterAccount, masterName, masterBalance);
            printf("%d %s %.2f\n", masterAccount, masterName, masterBalance);
        }
        
        // comunica all'utente se il conto del file delle transazioni non corrisponde al conto del file principale
        else if(masterAccount > transactionAccount) {
            printf("Unmatched transaction record for account %d\n", transactionAccount);
            fprintf(nfPtr, "%d %s %.2f\n", masterAccount, masterName, masterBalance);
            printf("%d %s %.2f\n", masterAccount, masterName, masterBalance);
        }

        else{
            printf("Unmatched transaction record for account %d\n", transactionAccount);
        }

        fscanf(tfPtr, "%d%lf", &transactionAccount, &transactionBalance);
    }
    
    // effettua un ciclo lungo il file e stampa il numero di conto, il nome e il saldo
    while(!feof(ofPtr)) {
        fscanf(ofPtr, "%d%[^0-9-]%lf", &masterAccount, masterName, &masterBalance);
        fprintf(nfPtr, "%d %s %.2f\n", masterAccount, masterName, masterBalance);
        printf("%d %s %.2f\n", masterAccount, masterName, masterBalance);
    }
    
    // chiude tutti i puntatori a file
    fclose(ofPtr);
    fclose(tfPtr);
    fclose(nfPtr);

}