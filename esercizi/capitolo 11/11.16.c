#include <stdio.h>

int main() {
    // apri il file datasize.dat per la scrittura
    FILE* outPtr = fopen("datasize.dat", "w");
    
    fprintf(outPtr, "%s%17s\n", "Datatype", "Size");
    fprintf(outPtr, "%s%21ld\n", "char", sizeof(char));
    fprintf(outPtr, "%s%12ld\n", "unsigned char", sizeof(unsigned char));
    fprintf(outPtr, "%s%16ld\n", "short int", sizeof(short int));
    fprintf(outPtr, "%s%7ld\n", "unsigned short int", sizeof(unsigned short int));
    fprintf(outPtr, "%s%22ld\n", "int", sizeof(int));
    fprintf(outPtr, "%s%13ld\n", "unsigned int", sizeof(unsigned int));
    fprintf(outPtr, "%s%17ld\n", "long int", sizeof(long int));
    fprintf(outPtr, "%s%8ld\n", "unsigned long int", sizeof(unsigned long int));
    fprintf(outPtr, "%s%20ld\n", "float", sizeof(float));
    fprintf(outPtr, "%s%19ld\n", "double", sizeof(double));
    fprintf(outPtr, "%s%14ld\n", "long double", sizeof(long double));

    fclose(outPtr);
}