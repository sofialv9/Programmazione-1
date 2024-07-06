// Spostare a sinistra un unsigned int di 1 bit è equivalente a moltiplicare il valore per 2

#include <stdio.h>

void displayBits(unsigned int value);
unsigned int power2(unsigned int n, unsigned int p);

int main() {
    unsigned int number;
    unsigned int pow; // numero di bit da spostare a sinistra

    printf("%s", "Enter two integers: ");
    scanf("%u%u", &number, &pow);

    puts("number: ");
    displayBits(number);

    puts("\npow: ");
    displayBits(pow);
    
    unsigned int result = 0;
    result = power2(number, pow);
    printf("\n%u * 2^%u = %u\n", number, pow, result);
    displayBits(result);
}

// la funzione power2 sposta a sinistra n di p bit
unsigned int power2(unsigned int n, unsigned int p) {
    return n << p;
}

void displayBits(unsigned int value) {
    unsigned int displayMask = 1 << 15;

    printf("%7u = ", value);

    for (unsigned int c = 0; c < 16; ++c) {
        value & displayMask ? putchar('1') : putchar('0');
        value <<= 1;

        if (c % 8 == 0) {
            putchar(' ');
        }
    }
    putchar('\n');
}