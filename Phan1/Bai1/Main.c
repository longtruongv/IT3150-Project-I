#include <stdio.h>
#include "InputOutput.h"
#include "SortingAlgorithms.h"

int main(){
    Array a = inputFile();
    mergeSort(a);
    outputTerminal(a);
    
    freeArray(a);
    return 0;
}