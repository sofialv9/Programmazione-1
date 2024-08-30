#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

// Una struct per conservare i dati dell'account
typedef struct {
    int accountNumber;
    // Le stringhe sono allocate in maniera automatica poiché si conosce la lunghezza massima. Verranno allocate quando creiamo una nuova struct.
    char firstName[255]; 
    char lastName[255];
    float balance;
} Account;

// La struct nodo della lista usata per creare la lista concatenata
struct listNode {
    Account data;
    struct listNode *next;
};

// Una abbreviazione per la struct listNode
typedef struct listNode ListNode;



// Inserisce un nuovo nodo in testa
bool insertHead(ListNode **head, Account data) {
    // prendiamo in input doppio puntatore a head necessario se vogliamo sia modificare il contenuto puntato da head che cambiare l'indirizzo di memoria del puntatore alla testa (usato nell'inserimento) - utile nell'inserimento in testa e nell'eliminazione di un nodo di una lista.

    // Nuovo nodo da inserire - si alloca lo spazio che dovrà contenere una struct Account e un puntatore a una struct listNode
    ListNode *newHead = malloc(sizeof(ListNode));

    // se non sono riuscito ad allocare memoria
    if(newHead == NULL)
        return false; // restituisci false, indica che c'è stato un problema
        // questa istruzione termina anche l'esecuzione della funzione

    newHead->next = *head; // la nuova testa avrà come next la vecchia testa
    newHead->data = data; // inseriamo i dati nella nuova testa - si può fare perché data è allocato dinamicamente e passato per valore alla funzione

    *head = newHead; // cambia l'indirizzo della testa - ciò si può fare perché head è stato passato come doppio puntatore

    return true; // restituisci true, l'inserimento è andato a buon fine
}

// Inserisce un nuovo nodo in coda
bool insertTail(ListNode **head, Account data) { 
    if(*head == NULL) { // Se la testa è NULL (cioè se la lista è vuota) inseriamo un nodo in testa.
        return insertHead(head, data); // qui si potrebbe direttamente inserire il codice per inserire un nodo in testa
    }
    
    // Devo scorrere tutti i nodi della lista . Uso il puntatore "currentPtr" come "cursore" per scorrere i vari nodi, iniziando dalla testa.
    ListNode *currentPtr = *head; // copia l'indirizzo della testa in currentPtr
    while(currentPtr->next) { // finché il prossimo nodo non è NULL non siamo ancora alla fine della lista, quindi scorro il cursore
        currentPtr = currentPtr->next; // il nuovo cursore è il prossimo nodo
    } // Una volta terminato, currentPtr contiene la coda (se il next è NULL si è raggiunto l'ultimo nodo della lista)

    // Creo il nuovo nodo
    ListNode* newNode = malloc(sizeof(ListNode)); 
    
    // Se newNode è NULL, non sono riuscito ad allocare correttamente
    if(newNode == NULL)
        return false; // indica che c'è stato un problema e esci dalla funzione
        
    // inserisci i dati nel nuovo nodo
    newNode->data = data;
    newNode->next = NULL; //next punta a NULL, è la nuova coda

    currentPtr->next = newNode; // la vecchia coda punta al nuovo nodo

    return true; // restituisco true (tutto è andato a buon fine)
}

// Funzione di utilità per inserire un nodo dopo un dato nodo
bool insertAfter(ListNode **node, Account data) {
    // Alloco il nuovo nodo
    ListNode* newNode = malloc(sizeof(ListNode));

    if(!newNode) //errore se non riesco ad allocare
        return false;

    // inserisco i dati
    newNode->data = data;
    newNode->next = (*node)->next; // il nuovo nodo punta al next del nodo dopo il quale inserire

    // il nodo dopo il quale inserire avrà il nuovo nodo come next
    (*node)->next = newNode;

    return true; // nessun error
}

// Effettua un inserimento ordinato per accountNumber - assume che la lista sia ordinata
bool insertOrdered(ListNode **head, Account data) {
    ListNode *currentPtr = *head; // cursore per scorrere fino al punto di inserimento
    ListNode *lastPtr = NULL; // tengo anche un riferimento allo scorso puntatore
    // ci servirà per effettuare un inserimento con insertAfter

    // finché il puntatore corrente non è NULL (equivalente a currentPtr != NULL)
    // e l'account number del nodo corrente è inferiore all'account number da inserire
    while(currentPtr && currentPtr->data.accountNumber < data.accountNumber) {
        lastPtr = currentPtr; // aggiorna riferimento allo scorso puntatore
        currentPtr = currentPtr->next; // aggiorna riferimento al puntatore corrente
    }

    if(lastPtr == NULL) //se lastPtr è NULL, non siamo entrati nel while (cioè data.accountNumber è inferiore a tutti i numeri di account o non è presente nessun nodo)
        return insertHead(head, data); // in entrambi i casi va effettuato un inserimento in testo

    // se siamo arrivati qui, abbiamo un lastPtr valido e dobbiamo inserire dopo quello
    return insertAfter(&lastPtr, data);
}

