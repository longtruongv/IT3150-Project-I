#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

typedef struct Array {
    int leng;
    int *arr;
} Array;

void freeArray(Array a){
    free(a.arr);
}

Array inputTerminal(){
    Array a;
    scanf("%d", &a.leng);

    a.arr = (int *)malloc(a.leng * sizeof(int));
    for (int i = 0; i < a.leng; i++){
        scanf("%d", a.arr + i);
    }

    return a;
}

Array inputFile(){
    FILE *file;
    file = fopen("input.txt", "r");

    Array a;
    fscanf(file, "%d", &a.leng);

    a.arr = (int *)malloc(a.leng * sizeof(int));
    for (int i = 0; i < a.leng; i++){
        fscanf(file, "%d", a.arr + i);
    }

    fclose(file);
    return a;
}

Array inputRandom(int leng){  
    srand(time(NULL));
    Array a;
    a.leng = leng;

    a.arr = (int *)malloc(a.leng * sizeof(int));
    for (int i = 0; i < a.leng; i++){
        a.arr[i] = rand();
    }
    
    return a;
}

void outputTerminal(Array a){
    for (int i = 0; i < a.leng; i++){
        printf("%d\n", a.arr[i]);
    }
}

void outputFile(Array a){
    FILE *file;
    file = fopen("output.txt", "w");

    for (int i = 0; i < a.leng; i++){
        fprintf(file, "%d\n", a.arr[i]);
    }

    fclose(file);
}

#endif