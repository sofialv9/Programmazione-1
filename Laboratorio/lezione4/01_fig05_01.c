// fig05_01.c
// Creating and using a function.
#include <stdio.h> 

//int square(int number); // function prototype 

int square(int number) { // number is a copy of the function's argument - la variabile number ha visibilità limitata a square (esiste solo in square)
   return number * number; // returns square of number as an int        
}

int main(void) {  //main inizializza uno stack (spazio di memoria operativo della funzione) dove pone la variabile x (che occupa lo spazio necessario per un intero, cioè 32 bit)
   // loop 10 times and calculate and output square of x each time
   for (int x = 1; x <= 10; ++x) {
      printf("%d  ", square(x)); // function call - square inizializza un nuovo stack con la variabile number - viene fatto un nuovo stack ad ogni chiamata di funzione ed eliminato ad ogni return
      // f(y) = y^2
      // f : R -> R
      int y = 2; //variabile che esiste solo all'interno del blocco definito dalle parentesi
   }
   
   print("%d", y) // dà errore perché la variabile y esiste solo all'interno del for

   puts("");
} 

// square function definition returns the square of its parameter
/*int square(int number) { // number is a copy of the function's argument 
   return number * number; // returns square of number as an int        
}*/                                                                       




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

