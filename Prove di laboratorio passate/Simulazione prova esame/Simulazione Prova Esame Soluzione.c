
#include<stdlib.h>

#include<stdio.h>

#include<stdbool.h>

#include<string.h>

 

typedef struct {

    char word[100];

    int count;

} Riga;

 

struct node {

    Riga data;

    struct node *next;

};

 

typedef struct node Node;

 

bool insertHead(Node **head, Riga r) {

    Node *newNode = malloc(sizeof(Node));

    if(newNode==NULL)

        return false;

    newNode->data = r;

 

    newNode->next = *head;

    *head = newNode;

 

    return true;

}

 

bool insertTail(Node **head, Riga r) {

    if(*head==NULL) {

        return insertHead(head, r);

    }

 

    Node *ptr = *head;

 

    while(ptr->next) {

        ptr = ptr->next;

    }

 

    Node *newNode = malloc(sizeof(Node));

 

    if(newNode==NULL)

        return false;

 

    newNode->data = r;

    newNode->next = NULL;

 

    ptr->next = newNode;

   

    return true;

}

 

Node* readFile(char *name) {

    Node **head = malloc(sizeof(Node*));

    *head = NULL;

    FILE *f = fopen(name, "r");

 

    char s[1000];

 

    bool done = false;

 

    while(!done) {

        char *out = fgets(s, 1000, f);

        if(out!=NULL) {

            char *tok = strtok(s, " \n");

            char *firstTok = tok;

            int count = 0;

            do {

                if(strcmp(firstTok, tok)==0) {

                    count++;

                }

               

            } while((tok=strtok(NULL, " \n")));

            Riga r;

            r.count = count;

            strcpy(r.word, firstTok);

            insertTail(head, r);

        } else {

            done = true;

        }

    }

 

    return *head;

}

 

void printList(Node *head) {

    Node *ptr = head;

 

    while(ptr) {

        Riga *r = &ptr->data;

        printf("%s %d\n", r->word, r->count);

        ptr = ptr->next;

    }

}

 

bool deleteHead(Node **head) {

    if(*head) {

        Node *tmp = *head;

        *head = (*head)->next;

        free(tmp);

        return true;

    } else {

        return false;

    }

}

 

void filterList(Node **head, int n) {

    if(*head==NULL) {

        return;

    }

 

    Node *ptr = *head;

    Node *prevPtr = NULL;

 

    while(ptr) {

        if(ptr->data.count<n) {

            if(prevPtr==NULL) {

                deleteHead(head);

                ptr = *head;

                continue;

            } else {

                Node *tmp = ptr;

                prevPtr->next = ptr->next;

                free(tmp);

                ptr = prevPtr;

            }

        }

 

        prevPtr = ptr;

        ptr = ptr->next;

    }

}

 

int readN(int argc, char *argv[]) {

    if(argc!=2) {

        fprintf(stderr, "Errore, bisogna passare un parametro intero da riga di comando.\n");

        exit(-1);

    }

 

    char **end = malloc(sizeof(char*));

    int n = (int) strtol(argv[1], end, 0);

 

    if(!end || n < 0) {

        fprintf(stderr, "Errore, il parametro passato deve essere intero positivo.\n");

        exit(-1);

    }

 

    return n;

}

 

int main(int argc, char *argv[]) {

    int n = readN(argc, argv);

 

    Node **head = malloc(sizeof(Node*));

 

    *head = readFile("input.txt");

    filterList(head, n);

    printList(*head);

}