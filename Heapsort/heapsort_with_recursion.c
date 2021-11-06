#include <stdio.h>
#include <math.h>

void swap(int *a, int *b){
    
    int temp = *a;
    *a = *b;
    *b = temp;

}

void heapify(int arr[], int size, int father){

    int largest = father;
    int l = 2*father + 1;
    int r = 2*father + 2;

    if(l < size && arr[l] > arr[largest]){
        largest = l;
    }

    if(r < size && arr[r] > arr[largest]){
        largest = r;
    }

    if(largest != father){        
        swap(&arr[largest], &arr[father]);
        heapify(arr, size, largest);
    }

}

void heapSort(int arr[], int size){
    
    for (int i = size/2 - 1; i >= 0; i--){
        heapify(arr, size, i);
    }
    
    for (int i = size - 1; i > 0; i--) { 
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main(){

    int n = 16;
    int tree[n];

    FILE *fr, *fw;

    fr = fopen("C:\\Users\\tomek\\Desktop\\C\\Algosy\\heap.txt","r");
    fw = fopen("C:\\Users\\tomek\\Desktop\\C\\Algosy\\sorted_heap.txt","w");
    

    if (fr == NULL){
       printf("Error!");
       return(1);
    }

    for(int i = 0; i < n; i++){
        fscanf(fr,"%d ", &tree[i]);
    }
    
    heapSort(tree, sizeof(tree)/sizeof(int));

    for(int i = 0; i < n; i++){
      printf("%d, ", tree[i]);
    }

    for(int i = 0, j = 0, c = 0; i < n; i++){   //decomposing numbers in text file, in a shape of heap
                                                //
        if(pow(2, j) == c){                     //"c" is a counter of numbers in a row, every row has 2^j numbers in it
            fprintf(fw,"\n");                   //
            i--;                                //decreasing the "i" counter to not to omit the array element after typing "\n"
            j++;                                //new row -> higher power of two
            c = 0;                              //reseting the counter of numbers for a new line
        }else{                                  //
            fprintf(fw,"%d ", tree[i]);         //
            c++;                                //increasing the counter of numbers in a row
        }                                       //
    }                                           //

    fclose(fr);
    fclose(fw);
     
    return 0;
}
