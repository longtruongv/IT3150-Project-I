#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HeaderBai3.h"

//DECLARE
Node *hashTable[100];

//ALGORITHM
int hashValue(char *str){
    int sum = 0, i;
    for (i = 0; str[i] != '\0'; i++){
        sum += str[i];
    }
    return sum % 100;
}

void insertWordToHashTable(char *str){
    Node *pNode;
    int hv = hashValue(str);
    
    if (hashTable[hv] == NULL || strcmp(hashTable[hv]->keyWord, str) > 0){
        hashTable[hv] = makeNewNode(str, NULL, hashTable[hv]);
    } else if (strcmp(hashTable[hv]->keyWord, str) == 0){
        insertLineToWord(hashTable[hv]);
    } else {
        pNode = hashTable[hv];

        while (pNode->next != NULL && strcmp(pNode->next->keyWord, str) < 0){
            pNode = pNode->next;
        }

        if (pNode->next != NULL && strcmp(pNode->next->keyWord, str) == 0){
            insertLineToWord(pNode->next);
        } else {
            makeNewNode(str, pNode, pNode->next);
        }
    }
}

//PRINT
void printHashTable(){
    soLuongTu = 0;
    soLuongTuLoai = 0;

    for (int i = 0; i < 100; i++){
        Node *pNode = hashTable[i];

        if (pNode != NULL) printf("\n%d\n", i);
        while (pNode != NULL){
            soLuongTu += pNode->count;
            soLuongTuLoai++;
            int countingLine = 0;

            printf("%-31s %d", pNode->keyWord, pNode->count);

            NumNode *pNumNode = pNode->firstLine;
            while (pNumNode != NULL){
                printf(", %d", pNumNode->num);
                countingLine++;
                pNumNode = pNumNode->next;
            }
            printf("\n");

            if (countingLine < pNode->count){
                insertTXHN1D(pNode->keyWord);
            }

            pNode = pNode->next;
        }
    }

    printf("\nSo luong tu: %d\nSo luong tu khac loai: %d\n", soLuongTu, soLuongTuLoai);
    printTXHN1D();
}

//FREE
void freeHashTable(){
    int i;
    for (i = 0; i < 100; i++){
        Node *pCurrNode = hashTable[i];
        Node *pNextNode = NULL;

        while (pCurrNode != NULL){
            pNextNode = pCurrNode->next;
            freeNode(pCurrNode);
            pCurrNode = pNextNode;
        }

        hashTable[i] = NULL;
    }
}

//INIT END
void initHashTable(){
    int i;
    for (i = 0; i < 100; i++){
        hashTable[i] = NULL;
    }
}

void endHashTable(){
    freeHashTable();
}