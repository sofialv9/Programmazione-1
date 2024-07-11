// fig07_03.c
// Cube a variable using pass-by-reference with a pointer argument.
// Nel passaggio per riferimento si passa un puntatore alla funzione.
// Si usa la & nella scanf affinché l'istruzione possa sovrascrivere la variabile a quell'indirizzo

#include <stdio.h>

void cubeByReference(int *nPtr); // function prototype

int main(void) {
   int number = 5; // initialize number

   printf("The original value of number is %d", number);
   cubeByReference(&number); // pass address of number to cubeByReference
   printf("\nThe new value of number is %d\n", number);

   int number2 = 5
   printf("The original value of number is %d", number2);
   cubeByValue (number2); 
   printf("\nThe new value of number is %d\n", number2);
} 

// calculate cube of *nPtr; actually modifies number in main
void cubeByReference(int *nPtr) {                           
   *nPtr = *nPtr * *nPtr * *nPtr; // cube *nPtr             
}

void cubeByValue(int x) {                           
   x = x * x * x; // sovrascrive solo il valore della variabile locale x e non quello di number            
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

