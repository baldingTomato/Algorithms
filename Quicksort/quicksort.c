#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define CONS 3
#define SIZE 10000

void swap(int *a, int *b){
    
    int temp = *a;
    *a = *b;
    *b = temp;

}

void bubbleSort(int arr[], int left, int right){
    
    for(int i = left; i < right - 1; i++){
        for(int j = 0; j < right - i - 1; j++){
            if(arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }

}

int partition(int arr[], int left, int right){  //divides array into two subarrays separated by a pivot

    int pivot = arr[right];
    int i = (left - 1);
    
    for (int j = left; j <= right - 1; j++){
        if (arr[j] <= pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[right]);

    return (i + 1);
}

void quickSort(int arr[], int left, int right){

    if (left < right){
        int pivot = partition(arr, left, right);
        quickSort(arr, left, pivot - 1);
        quickSort(arr, pivot + 1, right);
    }  

}

void modifiedQuickSort(int arr[], int left, int right){

    if (left + CONS < right){
        int pivot = partition(arr, left, right);
        quickSort(arr, left, pivot - 1);
        quickSort(arr, pivot + 1, right);
    }else if(left + CONS >= right){
        bubbleSort(arr, left, right);
    }

}

void randomArray(int arr[]){        //fills an array with random integers

    for (int i = 0; i < SIZE; i++){
        arr[i] = rand() % 300 + 1;
    //    printf("%d ", arr[i]);
    }

}

void pessimistic(int arr[]){

    for (int i = 0; i < SIZE; i++){
        arr[i] = SIZE - i;
    //    printf("%d ", arr[i]);
    }

}

int main(){
    
    LARGE_INTEGER frequency;        // ticks per second
    LARGE_INTEGER t1, t2;           // ticks
    double elapsedTime;
    srand(time(NULL));

    int arr[SIZE];

    randomArray(arr);
    //pessimistic(arr);
    
    QueryPerformanceFrequency(&frequency);  //start counting time
    QueryPerformanceCounter(&t1);

    modifiedQuickSort(arr, 0, SIZE-1);

    QueryPerformanceCounter(&t2);   //finish counting time

    elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
    printf("Elapsed time: %3.7lf ms", elapsedTime);

    return 0;
}
