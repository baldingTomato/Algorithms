/*
This is a simple hash table implementation for my uni assignment. In this hash table I can store words, their hashed values (keys) and
collisions are handled with single linked lists. Size of hash table is defined by big prime number.
In the future I may use this for testing how much collisions occure with this hashing function.
*/
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

//Hash a string for a particular hash table
int hash(char *word){

        int len = strlen(word);
        int result = 0, i;

        for(i = 0; i < len-1; i = i+2){
            result ^= ((256*word[i]) + word[i+1]);
        }

        if(word[i] != 0){
                result ^= (256*word[i]);
        }

        return result%LIST_LENGTH;
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

// Retrieve a key-string pair from a hash table.
char *findWord(hashTable *hashtable, char *string){

        int slot = 0;
        int collisions = 0;
        hashList *pair;

        slot = hash(string);

        // Step through the slot, looking for our word.
        pair = hashtable->table[slot];
        while( pair != NULL && pair->word != NULL && strcmp(string, pair->word) != 0) {
                pair = pair->hash_list;
        }

        // Did we actually find anything?
        if(pair == NULL || pair->word == NULL || strcmp(string, pair->word) != 0){
                printf("\"%s\" - ", string);
                return "there is no such word in hashtable!";

        } else {
                printf("Key: %d, Collisions: %d ", pair->key, hashtable->collisions[slot]);
                return pair->word;
        }

}

int main(){

    hashTable *hashtable = createHashTable();

    setHashTable(hashtable, "pop");
    setHashTable(hashtable, "pinky");
    setHashTable(hashtable, "jurny");
    setHashTable(hashtable, "blinky");
    setHashTable(hashtable, "Finick");
    setHashTable(hashtable, "Tomek");
    setHashTable(hashtable, "brach");

    printf( "%s\n", findWord(hashtable, "pop"));
    printf( "%s\n", findWord(hashtable, "pinky"));
    printf( "%s\n", findWord(hashtable, "blinky"));
    printf( "%s\n", findWord(hashtable, "Tomek"));
    printf( "%s\n", findWord(hashtable, "brachu"));
    printf( "%s\n", findWord(hashtable, "Finick"));

    free(hashtable);

}
