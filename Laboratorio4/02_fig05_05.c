// fig05_05.c
// Rolling a six-sided die 60,000,000 times.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
   int frequency1 = 0; // rolled 1 counter // 10,000,000
   int frequency2 = 0; // rolled 2 counter // 10,000,000
   int frequency3 = 0; // rolled 3 counter // 10,000,000
   int frequency4 = 0; // rolled 4 counter // 10,000,000
   int frequency5 = 0; // rolled 5 counter // 10,000,000
   int frequency6 = 0; // rolled 6 counter // 10,000,000

   srand(time(NULL)); // si dà un seme da cui iniziare a campionare i numeri casuali

   int numero_iterazioni = 60000000;

   // loop 60000000 times and summarize results
   for (int roll = 1; roll <= numero_iterazioni; ++roll) {
      int face = 1 + rand() % 6; // random number from 1 to 6
      // int x = a + rand() % (b-a+1) - genera numeri da a a 

      // determine face value and increment appropriate counter
      switch (face) {
         case 1: // rolled 1
            ++frequency1;
            break;
         case 2: // rolled 2
            ++frequency2;
            break;
         case 3: // rolled 3
            ++frequency3;
            break;
         case 4: // rolled 4
            ++frequency4;
            break;
         case 5: // rolled 5
            ++frequency5;
            break;
         case 6: // rolled 6
            ++frequency6;
            break; // optional
      } 
   } 
   
   // display results in tabular format
   printf("FREQUENZE ASSOLUTE\n"); // quantità di volte in cui appare uno dei valori
   printf("%s%13s\n", "Face", "Frequency");
   printf("   1%13d\n", frequency1);
   printf("   2%13d\n", frequency2);
   printf("   3%13d\n", frequency3);
   printf("   4%13d\n", frequency4);
   printf("   5%13d\n", frequency5);
   printf("   6%13d\n", frequency6);

   printf("FREQUENZE RELATIVE\n"); // probabilità di ottenere uno dei valori in percentuale
   // display results in tabular format
   printf("%s%13s\n", "Face", "Frequency");
   printf("   1%13f\n", ((double)frequency1/numero_iterazioni)*100);
   printf("   2%13f\n", ((double)frequency2/numero_iterazioni)*100);
   printf("   3%13f\n", ((double)frequency3/numero_iterazioni)*100);
   printf("   4%13f\n", ((double)frequency4/numero_iterazioni)*100);
   printf("   5%13f\n", ((double)frequency5/numero_iterazioni)*100);
   printf("   6%13f\n", ((double)frequency6/numero_iterazioni)*100);
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


