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
    } else {
        pNode = hashTable[hv];

        while (pNode->next != NULL && strcmp(pNode->keyWord, str) < 0){
            pNode = pNode->next;
        }

        if (strcmp(pNode->keyWord, str) == 0){
            insertLineToWord(pNode);
        } else {
            makeNewNode(str, pNode, pNode->next);
        }
    }
}

//PRINT
void printHashTable(){
    int i;
    for (int i = 0; i < 100; i++){
        Node *pNode = hashTable[i];
        while (pNode != NULL){
            printf("%s %d", pNode->keyWord, pNode->count);

            NumNode *pNumNode = pNode->firstLine;
            while (pNumNode != NULL){
                printf(", %d", pNumNode->num);
                pNumNode = pNumNode->next;
            }
            printf("\n");

            pNode = pNode->next;
        }
    }
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