/*
This program uses radix sort for sorting alphabetically Polish surnames and their popularity in text files. It stores strings with different length
in an array.
I am also measuring elapsed time of an algorithm. For comparison I used quicksort to see how fast radix sort is.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define NO_ELEMENTS 20000

//	functions for Quicksort:

void swap(char **a, char **b) {
	char *temp = *a;
	*a = *b;
	*b = temp;
}

void quicksort(char *arr[], unsigned int length, int *popularity){

	unsigned int i, piv = 0;
	int temp;
	if (length <= 1) 
		return;
	
	for (i = 0; i < length; i++) {
		// if curr str < pivot str, move curr into lower array and  lower++(pvt)
		if (strcmp(arr[i], arr[length -1]) < 0){
			swap(arr + i, arr + piv++);				//use string in last index as pivot
			temp = popularity[i];
			popularity[i] = popularity[piv];
			popularity[piv] = temp;
		}	
			

	}
	//move pivot to "middle"
	swap(arr + piv, arr + length - 1);

	//recursively sort upper and lower
	quicksort(arr, piv++, popularity);			//set length to current pvt and increase for next call
	quicksort(arr + piv, length - piv, popularity);
}


//	functions for Radix Sort:

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

	int *occurrences = calloc(no_characters, sizeof(int));	//array of 'buckets' for every character in alphabet

	// variables for counting
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
			temp[temp_index] = words[i];	//change order of words
			temp_lengths[temp_index] = length[i];	//shorten length
			temp_popularity[temp_index] = popularity[i];	//swap popularity
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
	free(temp_popularity);

	return words;
}

void radixSort(char **words, int *length, int *popularity){		//sorts strings starting from last character

	int max = getMaxLength(length);

	// sorting from least significant character
	for(int position = max - 1; position >= 0; position--){
		counting_sort(words, length, position, popularity);
	}

	
}

int main(){

	LARGE_INTEGER frequency;        // ticks per second
    LARGE_INTEGER t1, t2;           // ticks
    double elapsedTime;
    srand(time(NULL));

    FILE *fr, *fw;
    int *popularity = malloc(NO_ELEMENTS * sizeof(int));	//array for popularity of surnames

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
        //printf("%s\n", words[i]);
        
    }

	QueryPerformanceFrequency(&frequency);  //start counting time
    QueryPerformanceCounter(&t1);
    
    radixSort(words, length, popularity);
	//quicksort(words, NO_ELEMENTS, popularity);

	QueryPerformanceCounter(&t2);   //finish counting time

    //print(words, popularity);

	for(int i = 0; i < NO_ELEMENTS; i++){
		fprintf(fw,"%d %s\n",popularity[i], words[i]);
	}

	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
    printf("Elapsed time: %3.7lf ms", elapsedTime);


    free(length);

    fclose(fr);
	fclose(fw);
    return 0;
}
