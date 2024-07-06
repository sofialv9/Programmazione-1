#include <stdio.h>

void wordGenerator(unsigned int number[]);

int main() {
    printf("%s", "Enter a phone number one digit at a time using the digits 2 thru 9: \n");
    unsigned int phoneNumber[7] = {0};

    for (unsigned int loop = 0; loop < 7; ++loop) {
        printf("%s", "? ");
        scanf("%d", &phoneNumber[loop]);
        
        // verifica se la cifra inserita è compreso tra 2 e 9 (estremi compresi)
        while (phoneNumber[loop] < 2 || phoneNumber[loop] > 9) {
            printf("%s", "\nInvalid number entered. Please try again:");
            scanf("%d", &phoneNumber[loop]);
        }
    }
    
    // forma parole partendo dal numero telefonico
    wordGenerator(phoneNumber);
}

void wordGenerator(unsigned int number[]) {

    // lettere corrispondenti a ciascun numero (le stringhe relative a 0 e 1 sono vuote)
    char* phoneLetters[10] = {"", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PRS", "TUV", "WXY"};

    // apre il file di output
    FILE *foutPtr;
    if ((foutPtr = fopen("phone.out", "w")) == NULL) {
        puts("Output file was not opened.");
    }
    else { // stampa tutte le combinazioni possibili
        for (unsigned int loop1 = 0; loop1 < 3; ++loop1) {
            for (unsigned int loop2 = 0; loop2 < 3; ++loop2) {
                for (unsigned int loop3 = 0; loop3 < 3; ++loop3) {
                    for (unsigned int loop4 = 0; loop4 < 3; ++loop4) {
                        for (unsigned int loop5 = 0; loop5 < 3; ++loop5) {
                            for (unsigned int loop6 = 0; loop6 < 3; ++loop6) {
                                for (unsigned int loop7 = 0; loop7 < 3; ++loop7) {
                                    fprintf(foutPtr, "%c%c%c%c%c%c%c\n",
                                    phoneLetters[number[0]][loop1], // seleziona a turno ognuna delle 3 lettere presenti nel gruppo la cui posizione è ndicata dalla cifra selezionata dal numero di telefono
                                    phoneLetters[number[1]][loop2],
                                    phoneLetters[number[2]][loop3],
                                    phoneLetters[number[3]][loop4],
                                    phoneLetters[number[4]][loop5],
                                    phoneLetters[number[5]][loop6],
                                    phoneLetters[number[6]][loop7]);
                                }
                            }
                        }
                    }
                }
            }
        }

        // stampa il numero di telefono
        fputs("\nPhone number is: ", foutPtr);

        for (unsigned int loop = 0; loop < 7; ++loop){
            // separa le prime 3 cifre con un trattino
            if (loop == 3) {
                fprintf(foutPtr, "-");
            }
        fprintf(foutPtr, "%d", number[loop]);
        }
    }
    
    fclose(foutPtr); // chiude il file di output
    
}