//stampa i caratteri digitati dall'utente in ordine inverso rispetto a quello di inserimento dopo aver digitato la sequenza EOF

#include <stdio.h>

int main(void)
{
    int c; //variabile che conserva i caratteri digitati
    if ((c=getchar()) != EOF) {
        main(); //funzione ricorsiva
        printf("%c", c);
    }
}