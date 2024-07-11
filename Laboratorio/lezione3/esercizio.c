//esercizio 4.28 del libro

#include <stdio.h>

int main () {
    int code = 0;
    double retribuzione = 0;
    int settimane = 0;
    double paga_fissa = 0;
    double paga = 0;
    int ore = 0;
    int vendite = 0;
    int articoli = 0;
    double denaro = 0;

    do {
        printf ("Inserisci il codice lavoratore (-1 per terminare): ");
        scanf ("%d", &code);

        switch (code) {
            case 1: //manager
               printf ("Inserire la retribuzione fissa settimanale: ");
               scanf ("%lf", &retribuzione);
               printf ("Inserire il numero di settimane lavorate: ");
               scanf ("%d", &settimane);
               printf ("La paga è: %0.2f \n", retribuzione * settimane);
               break;
            case 2: //lavoratori a ore
               printf ("Inserire la paga fissa all'ora: ");
               scanf ("%lf", &paga_fissa);
               printf ("Inserire il numero di ore lavorative: ");
               scanf ("%d", &ore);
               if (ore <= 40)
               {
                paga = paga_fissa * 40;
               }
               else
               {
                paga = (paga_fissa * 40) + ((1.5 * paga_fissa) * (ore - 40));
               }
               printf ("La paga è: %0.2f\n", paga);
               break;

            case 3: //lavoratori con provvigione
               printf ("Inserire le vendite settimanali lorde: ");
               scanf ("%d", &vendite);
               paga = 250 + vendite * (5.7 / 100);
               printf ("La paga è: %0.2f\n", paga);
               break;

            case 4: //lavoratori a cottimo
               printf ("Inserire quantità di denaro per articolo: ");
               scanf ("%lf", &denaro);
               printf ("Inserire quantità di articoli prodotti: ");
               scanf ("%d", &articoli);
               paga = denaro * articoli;
               printf ("La paga è: %0.2f\n", paga);
               break;
            
            case -1:
               break;

            default:
               printf ("Inserisci un codice valido nel range [1,4] \n");
               break;
        }

    } while (code != -1);
}