//stampa i numeri contenuti nell'array in ordine inverso rispetto a quello della definizione (con indici in ordine decrescente) - 5 4 7 9 0 6 2 1 3 8

#include <stdio.h>
#define SIZE 10

void someFunction(const int b[], size_t startIndex, size_t size);

int main (void)
{
    int a[SIZE] = {8,3,1,2,6,0,9,7,4,5};

    puts ("Answer is:");
    someFunction(a, 0, SIZE);
    puts ("");
}

void someFunction(const int b[], size_t startIndex, size_t size)
{
    if (startIndex < size) {
        someFunction(b, startIndex + 1, size);
        printf ("%d ", b[startIndex]);
    }
}