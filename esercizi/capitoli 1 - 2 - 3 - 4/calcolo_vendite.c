#include <stdio.h>

int main () {

    int prodotto = 0;
    int quantità = 0;
    int counter = 0;
    float prezzo = 0;
    float totale = 0;
    float totale_giornaliero = 0;
    float totale_settimanale = 0;

    

    while (++counter <=5) {
        
        printf ("Inserire il numero del prodotto: ");
        scanf ("%d", &prodotto);

        switch (prodotto) {
            case 1:
            prezzo = 2.98;
            break;

            case 2:
            prezzo = 4.50;
            break;

            case 3:
            prezzo = 9.98;
            break;
        
            case 4:
            prezzo = 4.49;
            break;

            case 5:
            prezzo = 6.87;
            break;
        
            default:
            printf ("Inserire un numero valido: ");
            scanf ("%d", &prodotto);
            break;
        }
        
        printf ("Inserire la quantità di vendite giornaliere: ");
        scanf ("%d", &quantità);

        totale = quantità * prezzo;
        totale_giornaliero += totale;

    }

    totale_settimanale = totale_giornaliero * 7;
    printf ("Il totale settimanale è: %.2f \n", totale_settimanale);

}