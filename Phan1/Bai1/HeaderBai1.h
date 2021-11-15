#ifndef INPUT_OUTPUT
#define INPUT_OUTPUT

typedef struct Array {
    int leng;
    int *arr;
} Array;

void freeArray(Array a);

//INPUT
Array inputTerminal();
Array inputFile();
Array inputRandom();

//OUTPUT
void outputTerminal();
void outputFile();

#endif

#ifndef SORTING_ALGORITHMS
#define SORTING_ALGORITHMS

//SORTING ALGORITHMS
void bubbleSort(Array a);
void selectionSort(Array a);
void heapSort(Array a);
void quickSort(Array a);
void mergeSort(Array a);

#endif
