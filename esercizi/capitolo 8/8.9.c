// Confronta 2 stringhe

#include <stdio.h>
#include <string.h>

int main () {
    printf("%s", "Enter two strings: ");
    char string1[20];
    char string2[20];
    scanf("%19s%19s", string1, string2);
    
    int result = 0;
    result = strcmp(string1, string2);

    if (result > 0) {
        printf("%s is greater than %s\n", string1, string2);
    }
    else if (0 == result) {
        printf("%s is equal to %s\n", string1, string2);
    }
    else {
        printf("%s is minor than %s\n", string1, string2);
    }
}