// Inverte l'ordine dei bit di un unsigned int

#include <stdio.h>

unsigned int reverseBits(unsigned int value);
void displayBits(unsigned int value);

int main() {
    printf("Enter an unsigned int: ");
    unsigned int number;
    scanf("%u", &number);

    puts("\nBefore bits are reversed:");
    displayBits(number);
    
    number = reverseBits(number);
    puts("\nAfter bits are reversed:");
    displayBits(number);
}

// la funzione reverseBits inverte i bit di value
unsigned int reverseBits(unsigned int value) {
    unsigned int mask = 1; // maschera di bit
    unsigned int temp = 0; // bit invertiti

    for (unsigned int i = 0; i < 16; ++i) {
        temp <<= 1; // sposta temp a destra di 1 bit
        temp |= (value & mask); // separa un bit e lo inserisce in temp
        value >>= 1; // sposta value a sinistra di 1 bit
    }

    return temp;
}

void displayBits(unsigned int value) {
    unsigned int displayMask = 1 << 15;

    for (unsigned int c = 0; c < 16; ++c) {
        value & displayMask ? putchar('1') : putchar('0');
        value <<= 1;

        if (c % 8 == 0) {
            putchar(' ');
        }
    }
    putchar('\n');
}
