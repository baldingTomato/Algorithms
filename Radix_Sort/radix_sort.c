#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_ELEMENTS 20000


int getMaxLength(int *arr){

    int max = 0;

    for(int i = 0; i < NO_ELEMENTS; i++){
        if(max < arr[i]){
            max = arr[i];
        }
    }

    return max;
}

int char_to_index(char character){

	int index = 0;

	if(character >= 'a') {
		index = character - 'a';
	}else if(character <= '9'){
		index = character - 20;
	}else{
		index = character - 'A';
	}

	// '0' index is reserved for 'not existing' character (word shorter than sorted position)
	return index + 1;
}

char** counting_sort(char **words, int *length, int position, int *popularity){

	int no_characters = 37;	// I do not need to count big letters differently

	int *occurrences = calloc(no_characters, sizeof(int));

	// for counting
    long i = 0;
	char curr_char;
	int index;

	for (i = 0; i < NO_ELEMENTS; i++){
		// check if word has character at given position (may be shorter), if it doesn't increment '0' index
		if(position < length[i]){
			curr_char = words[i][position];
			index = char_to_index(curr_char);
			occurrences[index]++;
		}else{
			occurrences[0]++;
		}
	}

	// compute first positions in output array for each bucket
	long sum = 0;
	long curr_count;
	for(i = 0; i < no_characters; i++){
		curr_count = occurrences[i];
		occurrences[i] = sum;
		sum += curr_count;
	}

	//	arrays for swaping words in original array
	char **temp = malloc(NO_ELEMENTS * sizeof(char*));
    int *temp_lengths = malloc(NO_ELEMENTS * sizeof(int));
	int *temp_popularity = malloc(NO_ELEMENTS * sizeof(int));

	//	computing element positions
	for(i = 0; i < NO_ELEMENTS; i++){

		if(position >= length[i]){
            temp_lengths[occurrences[0]] = length[i];
			temp[occurrences[0]] = words[i];
			temp_popularity[occurrences[0]] = popularity[i];
			occurrences[0]++;
		}else{
			index = char_to_index(words[i][position]);
			int temp_index = occurrences[index];
			temp[temp_index] = words[i];
			temp_lengths[temp_index] = length[i];
			temp_popularity[temp_index] = popularity[i];
			occurrences[index]++;
		}

	}

	free(occurrences);

	// copying positions to 'words'
	for(i = 0; i < NO_ELEMENTS; i++){
		words[i] = temp[i];
		length[i] = temp_lengths[i];
		popularity[i] = temp_popularity[i];
	}

	free(temp);
	free(temp_lengths);

	return words;
}

void radixSort(char **words, int *length, int *popularity){

	int max = getMaxLength(length);

	// sorting from least significant character
	for(int position = max - 1; position >= 0; position--){
		counting_sort(words, length, position, popularity);
	}

	
}

void print(char **words, int popularity[]){

	for (long i = 0; i < NO_ELEMENTS; i++){
		printf("\n%d %s", popularity[i], words[i]);
	}
    
}

int main(){

    FILE *fr, *fw;
    int *popularity = malloc(NO_ELEMENTS * sizeof(int));

    int *length = malloc(NO_ELEMENTS * sizeof(int));
    char *words[NO_ELEMENTS];

    fr = fopen("test.txt","r");
	fw = fopen("sorted_test.txt","w");
    
    if (fr == NULL){
       printf("Error!");
       return(1);
    }

    for(int i = 0; i < NO_ELEMENTS; i++){

        char word[30];

        fscanf(fr, "%d %s\n", &popularity[i], &word);
        //printf("%d, %s\n", popularity[i], word);
        length[i] = strlen(word);
        words[i] = (char *)malloc((length[i]+1)*sizeof(char));
        strcpy(words[i], word);
        printf("%s\n", words[i]);
        
    }
    
    radixSort(words, length, popularity);

    //print(words, popularity);

	for(int i = 0; i < NO_ELEMENTS; i++){
		fprintf(fw,"%d %s\n",popularity[i], words[i]);
	}


    free(length);

    fclose(fr);
	fclose(fw);
    return 0;
}
