#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_LENGTH 6000
#define DEL -1  //node of array in which was stored some value but now it's empty

struct hashNode {

    int amount;
    char *word;

};

typedef struct hashNode hashNode;

struct hashTable {

    struct hashNode **table;

};

typedef struct hashTable hashTable;

hashTable *createTable(){

    hashTable *newTable = NULL;

    if((newTable = malloc(sizeof(hashTable) * 1)) == NULL ){
        printf("Couldn't allocate new hash table!");
        return NULL;
    }

    if((newTable->table = malloc(sizeof(hashNode*) * TABLE_LENGTH)) == NULL ){
        printf("Couldn't allocate nodes to new hash table!");
        return NULL;
    }

    for(int i = 0; i < TABLE_LENGTH; i++){
            newTable->table[i] = NULL;
    }

    return newTable;
}

int main(){

    hashTable *hashtable = createTable();

    //hashInsert(hashtable, attempts, "Tomek", 88);
    //hashInsert(hashtable, attempts, "Tomek", 88);
    //hashInsert(hashtable, attempts, "Tomek", 88);
    //hashInsert(hashtable, attempts, "Gragas", 66);
    //hashInsert(hashtable, attempts, "Piotr", 28);
    //hashInsert(hashtable, attempts, "Roman", 48);

    free(hashtable);
  
    return 0;
}
