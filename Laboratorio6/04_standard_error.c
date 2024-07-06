#include<stdio.h>

int main() {
    // Le operazioni di input/output vengono eseguite in C mediante gli stream - si comportano come dei file sequenziali
    // Sono disponibili tre stream principali:
    //  - stdin: standard input - la tastiera
    //  - stdout: standard output - lo schermo
    //  - stderr: standard error - lo schermo - questo viene usato per stampare messaggi di errori (e distinguerli dagli altri)
    // I sistemi operativi permettono in genere di "redirigere" questi stream in modo da permettere letture o scritture da file
    // lasciando il programma invariato

    // Scrittura su standard output
    // La possiamo effettuare con printf o puts
    printf("%s", "Scrivo su standard output\n");
    puts("Anche questo va su standard output");

    // Letttura da standard input
    // La possiamo effettuare con scanf
    printf("Inserisci un numero e premi invio: ");
    int x;
    scanf("%d", &x);

    // Scrittura su standard error
    // La otteniamo con fprintf che funziona come printf ma permette di specificare lo stream (il file di uscita):
    if(getchar()!='\n') // se ci sono dei caratteri diversi da newline sullo standard input, allora abbiamo inserito un numero non valido (se non seguito da \n il numero inserito non è intero)
        fprintf(stderr, "Errore, il numero inserito non è valido!\n");
    else
        fprintf(stdout, "Numero inserito valido.\n"); //questo funziona esattamente come printf dato che sto specificando sdout come stream


    // SU UNIX:
    
    // Possiamo redirigere un file sull'input così: ./programma < input (non si deve recompilare)
    // Dove input è il file di input che viene visto dal programma come standard input
    // La redirezione vine fatta dal sistema operativo, non da C
    // La redirezione a standard input è utile per il debugging

    // Possiamo redirigere lo standard output su file così: ./programma > out - stampa l'output sul file out ma stampa comunque il messaggio di errore su schermo
    // Possiamo redirigere lo standard error su file così: ./programma 2> out
    // Possiamo redirigere sia standard error che standard output su file così: ./programma &> out
    // oppure si possono redirigere stderr e stdout su 2 file diversi ./programma < input &> out.out 2> out.err

    // Possiamo redirigere sia input che standard output così: ./programma < input > out 
    // Possiamo redirigere sia input che standard e error output così: ./programma < input &> out 
}