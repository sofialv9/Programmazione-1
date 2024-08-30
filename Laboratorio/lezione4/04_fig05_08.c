// fig05_08.c
// Scoping.
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void useLocal(void); // function prototype
void useStaticLocal(void); // function prototype
void useGlobal(void); // function prototype
int count(void);

int x = 1; // global variable - vale in tutto il programma, cioè in tutti i blocchi di codice - viene inizializzata al di fuori del main - allocata in un parte della memoria detta 

int main(void) {
   int x = 5; // local variable to main - locazione automatica nello stack - si perde l'accesso alla x esterna - le varie x si trovano in stack (locazioni di memoria) diversi

   printf("local x in outer scope of main is %d\n", x); // 5

   { // start new scope                                    
      int x = 7; // local variable to new scope - nasconde il valore di x definito nel main
      int y = 2;           
                                                           
      printf("local x in inner scope of main is %d\n", x); // 7
   } // end new scope - la variabile locale x = 7 viene deallocata

   //printf("%d", y); //restituisce un errore

   printf("local x in outer scope of main is %d\n", x); // 5

   useLocal(); // useLocal has automatic local x // 25, 26
   useStaticLocal(); // useStaticLocal has static local x // 50, 51
   useGlobal(); // useGlobal uses global x // 1, 10
   useLocal(); // useLocal reinitializes automatic local x //25, 26
   useStaticLocal(); // static local x retains its prior value // 51, 52
   useGlobal(); // global x also retains its value // 10, 100

   printf("\nlocal x in main is %d\n", x); //5


//stampa numeri casuali da 0 a 9 finché non si stampa un numero maggiore di 5
   srand(time(NULL));
   bool cond = true;
   while(cond) {
      int x = rand()%10;
      if(x>5)
         cond = false;
      count();
   }

   printf("Count: %d\n", count()); // ritorna il valore del numero di iterazioni
} 

int count(void) { // funzione stateful - stabilisce un contatore
   static int x = 0;
   x++;
   return x;
}

// useLocal reinitializes local variable x during each call
void useLocal(void) {
   int x = 25; // initialized each time useLocal is called

   printf("\nlocal x in useLocal is %d after entering useLocal\n", x);
   ++x;
   printf("local x in useLocal is %d before exiting useLocal\n", x);
} 

// useStaticLocal initializes static local variable x only the first time 
// the function is called; value of x is saved between calls to this
// function
void useStaticLocal(void) {
   static int x = 50; // initialized once - variabile statica: ha una visibilità limitata alla funzione ma in ogni esecuzione mantiene il valore assunto alla fine della precedente esecuzione (non viene reinizializzata)

   printf("\nlocal static x is %d on entering useStaticLocal\n", x); //50
   ++x;
   printf("local static x is %d on exiting useStaticLocal\n", x); //
   // alla prossima esecuzione x = 51, quindi la funzione stampa 51,52
} 

// function useGlobal modifies global variable x during each call
void useGlobal(void) {
   printf("\nglobal x is %d on entering useGlobal\n", x); // 1
   x *= 10; 
   printf("global x is %d on exiting useGlobal\n", x); //10
   // alla seconda esecuzione stampa 10,100
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
