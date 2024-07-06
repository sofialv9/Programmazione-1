// Calcola il prodotto di tre interi
#include <stdio.h>

int main (void)
{
  printf ("Enter three integers: \n");
  int x,y,z;
  scanf ("%d%d%d", &x,&y,&z);
  int result = x*y*z;
  printf ("The product is: %d\n", result);
}