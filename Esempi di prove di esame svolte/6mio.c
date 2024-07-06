#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

unsigned int get_random() {
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

int readInput(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Uso: %s n.\n", argv[0]);
        exit(-1);
    }

    char* end;
    int n = (int) strtol(argv[1], &end, 10);
    if(*end){
        fprintf(stderr, "Errore: n deve essere un intero.\n");
        exit(-1);
    }
    if(n < 0){
        fprintf(stderr, "Errore: n deve essere un intero.\n");
        exit(-1);
    }
    
    return n;
}

typedef struct node{
    char data;
    struct node* next;
} Node;

bool isEmpty(Node* head){
    return head == NULL;
}

void push(Node** head, char c){
    Node* new = malloc(sizeof(Node));
    if(!new){
        fprintf(stderr, "Errore di allocazione della memoria.\n");
        exit(-1);
    }
    new->data = c;
    new->next = *head;
    *head = new;
}

char pop(Node** head){
    if(isEmpty(*head)){
        fprintf(stderr, "Errore: la pila è vuota.\n");
        exit(-1);
    }
    
    char out = (*head)->data;
    Node* tmp = *head;
    *head = (*head)->next;
    free(tmp);
    return out;
}

char getRandomChar(char* string){
    return string[get_random() % strlen(string)];
}

char genVowel(){
    return getRandomChar("AEIOUaeiou");
}

char genConsonant(){
    return getRandomChar("BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz");
}

int charToInt(char c){
    char tmp[2];
    tmp[0] = c;
    tmp[1] = 0;
    char* end;
    int out = (int) strtol(tmp, &end, 10);
    return out;
}

Node** fillStack(int n){
    Node** head = malloc(sizeof(Node*));
    *head = NULL;

    for(int i = 0; i < n; i++){
        char x = getRandomChar("123456789");
        
        if(x >= '1' && x <= '4'){
            for(int j = 0; j < charToInt(x); j++){
                push(head, genVowel());
            }
            push(head, x);
        } else {
            for(int j = 0; j < charToInt(x); j++){
                char consonant = genConsonant();
                if(consonant == 'v'){
                    consonant = '*';
                } else if (consonant == 'w'){
                    consonant = '?';
                }
                push(head, consonant);
            }
            push(head, x);
        }
    }
    return head;
}

char** emptyStack(int n, Node** head){
    char** array = calloc(n, sizeof(char*));
    int i = 0;
    while(!isEmpty(*head)){
        char c = pop(head);
        int x = charToInt(c);
        array[i] = calloc(x + 1, sizeof(char)); //ERRORE-> messo x e non x + 1
        for(int j = 0; j < x; j++){
            array[i][j] = pop(head);
        }
        i++;
    }
    return array;
}

void printArray(char** array, int n){
    for(int i = 0; i < n; i++){
        printf("%s\n", array[i]);
    }
}

int main(int argc, char* argv[]){
    int n = readInput(argc, argv);
    
    Node** head = fillStack(n);

    char** array = emptyStack(n, head);

    printArray(array, n);
}