#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIST_LENGTH 14011

struct hashList {

        int key;
        char *word;
        struct hashList *hash_list;

};

typedef struct hashList hashList;

struct hashTable {

        struct hashList **table;
        int *collisions;

};

typedef struct hashTable hashTable;

//Create a new hashtable
hashTable *createHashTable(){

        hashTable *hashtable = NULL;

        if((hashtable = malloc(sizeof(hashTable) * 1)) == NULL ){
                return NULL;
        }

        if((hashtable->table = malloc(sizeof(hashList*) * LIST_LENGTH)) == NULL){
                return NULL;
        }

        if((hashtable->collisions = (int*) calloc(LIST_LENGTH, sizeof(int))) == NULL){
                return NULL;
        }

        for(int i = 0; i < LIST_LENGTH; i++){
                hashtable->table[i] == NULL;
        }

        return hashtable;
}

int main(){

    hashTable *hashtable = createHashTable();
  
  return 0;
}
