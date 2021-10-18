#include <stdio.h>
#include "inputoutput.h"

#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//BUBBLE SORT
void bubbleSort(Array a){
    int n = a.leng; //Giam thoi gian truy cap

    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (a.arr[i] > a.arr[j]){
                swap(a.arr + i, a.arr + j);
            }
        }
    }
}

//SELECTION SORT
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

//HEAP SORT


//QUICK SORT
void quickSort(Array a, int begin, int end){
    if (begin < end){

    }
}

//MERGE SORT
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



#endif