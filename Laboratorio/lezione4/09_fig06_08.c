// fig06_08.c
// Treating character arrays as strings.
#include <stdio.h>
#define SIZE 20

// function main begins program execution
int main(void) {
   char s[6] = {'h','e','l','l','o','\0'}; // una stringa può essere indicata come un array di caratteri - il carattere di terminazione (di escape) indica di ignorare il resto dei caratteri (inizializzati a zero se i caratteri inizializzati sono in numero minore rispetto alla lunghezza della stringa)
   // Array: struttura dati statica - non si può cambiare la dimensione di un array / la lunghezza di una stringa dopo la sua inizializzazione
   char string1[SIZE] = "ciao"; // reserves 20 characters - il quinto carattere viene automaticamente inizializzato a carattere di terminazione
   char string1[SIZE] = {'c','i','a','o'}; // valida perchè il codice del carattere di terminazione è 0, quindi viene automaticamente aggiunto /0
   char string1[4] = {'c','i','a','o'}; // non valida - non contiene /0
   char string2[] = "string literal"; // reserves 15 characters - aggiunge automaticamente /0 come ultimo carattere

   // prompt for string from user then read it into array string1
   printf("%s", "Enter a string (no longer than 19 characters): ");
   scanf("%19s", string1); // input no more than 19 characters - non serve la &

   // output strings
   printf("string1 is: %s\nstring2 is: %s\n", string1, string2);
   puts("string1 with spaces between characters is:");     

   string1[4] = 'x' // se si inserisce "ciao" stampa "ciaox"
   string1[5] = 'x' // se si inserisce "ciao" stampa "ciao", la x non viene stampata perché inserita dopo il carattere di terminazione

   // output characters until null character is reached  
   for (size_t i = 0; i < SIZE && string1[i] != '\0'; ++i) { // se non si inserisse la seconda condizione nell'and se si inserisce una stringa di lunghezza minore rispetto a quella della stringa precedente rimangono i caratteri della stringa precedente - es. se si inserisce "d" l'struzione stamperà "d (/0) a o"
      printf("%c ", string1[i]);                            
   }                                                        

   puts("");
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

