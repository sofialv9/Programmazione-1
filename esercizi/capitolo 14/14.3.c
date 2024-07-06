// Stampa gli argomenti di una riga di comando
// gcc 14.3.c -o 14.3 ----> /14.3 argomenti...ecc.

#include <stdio.h>

int main(int argc, char* argv[]) {
    puts("The command-line arguments are:");

    for(unsigned int i = 0; i < argc; ++i) {
        printf("%s ", argv[i]);
    }

    puts("");
}