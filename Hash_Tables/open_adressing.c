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
    int attempts[TABLE_LENGTH] = {0};

    FILE *fr;
    fr = fopen("surnames.txt","r");

    if(fr == NULL){
        printf("Error!");
        return(1);
    }

    //test for small amount of data
    /*for(int i = 0; i < 20; i++){
        char word[30];
        int popularity;
        fscanf(fr, "%d %s\n", &popularity, &word);
        hashInsert(hashtable, attempts, word, popularity);
    }*/

    for(int i = 0; i < 5400; i++){
        char word[30];
        int popularity;
        fscanf(fr, "%d %s\n", &popularity, &word);
        hashInsert(hashtable, attempts, i, word, popularity);
    }

    int mean = 0;

    for(int i = 0; i < 5400; i++){

        mean += attempts[i]; 

    }

    printf("\nMean number of attempts to insert element into a node: %d", mean/5400);

    //hashInsert(hashtable, attempts, "Tomek", 88);
    //hashInsert(hashtable, attempts, "Tomek", 88);
    //hashInsert(hashtable, attempts, "Tomek", 88);
    //hashInsert(hashtable, attempts, "Gragas", 66);
    //hashInsert(hashtable, attempts, "Piotr", 28);
    //hashInsert(hashtable, attempts, "Roman", 48);

    free(hashtable);
    fclose(fr);

    return 0;
}

//Linear probing:
//Table size: 6000; filled in 50% : mean = 5
//                  filled in 80% : mean = 22
//                  filled in 90% : mean = 60