// Effettua la cancellazione della testa
bool deleteHead(ListNode **head) {
    // se la lista è vuota
    if(*head == NULL)
        return false; // indichiamo che non abbiamo trovato l'elemento

    // nodo temporaneo per non perdere l'indirizzo di head in modo da poter liberare la memoria
    ListNode *tmpNode = *head;

    *head = (*head)->next; // la nuova head è il secondo nodo
    free(tmpNode); // liberiamo la memoria occupata da tmpNode
    return true; // restituiamo true, abbiamo cancellato con successo
}

// while(deleteNode(head)); per eliminare più nodi si itera la funzione finché la funzione non ritorna NULL (cioè finché il dato da eliminare non è più presente nella lista)

// Effettua la cancellazione di un nodo con un certo accountNumber
bool deleteNode(ListNode **head, int accountNumber) {
    if(*head==NULL)
        return false; // il nodo da cancellare non esiste
    // se trovo il valore in testa
    if(accountNumber == (*head)->data.accountNumber)
        return deleteHead(head); //elimino il nodo in testa

    // mantengo un riferimento allo scorso nodo
    ListNode *lastPtr = NULL;
    ListNode *currentPtr = *head; // cursore per scorrere fino al nodo da cancellare

    // scorriamo finché il currentPtr è non NULL e accountNumber corrente è diverso dal numero di account da rimuovere
    while(currentPtr && currentPtr->data.accountNumber != accountNumber) {
        // aggiorna riferimenti
        lastPtr = currentPtr;
        currentPtr = currentPtr->next;
    }

    if(currentPtr == NULL) //se currentPtr è NULL la lista è vuota o siamo a fine lista
        return false; // non abbiamo trovato l'elemento da cancellare

    // altrimenti, colleghiamo lo scorso puntatore al prossimo
    lastPtr->next = currentPtr->next;
    removeAccount(currentPtr->data); //liberiamo memoria account
    free(currentPtr); //liberiamo memoria nodo

    return true; //cancellazione corretta
}

bool printList(ListNode *head) { //stampiamo la lista
    if(head == NULL) //se è vuota non posso stampare
        return false;

    // cursore per scorre la lista
    ListNode *currentNode = head;

    // finché il nodo corrente non è NULL
    while(currentNode) {
        // stampo account
        printf("%d %s %s %f\n", currentNode->data.accountNumber, currentNode->data.firstName, currentNode->data.lastName, currentNode->data.balance);
        // continuo a scorrere la lista
        currentNode = currentNode->next;
    }
    
    return true; // la stampa è andata a buon fine
}

// Calcolo la lunghezza della lista - unico modo
int listlen(ListNode *head) {
    ListNode *cursor = head;

    int i = 0; // lunghezza
    while(cursor){ // se è NULL la lista è vuota e quindi la funzione restituisce 0 (non ci sono nodi)
        cursor = cursor->next; //scorro la lista
        i++; // incremento contatore
    }

    return i;
}


int main() {
    ListNode *head = NULL;

    char firstName[255];
    char lastName[255];
    int accountNumber = 0;
    float balance;

    int tipoInserimento;

    puts("Scegli un tipo di inserimento (default: coda):");
    puts(" 1 in testa");
    puts(" 2 ordinato");
    puts(" 3 in coda");
    

    scanf("%d", &tipoInserimento);

    printf("Scelto inserimento ");
    switch(tipoInserimento) {
        case 1:
            printf("in testa");
            break;
        case 2:
            printf("ordinato");
            break;
        default:
            printf("in coda");
    }
    puts("");
    puts("");

    puts("Inserisci dati account nel formato \"accountNumber firstName lastName balance\".");
    puts("Ad esempio: 1234 John Doe 123.5");
    puts("Termina l'inserimento inserendo -1 -1 -1 -1");
    while(accountNumber!=-1) {
        Account data; // allocazione automatica di una struct data
        printf("?: ");
        scanf("%d %s %s %f", &accountNumber, firstName, lastName, &balance);
        if(accountNumber==-1) {
            break;
        }
       
        bool result;
        switch(tipoInserimento) {
            case 1:
                result = insertHead(&head, data); // i dati nella lista sono in ordine inverso rispetto a quello di inserimento
                break;
            case 2:
                result = insertOrdered(&head, data); // i dati nella lista sono in ordine in base al dato accountnumber
                break;
            default:
                result = insertTail(&head, data); // i dati nella lista sono nello stesso ordine rispetto a quello di inserimento
        }
            
        if(!result) // si verifica solo se la memoria è piena
            fprintf(stderr, "Errore inserendo l'elemento!\n");
    }

    puts("\nEcco i dati da te inseriti:");
    printList(head);

    printf("Quale account vuoi eliminare? ");
    int toRemove;
    scanf("%d", &toRemove);

    printf("Rimuovo %d\n", toRemove);

    if(deleteNode(&head, toRemove)) { // se ritorna true (ha trovato il nodo da eliminare nella lista)
        puts("\n\nEcco la lista dopo la cancellazione:");
        printList(head);
    } else { // se ritorna false (il nodo non è presente nella lista)
        printf("L'account %d non esiste\n", toRemove);
    }

    printf("\nLunghezza della lista: %d\n", listlen(head));
}