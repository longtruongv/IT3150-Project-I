#include <stdio.h>
#include <stdlib.h>
#include <time.h> // time()

#include "HeaderBai1.h"

void freeArray(Array a){
    free(a.arr);
}

Array inputTerminal(){
    Array a;

    printf("\nNhap so phan tu: ");
    scanf("%d", &a.leng);

    printf("\nNhap day so:\n");
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

    printf("Doc tu file \"input.txt\" thanh cong!\n");
    fclose(file);
    return a;
}

Array inputRandom(){  
    Array a;

    printf("\nNhap so phan tu: ");
    scanf("%d", &a.leng);

    printf("Day so:\n");
    a.arr = (int *)malloc(a.leng * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < a.leng; i++){
        a.arr[i] = rand();
        printf("%5d ", a.arr[i]); //Bo comment de in day so random
    }
    
    printf("\nRandom day so thanh cong!\n");
    return a;
}

void outputTerminal(Array a){
    printf("\nDay so da sap xep:\n");
    for (int i = 0; i < a.leng; i++){
        printf("%5d ", a.arr[i]);
    }
    printf("\n");
}

void outputFile(Array a){
    FILE *file;
    file = fopen("output.txt", "w");

    for (int i = 0; i < a.leng; i++){
        fprintf(file, "%d\n", a.arr[i]);
    }

    printf("Xuat ra file \"output.txt\" thanh cong!\n");
    fclose(file);
}