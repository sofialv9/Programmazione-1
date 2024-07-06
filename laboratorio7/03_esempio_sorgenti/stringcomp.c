#include "stringcomp.h"
#include <stdlib.h>
#include <string.h>

// crea una stringa con un caratteri estratti casualmente dalla stringa alfabeto
char* sampleString(const char* alfabeto, short k) {
    char* s = calloc(k + 1,sizeof(char));
    int len = strlen(alfabeto);
    for (size_t i = 0; i < k; i++) {
        s[i] = alfabeto[sampleIndex(len)];
    }
    s[k] = 0; // non necessario poiché la calloc inizializza tutto a 0
    return s;
}

// campiona un indice intero tra 0 e max - 1
int sampleIndex(int max){
    return rand() % max;
}