// fig08_05.c
// Using function strtol
#include <stdio.h>
#include <stdlib.h>

int main(void) {
   const char *string = "-1234567abc123"; // la stringa da convertire in long - const indica che il valore della stringa non può essere modificato
   char *remainderPtr = NULL; // punterà alla stringa contenente la parte che non può essere convertita
   
   // La funzione strol converte una stringa in un long
   // va notato che solo parte della stringa è convertibile
   // in un long. La restante parte della stringa verrà
   // inserita in una nuova stringa e fatta puntare dal puntatore passato
   long x = strtol(string, &remainderPtr, 0); // 0 indica la base (0 indica la base decimale) - viene passato l'indirizzo del puntatore (quindi un puntatore a puntatore) perché la funzione possa modificarlo - conterrà l'indirizzo di memoria del carattere non convertibile 'a'

   printf("Differenza remainderPtr - string: %lu\n", remainderPtr - string); // restituisce la posizione del primo carattere non valido (cioè 'a') all'interno della stringa (cioè la posizione 8)

    // stampiamo i valori che abbiamo ottenuto
   printf("%s\"%s\"\n%s%ld\n%s\"%s\"\n%s%ld\n",
      "The original string is ", string,
      "The converted value is ", x, //-1234567
      "The remainder of the original string is ", remainderPtr, //abc123
      "The converted value plus 567 is ", x + 567);

    // Analogamente, possiamo convertire una stringa in double come segue
    const char *string2 = "51.2% are admitted";
    char *stringPtr2 = NULL; 
    
    double d = strtod(string2, &stringPtr2);
    
    printf("\nThe string \"%s\" is converted to the\n", string2); //51.2
    printf("double value %.2f and the string \"%s\"\n", d, stringPtr2); //% are admitted

    const char *string3 = "13";
    char *stringPtr3 = NULL;

    long l = strtol (string3, &stringPtr3, 0);

    printf("\nThe string \"%s\" is converted to the\n", string3);
    printf("long value %ld and the string \"%s\"\n", l, stringPtr3); // in stringPtr3 mette sempre il puntatore al prossimo carattere (in questo caso il carattere di terminazione)

   // Controlla se il numero inserito è valido
    if (*stringPtr3 == 0) { // dereferenzio il puntatore che punta al carattere successivo e stampo che l'intero è valido se il carattere è quello di terminazione
      puts("L'intero è valido");
    } else {
      puts ("L'intero non è valido");
    }

    
} 

/**************************************************************************
 * (C) Copyright 1992-2021 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/