// Impacchetta 4 valori di tipo carattere in una variabile unsigned int di 4 byte

#include <stdio.h>

unsigned int packCharacters(char x, char y);
void displayBits(unsigned int value);

int main() {
    char a, b, c, d;

    printf("Enter 2 characters: ");
    scanf("%c %c", &a, &b);

    printf("\'%c\' in bits as an unsigned int is:\n", a);
    displayBits(a);
    printf("\'%c\' in bits as an unsigned int is:\n", b);
    displayBits(b);

    unsigned int result = packCharacters(a, b);

    printf("\n\'%c\' and \'%c\' packed in an unsigned int:\n", a, b);
    displayBits(result);
}

// la funzione packCharacters impacchetta 2 caratteri in un unsigned int
unsigned int packCharacters(char x, char y) {
    unsigned int pack = x; // inizializza pack a x (1° valore)
    pack <<= 8; // sposta pack di 8 bit a sinistra
    pack |= y; // impacchetta y usando l'operatore OR inclusivo
    return pack;
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