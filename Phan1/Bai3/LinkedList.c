#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HeaderBai3.h"

//DECLARE
Node *linkedListHead;

//ALGORITHMS
Node *makeNewNode(char *str, Node *p, Node *n){
    Node *pNewNode = (Node *) malloc(sizeof(Node));
    if (pNewNode == NULL){
        printf("Loi bo nho!");
        return NULL;
    }

    strcpy(pNewNode->keyWord, str);
    pNewNode->count = 1;

    pNewNode->firstLine = (NumNode *) malloc(sizeof(NumNode));
    pNewNode->lastLine = pNewNode->firstLine;
    pNewNode->lastLine->num = lineCount;
    pNewNode->lastLine->next = NULL;

    pNewNode->prev = p;
    pNewNode->next = n;

    if (p != NULL) p->next = pNewNode;
    if (n != NULL) n->prev = pNewNode;

    return pNewNode;
}

void insertLineToWord(Node *pNode){
    pNode->count++;

    if (lineCount == pNode->lastLine->num) return;

    NumNode *pNewNumNode = (NumNode *) malloc(sizeof(NumNode));
    pNewNumNode->num = lineCount;
    pNewNumNode->next = NULL;

    pNode->lastLine->next = pNewNumNode;
    pNode->lastLine = pNewNumNode;
}

void insertWordToLinkedList(char *str){
    Node *pNode;

    if (linkedListHead == NULL || strcmp(linkedListHead->keyWord, str) > 0){
        linkedListHead = makeNewNode(str, NULL, linkedListHead);
    } else {
        pNode = linkedListHead;

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
void printLinkedList(){
    Node *pNode = linkedListHead;
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

//FREE
void freeNode(Node *pNode){
    NumNode *pCurrNumNode = pNode->firstLine;
    NumNode *pNextNumNode = NULL;

    while (pCurrNumNode != NULL){
        pNextNumNode = pCurrNumNode->next;
        free(pCurrNumNode);
        pCurrNumNode = pNextNumNode;
    }

    free(pNode);
}

void freeLinkedList(){
    Node *pCurrNode = linkedListHead;
    Node *pNextNode = NULL;

    while (pCurrNode != NULL){
        pNextNode = pCurrNode->next;
        freeNode(pCurrNode);
        pCurrNode = pNextNode;
    }

    linkedListHead = NULL;
}


//INIT END
void initLinkedList(){
    linkedListHead = NULL;
}

void endLinkedList(){
    freeLinkedList();
}