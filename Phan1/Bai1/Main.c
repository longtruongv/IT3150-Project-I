#include <stdio.h>
#include <stdlib.h> //system()
#include <time.h> //clock()
#include "InputOutput.h"
#include "SortingAlgorithms.h"

int main(){
    Array (* inputFunction)();
    void (* outputFunction)(Array);
    void (* sortingAlgorithm)(Array);

    int i;

    //Chon phuong thuc input
    system("cls");

    printf("Chon phuong thuc input:\n");
    printf("1 - Nhap vao tu Terminal\n");
    printf("2 - Doc tu file \"input.txt\" \n");
    printf("3 - Random day so\n");
    printf("Khac - Thoat chuong trinh\n");

    scanf("%d", &i);
    switch (i){
        case 1:
            inputFunction = inputTerminal;
            break;
        case 2:
            inputFunction = inputFile;
            break;
        case 3:
            inputFunction = inputRandom;
            break;
        default:
            return 0;
    }

    //Chon phuong thuc output
    system("cls");

    printf("Chon phuong thuc output:\n");
    printf("1 - In ra Terminal\n");
    printf("2 - Xuat ra file \"output.txt\" \n");
    printf("Khac - Thoat chuong trinh\n");

    scanf("%d", &i);
    switch (i){
        case 1:
            outputFunction = outputTerminal;
            break;
        case 2:
            outputFunction = outputFile;
            break;
        default:
            return 0;
    }

    //Chon thuat toan sap xep
    system("cls");

    printf("Chon thuat toan sap xep:\n");
    printf("1 - Sap xep noi bot (Bubble Sort)\n");
    printf("2 - Sap xep lua chon (Selection Sort)\n");
    printf("3 - Sap xep vun dong (Heap Sort)\n");
    printf("4 - Sap xep nhanh (Quick Sort)\n");
    printf("5 - Sap xep tron (Merge Sort)\n");
    printf("Khac - Thoat chuong trinh\n");

    scanf("%d", &i);
    switch (i){
        case 1:
            sortingAlgorithm = bubbleSort;
            break;
        case 2:
            sortingAlgorithm = selectionSort;
            break;
        case 3:
            sortingAlgorithm = heapSort;
            break;
        case 4:
            sortingAlgorithm = quickSort;
            break;
        case 5:
            sortingAlgorithm = mergeSort;
            break;
        default:
            return 0;
    }

    //Thuc hien chuong trinh chinh
    system("cls");

    Array a = inputFunction();

    clock_t start, end;
    start = clock();
    sortingAlgorithm(a);
    end = clock();

    outputFunction(a);

    double time_taken = (double) (end - start) / (double)(CLOCKS_PER_SEC);
    printf("\nThuat toan voi %d phan tu chay trong: %.9lf giay", a.leng, time_taken);
    
    freeArray(a);
    return 0;
}