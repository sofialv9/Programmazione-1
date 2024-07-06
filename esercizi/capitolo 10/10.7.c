// Crea, mescola e distribuisce un mazzo di carte

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CARDS 52

// definizione della struttura bitCard
struct bitCard {
    unsigned int face: 4; // servono 4 bit per rappresentare i numeri da 0 a 15
    unsigned int suit: 2; // 2 bit per i numeri 0-4
    unsigned int color: 1; // 1 bit per 0-1
};

// nuovo nome di tipo Card
typedef struct bitCard Card;

void fillDeck(Card *wDeck);
void shuffle(Card *wDeck);
void deal(Card *wDeck);

int main () {
    srand(time(NULL));
    Card deck[CARDS]; // crea un array di strutture di tipo Card

    fillDeck(deck);
    shuffle(deck);
    deal(deck);
}

// crea 52 carte
void fillDeck(Card *wDeck) {
    for (size_t i = 0; i < CARDS; i++) {
        wDeck[i].face = i % (CARDS / 4); // numeri da 0 a 13
        wDeck[i].suit= i / (CARDS / 4); // numeri da 0 a 3
        wDeck[i].color = i / (CARDS / 2); // numeri 1 o 0
    }
}

// mischia le carte
void shuffle(Card *wDeck) {
    for (size_t i = 0; i < CARDS; i++) {
        size_t j = rand() % CARDS; // seleziona una carta randomica
        
        // scambia le carte se non sono uguali
        if (i != j) {
            Card temp = wDeck[i];
            wDeck[i] = wDeck[j];
            wDeck[j] = temp;
        }
    }
}

// distribuisce le carte
void deal(Card *wDeck) {
    // array che contengono tutte le possibili stringhe di descrizione delle carte
    char* face[] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    char* suit[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    char* color[] = {"Red", "Black"};
    
    // stampa le stringhe di descrizione di ciscuna carta
    for (size_t i = 0; i < CARDS; i++) {
        printf("%5s: %5s of %-8s", color[wDeck[i].color], face[wDeck[i].face], suit[wDeck[i].suit]);
        putchar((i + 1) % 2 ? '\t' : '\n');
    }
}