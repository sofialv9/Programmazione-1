// Stampa in maniera ricorsiva gli elementi in una lista in ordine inverso
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int data;
    struct ListNode* nextPtr;
};
typedef struct ListNode ListNode;
typedef ListNode* ListNodePtr;

void printList(ListNodePtr currentPtr);
void printListBackward(ListNodePtr currentPtr);
void insertItem(ListNodePtr* sPtr, int value);

int main() {
    ListNodePtr startPtr = NULL; // puntatore alla lista

    // inserisce interi nella lista
    for(int item = 1; item < 11; ++item) {
        insertItem(&startPtr, item);
    }
    printList(startPtr);
    printf("%s", "\n");
    printListBackward(startPtr);
    puts("*\n");
}

// Inserisce un nuovo valore della lista in ordine
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
    if(!currentPtr) {
        puts("List is empty.\n");
    }
    else {
        while(currentPtr) {
            printf("%d  ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
        puts("*\n");
    }
}

// Stampa la lista ricorsivamente a ritroso
void printListBackward(ListNodePtr currentPtr) {
    if(currentPtr == NULL) {
        puts("The list reversed is:");
    }
    else{
        printListBackward(currentPtr->nextPtr);
        printf("%d  ", currentPtr->data);
    }
    
}