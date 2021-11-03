#include<stdio.h>
#include<string.h>

#include"Utility.h"

#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct LinkedListNode {
    char* keyWord;
    int count;
    NumNode *firstLine, *lastLine;
    struct LinkedListNode *prev, *next;
} LLNode;

LLNode *linkedListHead;

void insertNewNode(char *str, LLNode *p, LLNode *n){
    LLNode *pNewNode = (LLNode *) malloc(sizeof(LLNode));

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
}

void insertWord(char *str){
    
}

void freeNode(LLNode *pNode){
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
    LLNode *pCurrNode = linkedListHead;
    LLNode *pNextNode = NULL;

    while (pCurrNode != NULL){
        pNextNode = pCurrNode->next;
        free(pCurrNode);
        pCurrNode = pNextNode;
    }

    linkedListHead = NULL;
}

#endif