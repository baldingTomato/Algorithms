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

//Inserts given word and its 'hashed key'
hashList *insertHash(int key, char *string){
        
        hashList *newpair;

        if((newpair = malloc(sizeof(hashList))) == NULL){
                return NULL;
        }

        newpair->key = key;

        if((newpair->word = strdup(string)) == NULL){
                return NULL;
        }

        newpair->hash_list = NULL;

        return newpair;
}

//Insert a key-string pair into a hash table 
void setHashTable(hashTable *hashtable, char *string){

        int slot = 0;
        hashList *newpair = NULL;
        hashList *hash_list = NULL;
        hashList *prev = NULL;

        slot = hash(string);

        hash_list = hashtable->table[slot];

        while(hash_list != NULL && hash_list->word != NULL && strcmp(string, hash_list->word) != 0){
                prev = hash_list;
                hash_list = hash_list->hash_list;
        }

        newpair = insertHash(slot, string);

        //Start of the linked list in this slot.
        if(hash_list == hashtable->table[slot]){
                newpair->hash_list = hash_list;
                hashtable->table[slot] = newpair;
        
        //End of the linked list in this slot.
        }else if(hash_list == NULL){
                hashtable->collisions[slot]++;
                prev->hash_list = newpair;
        }
}

int main(){

    hashTable *hashtable = createHashTable();
  
  return 0;
}
