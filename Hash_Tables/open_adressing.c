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

int hash(const char* string, int attempt){

    int len = strlen(string);
    int result = 0, i;

    for(i = 0; i < len-1; i = i+2){
        result ^= ((256*string[i]) + string[i+1]);
    }

    if(string[i] != 0){
        result ^= (256*string[i]);
    }

    return ((result % TABLE_LENGTH) + attempt) % TABLE_LENGTH;

}

hashNode *setNode(int key, const char *string){
        
    hashNode *newNode;

    if((newNode = malloc(sizeof(hashNode) * 1)) == NULL){
        return NULL;
    }

    newNode->amount = key;

    if((newNode->word = strdup(string)) == NULL){
        return NULL;
    }

    return newNode;
}

void hashInsert(hashTable* hashtable, int attempts[], int count, const char* string, int popularity){

    for(int i = 0; i < TABLE_LENGTH; i++){

        int j = hash(string, i);
        printf("%d\n", j);
        attempts[count]++;

        if(hashtable->table[j] == NULL){

            hashtable->table[j] = setNode(popularity, string);

            printf("Word \"%s\" was inserted in node number %d\n", hashtable->table[j]->word, j);
            return;
        }

    }

    printf("There is no place for string \"%s\"", string);
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
