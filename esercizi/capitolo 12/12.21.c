// Cerca ricorsivamente un valore specificato in una lista collegata
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode* nextPtr;
};

typedef struct ListNode ListNode;
typedef ListNode* ListNodePtr;

void insertItem(ListNodePtr* sPtr, int value);
void printList(ListNodePtr currentPtr);
void instructions(void);
ListNodePtr searchList(ListNodePtr currentPtr, const int key);

int main() {
    instructions(); // stampa il menu
    printf("%s", "?");
    int choice; // scelta di menu dell'utente
    scanf("%d", &choice);

    int item; // valore da inserire nella lista
    int searchKey; // valore da cercare nella lista
    ListNodePtr startPtr = NULL; // puntatore alla lista

    // finché l'utente non sceglie 3
    while(choice != 3) {
        // determina la scelta dell'utente
        switch(choice) {

            // inserisce un intero nella lista
            case 1:
                // richiede e legge un intero
                printf("%s", "Enter an integer: ");
                scanf("\n%d", &item);
                // inserisce l'intero nella lista e la stampa
                insertItem(&startPtr, item);
                printList(startPtr);
                break; // esce dallo switch

            // ricerca l'intero dato
            case 2:
                // richiede e legge un intero
                printf("%s", "Enter integer to recursively search for: ");
                scanf("%d", &searchKey);

                ListNodePtr searchResultPtr = searchList(startPtr, searchKey);

                // se searchKey non viene trovato
                if(searchResultPtr == NULL) {
                    printf("%d is not in the list.\n\n", searchKey);
                }
                else {
                    printf("%d is in the list.\n\n", searchResultPtr->data);
                }
                break; // esce dallo switch
            
            // caso default
            default:
                puts("Invalid choice.\n");
                instructions();
                break;
        }

        printf("%s", "? ");
        scanf("%d", &choice); // riceve la scelta successiva
    }

    printf("%s", "End of run.\n");
}

// Stampa le istruzioni
void instructions(void) {
    puts("Enter your choice:\n"
            "   1 to insertItem an element into the list.\n"
            "   2 to recursively search list for an element.\n"
            "   3 to end.\n");
}

// Inserisce un nuovo valore nella lista in ordine
void insertItem(ListNodePtr* sPtr, int value) {
    ListNodePtr newPtr = malloc(sizeof(ListNode));

    if(newPtr) {
        newPtr->data = value;
        newPtr->nextPtr = NULL;

        ListNodePtr previousPtr = NULL;
        ListNodePtr currentPtr = *sPtr;

        while(currentPtr != NULL && value > currentPtr->data) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if(previousPtr == NULL) {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        }
        else {
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }
    }
    else {
        printf("%d not inserted. No memory available.\n", value);
    }
}

void printList(ListNodePtr currentPtr) {
    if (!currentPtr) {
        puts("List is empty.\n");
    }
    else {
        while(currentPtr) {
            printf("%d --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }

        puts("NULL\n");
    }
}

// Ricerca della chiave nella lista
ListNodePtr searchList(ListNodePtr currentPtr, const int key) {
    // se currentPtr è alla fine della lista
    if (currentPtr == NULL) {
        return NULL; // chiave non trovata
    }
    else if(currentPtr->data == key) {
        return currentPtr; // chiave trovata
    }
    else {
        return searchList(currentPtr->nextPtr, key); // continua la ricerca
    }
}