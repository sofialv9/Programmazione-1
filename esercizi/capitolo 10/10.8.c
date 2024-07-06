#include <stdio.h>
#include <stdlib.h>

union integer {
    char c;
    short s;
    int i;
    long b;
};

int main() {
    union integer a;

    printf("%s", "Enter a character:");
    a.c = getchar();

    printf("'%c' printed as a character is %c\n", a.c, a.c);
    printf("'%c' printed as a short integer is %hd\n", a.c, a.s);
    printf("'%c' printed as an integer is %d\n", a.c, a.i);
    printf("'%c' printed as a long integer is %ld\n", a.c, a.b);
}