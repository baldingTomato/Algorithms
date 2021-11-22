#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_ELEMENTS 5

int getMaxLength(int arr[]){

    int max = 0;

    for(int i = 0; i < NO_ELEMENTS; i++){
        if(max < arr[i]){
            max = arr[i];
        }
    }

    return max;
}

void countSort(char** words, int length[], int position){

    char **temp;
    *temp = malloc(NO_ELEMENTS * sizeof(char*));
    int occurrences[123] = {0};

    for (int j = 0; j < NO_ELEMENTS; j++){   
        //ccurrences[position < strlen(words[j]) ? (int)(unsigned char)words[j][position] + 1 : 0]++;
        occurrences[*(words[j]+length[j]-1)]++;
        temp[j] = malloc(length[j] * sizeof(char));
    }

     for(int f = 1; f < 123; f++){
        occurrences[f] += occurrences[f - 1];
    }

     for(int r = NO_ELEMENTS - 1; r >= 0; r--){
        temp[occurrences[position < strlen(words[r]) ? (int)(unsigned char)words[r][position] + 1 : 0] - 1] = *(words + r);
        occurrences[position < strlen(words[r]) ? (int)(unsigned char)words[r][position] + 1 : 0]--;
    }

     for(int l = 0; l < NO_ELEMENTS; l++){
        words[l] = temp[l];
    }

}

void radixSort(char** words, int length[]){

    int max = getMaxLength(length);

    for(max; max > 0; max--){
        countSort(words, length, max - 1);
    }

}

int main(){

    FILE *fr;
    int length[NO_ELEMENTS];
    int popularity[NO_ELEMENTS];

    char **words;
    *words = malloc(NO_ELEMENTS * sizeof(char*));

    fr = fopen("test.txt","r");
    
    if (fr == NULL){
       printf("Error!");
       return(1);
    }

    for(int i = 0; i < NO_ELEMENTS; i++){

        char word[20];

        fscanf(fr, "%d %s\n", &popularity[i], &word);
        //printf("%d, %s\n", popularity[i], word);
        length[i] = strlen(word);
        words[i] = malloc(length[i] * sizeof(char));
        strcpy(words[i], word);
        printf("%d, %s.\n", popularity[i], words[i]);
        
    }
    
    radixSort(words, length);

    for(int i = 0; i < NO_ELEMENTS; i++){
            printf("%s.\n", words[i]);
    }

    fclose(fr);
    return 0;
}