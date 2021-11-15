#include <stdio.h>
#include <stdlib.h> //system()
#include <time.h> //clock()
#include <string.h> // strcpy()

#include "HeaderBai3.h"

int main(){
    char inputFileName[50];
    void (* initStruct)();
    void (* endStruct)();
    void (* insertFunction)(char *);
    void (* printStruct)();

    int i;

    system("cls");
    printf("Chon file van ban:\n");
    printf("1 - Doc tu file \"vb.txt\" \n");
    printf("2 - Doc tu file khac\n");

    scanf("%d", &i);
    switch (i){
        case 1:
            strcpy(inputFileName, "vb.txt");
            break;
        default:
            getchar();
            printf("Nhap ten file: ");
            gets(inputFileName);
    }

    printf("\nChon cau truc du lieu luu tru:\n");
    printf("1 - Danh sach lien ket\n");
    printf("2 - Mang bam\n");
    printf("3 - Cay nhi phan tim kiem\n");
    printf("Khac - Thoat chuong trinh\n");

    scanf("%d", &i);
    switch (i){
        case 1:
            initStruct = initLinkedList;
            endStruct = endLinkedList;
            insertFunction = insertWordToLinkedList;
            printStruct = printLinkedList;
            break;
        case 2:
            initStruct = initHashTable;
            endStruct = endHashTable;
            insertFunction = insertWordToHashTable;
            printStruct = printHashTable;
            break;
        case 3:
            initStruct = initBinaryTree;
            endStruct = endBinaryTree;
            insertFunction = insertWordToBinaryTree;
            printStruct = printBinaryTree;
            break;
        default:
            return 0;
    }

    init(inputFileName, endStruct);

    processing(insertFunction);

    printf("\nDanh sach tu:\n");
    printStruct();

    end(endStruct);
    return 0;
}