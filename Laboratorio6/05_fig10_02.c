// fig10_02.c
// Card shuffling and dealing program using structures - strutture dati statiche
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CARDS 52
#define FACES 13

// card structure definition                  
struct card {
   // Puntatori costanti
   // Posso farli puntare a delle stringhe
   // Ma non posso cambiare il caratteri delle stringhe                                 
   const char *face; // define pointer face   
   const char *suit; // define pointer suit   
};

struct card c = {NULL, NULL}; // STATICA - le variabili possono essere inizializzate nello stesso ordine in cui compaiono nella definizione della struct

// Crea un alias della struct card (un nuovo nome per un tipo esistente) che si chiama "Card" per semplificare la notazione
typedef struct card Card; // new type name for struct card 

Card c2 = {NULL, NULL}; // STATICA

// In alternativa possiamo combinare la definizione della struct e typedef così:
// typedef struct {
//    // Puntatori costanti
//    // Posso farli puntare a delle stringhe
//    // Ma non posso cambiare il caratteri delle stringhe                                 
//    const char *face; // define pointer face   
//    const char *suit; // define pointer suit   
// } Card; - l'alias è posto prima del punto e virgola finale

// prototypes
void fillDeck(Card * const deck, const char *faces[], const char *suits[]);
void shuffle(Card * const deck);
void deal(const Card * const deck);

int main(void) {
   Card deck[CARDS]; // define array of Cards
   // Alternativamente (se non usiamo typedef)
   //struct card deck[CARDS]; // define array of Cards

   // initialize faces array of pointers
   const char *faces[] = { "Ace", "Deuce", "Three", "Four", "Five",
      "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

   // initialize suits array of pointers
   const char *suits[] = { "Hearts", "Diamonds", "Clubs", "Spades"};

   srand(time(NULL)); // randomize

   fillDeck(deck, faces, suits); // load the deck with Cards
   shuffle(deck); // put Cards in random order
   deal(deck); // deal all 52 Cards
}

// place strings into Card structures
void fillDeck(Card * const deck, const char * faces[], 
   const char * suits[]) {
   // loop through deck
   for (size_t i = 0; i < CARDS; ++i) { 
      deck[i].face = faces[i % FACES]; // itera tra le facce ricominciando quando finiscono - da 0 a 12 (dal'asso al re)
      deck[i].suit = suits[i / FACES]; // mediante la divisione intera produce numeri del tipo 0 0 0 0 ... 1 1 1 1 ... 2 2 2 2 - da 13 volte 0 (cuori) a 13 volte 3 (spade)
   }
}

// shuffle cards
void shuffle(Card * const deck) {
   // loop through deck randomly swapping Cards
   for (size_t i = 0; i < CARDS; ++i) { 
      size_t j = rand() % CARDS; // genera un indice casuale da 0 a 51
      Card temp = deck[i]; // temp = variabile temporanea di tipo Card - locazione automatica (la Card temp viene deallocata all'uscita dal for) - l'uguale effettua una copia del valore
      deck[i] = deck[j];  
      deck[j] = temp;     
   }
}

// deal cards
void deal(const Card * const deck) {
   // loop through deck
   for (size_t i = 0; i < CARDS; ++i) {
      printf("%5s of %-8s%s", deck[i].face, deck[i].suit, // stampa (il meno serve per l'allineamento a sinistra)
         ((i + 1) % 4) == 0 ? "\n" : " "); // va a capo ogni quattro colonne

   }
}


/**************************************************************************
 * (C) Copyright 1992-2021 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/
