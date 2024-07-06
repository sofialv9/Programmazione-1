// Sposta a destra una variabile intera di 4 bit.

#include <stdio.h>

void displayBits(unsigned int value);

int main() {
    printf("%s", "Enter an integer: ");
    unsigned int val;
    scanf("%u", &val);
    
    printf("%u before right shifting 4 bits is:\n", val);
    displayBits(val);

    printf("%u after right shifting 4 bits is:\n", val);
    displayBits(val >> 4);
}

void displayBits(unsigned int value) {
    unsigned int displayMask = 1 << 15; // maschera di bit

    printf("%7u = ", value);

    // iterazione attraverso i bit
    for (unsigned int c = 0; c < 16; ++c) {
        value & displayMask ? putchar('1') : putchar('0');
        value <<= 1; // sposta value di 1 bit a sinistra

        if (c % 8 == 0) {
            putchar(' ');
        }
    }
    putchar('\n');
}