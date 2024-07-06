#include <stdio.h>
#include <stdlib.h>

int main () {
    char string[80];
    double sum = 0;

    for (unsigned int i = 0; i < 4; i++) {
        printf("%s", "Enter a floating poing string: ");
        fgets(string, 15, stdin);
        sum += strtod(string, 0);
    }

    printf("The total of the values is %.2f\n", sum);
}