// Spacchetta un valore unsigned int in 4 caratteri

#include <stdio.h>

unsigned int unpackCharacters(char* aPtr, char* bPtr, unsigned int pack);
void displayBits(unsigned int value);

int main() {
    unsigned int packed = 16706;
    puts("The packed character representation is:");
    displayBits(packed);
    
    // spacchetta packed e stampa i risultati
    char a;
    char b;
    unpackCharacters(&a, &b, packed);
    printf("\nThe unpacked characters are \'%c\' and \'%c\'\n", a, b);
    displayBits(a);
    displayBits(b);
}

// spacchetta 2 caratteri da packed
unsigned int unpackCharacters(char* aPtr, char* bPtr, unsigned int pack) {
    unsigned int mask1 = 65280; // maschera per il 1° carattere (11111111 00000000)
    unsigned int mask2 = 255; // maschera per il 2° carattere (00000000 11111111)

    *aPtr = (pack & mask1) >> 8; // separa il 1° carattere
    *bPtr = (pack & mask2); // separa il 2° carattere
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