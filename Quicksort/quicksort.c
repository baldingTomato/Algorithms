#include <stdio.h>

void swap(int *a, int *b){
    
    int temp = *a;
    *a = *b;
    *b = temp;

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

    int cons = 3;
    int length = sizeof(arr)/sizeof(arr[0]);

    if (left + cons < right){
        int pivot = partition(arr, left, right);
        quickSort(arr, left, pivot - 1);
        quickSort(arr, pivot + 1, right);
    }
}

int main(){

    int arr[] = {4, 12, 2, 5, 5, 1, 7, 8, 9, 3, 6};
    int length = sizeof(arr)/sizeof(arr[0]);
    
    quickSort(arr, 0, length-1);
    
    printf("The sorted array is: ");
    
    for (int i = 0; i < length; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}