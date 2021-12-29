#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_LENGTH 10

struct hashList {

    int key;
    char *word;
    struct hashList* next;

};

typedef struct hashList hashList;

struct hashTable {

    hashList **list;

};

typedef struct hashTable hashTable;

int main(){

    printf("poczatek\n");

    hashTable *new = malloc(sizeof(hashTable));

    new->list = malloc(sizeof(hashList*) * LIST_LENGTH);
    for(int i = 0; i < LIST_LENGTH; i++){

        new->list[i] = NULL;

    }

    char* word = "Tomek";

    printf("srodek\n");
    
    for(int i = 0; i < 10; i++){
    
        hashList *h = malloc(sizeof(new->list[i]) * 1);
        h->word = malloc(sizeof(char) * 6);

        strcpy(h->word, word);
        h->key = i;
        h->next  = NULL;
        //newHashTable->list[i]->collision = 0;
        //printf("\n%s", new->list[i]->word);

    }

    printf("koniec\n");

    return 0;
}
