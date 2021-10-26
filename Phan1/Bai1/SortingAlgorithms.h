#include <stdio.h>
#include "inputoutput.h"

#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

/////////////////
// BUBBLE SORT //
/////////////////
void bubbleSort(Array a){
    int n = a.leng; //Giam thoi gian truy cap

    for (int i = n - 1; i > 0; i--){
        for (int j = 0; j < i; j++){
            if (a.arr[j] > a.arr[j + 1]){
                swap(a.arr + j, a.arr + j + 1);
            }
        }
    }
}


////////////////////
// SELECTION SORT //
////////////////////
void selectionSort(Array a){
    int n = a.leng; //Giam thoi gian truy cap

    for (int i = 0; i < n - 1; i++){
        int indexMin = i;

        for (int j = i + 1; j < n; j++){
            if (a.arr[j] < a.arr[indexMin]) indexMin = j;
        }

        if (indexMin != i) swap(a.arr + i, a.arr + indexMin);
    }
}


///////////////
// HEAP SORT //
///////////////
void heapify(int *arr, int leng, int i){
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    int largest = i;
    if (leftChild < leng && arr[leftChild] > arr[largest]) largest = leftChild;
    if (rightChild < leng && arr[rightChild] > arr[largest]) largest = rightChild;

    if (largest != i){
        swap(arr + i, arr + largest);
        heapify(arr, leng, largest);
    }
}

void heapSort(Array a){
    int n = a.leng;
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(a.arr, a.leng, i);
    }

    for (int i = n - 1; i >= 0; i--){
        swap(a.arr, a.arr + i);

        heapify(a.arr, i, 0);
    }
}
//end Heap Sort


////////////////
// QUICK SORT //
////////////////
int partition(int *arr, int begin, int end){
    int pivot = arr[begin];
    int left = begin + 1;
    int right = end;

    while (1) {
        while (left <= right && arr[left] < pivot) left++;
        while (left <= right && arr[right] > pivot) right--;

        if (left >= right) break;

        swap(arr + left, arr + right);
        left++;
        right--;
    }

    swap(arr + begin, arr + right);
    return right;
}

void quickSortFunction(int* arr, int begin, int end){
    if (begin < end){
        int indexPivot = partition(arr, begin, end);

        quickSortFunction(arr, begin, indexPivot - 1);
        quickSortFunction(arr, indexPivot + 1, end);
    }
}

void quickSort(Array a){
    quickSortFunction(a.arr, 0, a.leng - 1);
}
//end Quick Sort


////////////////
// MERGE SORT //
////////////////
void merge(int *arr, int begin, int middle, int end){
    int firstLeng = middle - begin + 1;
    int *firstArr = (int *)malloc(firstLeng * sizeof(int));
    for (int i = 0; i < firstLeng; i++){
        firstArr[i] = arr[begin + i];
    }
    int firstPtr = 0;

    int secondLeng = end - middle;
    int *secondArr = (int *)malloc(secondLeng * sizeof(int));
    for (int i = 0; i < secondLeng; i++){
        secondArr[i] = arr[middle + i + 1];
    }
    int secondPtr = 0;

    int leng = firstLeng + secondLeng;
    for (int i = 0; i < leng; i++){
        if (firstPtr == firstLeng){
            arr[begin + i] = secondArr[secondPtr];
            secondPtr++;
            continue;
        }

        if (secondPtr == secondLeng){
            arr[begin + i] = firstArr[firstPtr];
            firstPtr++;
            continue;
        }

        if (firstArr[firstPtr] < secondArr[secondPtr]){
            arr[begin + i] = firstArr[firstPtr];
            firstPtr++;
        } else {
            arr[begin + i] = secondArr[secondPtr];
            secondPtr++;
        }
    }

    free(firstArr);
    free(secondArr);
}

void mergeSortFunction(int* arr, int begin, int end){
    if (end > begin){
        int middle = begin + (end - begin) / 2;

        mergeSortFunction(arr, begin, middle);
        mergeSortFunction(arr, middle + 1, end);

        merge(arr, begin, middle, end);
    }
}

void mergeSort(Array a){
    mergeSortFunction(a.arr, 0, a.leng - 1);
}
//end Merge Sort

#endif