#include<stdio.h>
#define NUM 4
#define NUM2 3>5

int main() {
    // una costante macro (definita sopra) - NUM non occupa spazio in memoria
    // il preprocessore sostituisce NUM con 4
    // prima della compilazione
    printf("%d\n", NUM);

    // una costante letterale, ovvero un numero - occupa uno spazio in memoria
    // inserito direttamente nel codice del programma - non utile se poi si vuole cambiare la costante
    printf("%d\n", 4);

    // esempio in cui l'uso di macro per definire costanti
    // può creare confusione
    printf("%d\n", NUM2);

    // esempio di variabili definite come costanti - occupano spazio in memoria
    // mediante il modificatore const - non si può accedere in scrittura, solo in lettura (il valore delle variabili non può essere cambiato)
    const float pi = 3.14;
    const int x = 0;

    printf("%f\n%d\n", pi, x);

    // Le seguenti due istruzioni danno errori di compilazione (se non commentate)
    //const double y; //non si può dichiarare una costante senza inizializzarla
    //y = 2.5; //non si può assegnare un valore a una costante
}
