// fig07_14.cpp
// Using subscripting and pointer notations with arrays.
#include <stdio.h>
#define ARRAY_SIZE 4

int main(void) {
   int b[] = {10, 20, 30, 40}; // create and initialize array b
   int *bPtr = b; // create bPtr and point it to array b

   // output array b using array subscript notation
   puts("Array b printed with:\nArray subscript notation");

   // loop through array b
   for (size_t i = 0; i < ARRAY_SIZE; ++i) {
      printf("b[%zu] = %d\n", i, b[i]); // b + i * sizeof(tipo a cui punta b)
   } 

   // output array b using array name and pointer/offset notation
   puts("\nPointer/offset notation where the pointer is the array name");

   // loop through array b
   for (size_t offset = 0; offset < ARRAY_SIZE; ++offset) {
      printf("*(b + %zu) = %d\n", offset, *(b + offset)); // b[i] === *(b + 1)
   } 

   // output array b using bPtr and array subscript notation
   puts("\nPointer subscript notation");

   // loop through array b
   for (size_t i = 0; i < ARRAY_SIZE; ++i) {
      printf("bPtr[%zu] = %d\n", i, bPtr[i]);
   } 

   /* Esempio notazione con indice
   int a = 5;
   int* aPtr = &a;
   aPtr[0]; --> *aPtr
   */

   // output array b using bPtr and pointer/offset notation
   puts("\nPointer/offset notation");

   // loop through array b
   for (size_t offset = 0; offset < ARRAY_SIZE; ++offset) {
      printf("*(bPtr + %zu) = %d\n", offset, *(bPtr + offset));   
   } 

   //A multiple array can be seen as a pointer to pointers
   int A[2][3] = {{1,2,3},{4,5,6}}; // int** - matrice = array di array
   printf("A[0] is a pointer to an array of 3 elements: %p\n", A[0]); // = 1 2 3
   printf("A[1] is a pointer to another array of 3 elements: %p\n", A[1]); // = 4 5 6

   printf("*(*A+1)) == A[0][1]: %d == %d\n",*(*A+1), A[0][1]);
   printf("*(A[0]+1) == A[0][1]: %d == %d\n",*(A[0]+1), A[0][1]);
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

