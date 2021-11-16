#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HeaderBai3.h"

//DECLARE
typedef struct TreeNode {
    char keyWord[WORD_SIZE];
    int count;
    NumNode *firstLine, *lastLine;
    struct TreeNode *parent, *leftChild, *rightChild;
} TreeNode;

TreeNode *treeRoot;

//ALGORITHM
TreeNode *makeNewTreeNode(char *str, TreeNode *parent){
    TreeNode *pNewTreeNode = (TreeNode *) malloc(sizeof(TreeNode));
    if (pNewTreeNode == NULL){
        printf("Loi bo nho!");
        return NULL;
    }

    strcpy(pNewTreeNode->keyWord, str);
    pNewTreeNode->count = 1;

    pNewTreeNode->firstLine = (NumNode *) malloc(sizeof(NumNode));
    pNewTreeNode->lastLine = pNewTreeNode->firstLine;
    pNewTreeNode->lastLine->num = lineCount;
    pNewTreeNode->lastLine->next = NULL;

    pNewTreeNode->parent = parent;
    pNewTreeNode->leftChild = NULL;
    pNewTreeNode->rightChild = NULL;

    return pNewTreeNode;
}

void insertLineToWordInTree(TreeNode *pTreeNode){
    pTreeNode->count++;

    if (lineCount == pTreeNode->lastLine->num) return;

    NumNode *pNewNumNode = (NumNode *) malloc(sizeof(NumNode));
    pNewNumNode->num = lineCount;
    pNewNumNode->next = NULL;

    pTreeNode->lastLine->next = pNewNumNode;
    pTreeNode->lastLine = pNewNumNode;
}

void insertWordToBinaryTree(char *str){
    TreeNode *pCurrTreeNode, *pPrevTreeNode;
    int temp;

    if (treeRoot == NULL){
        treeRoot = makeNewTreeNode(str, NULL);
    } else {
        pCurrTreeNode = treeRoot;
        while (pCurrTreeNode != NULL){
            pPrevTreeNode = pCurrTreeNode;

            temp = strcmp(pCurrTreeNode->keyWord, str);
            if (temp > 0){
                pCurrTreeNode = pCurrTreeNode->leftChild;
            } else if (temp < 0){
                pCurrTreeNode = pCurrTreeNode->rightChild;
            } else {
                insertLineToWordInTree(pCurrTreeNode);
                return;
            }
        }

        if (temp > 0){
            pPrevTreeNode->leftChild = makeNewTreeNode(str, pPrevTreeNode);
        } else {
            pPrevTreeNode->rightChild = makeNewTreeNode(str, pPrevTreeNode);
        }
    }
}

//PRINT
void printTreeNode(TreeNode *pTreeNode){
    if (pTreeNode == NULL) return;

    printTreeNode(pTreeNode->leftChild);

    soLuongTu += pTreeNode->count;
    soLuongTuLoai++;
    
    printf("%-31s %d", pTreeNode->keyWord, pTreeNode->count);
    NumNode *pNumNode = pTreeNode->firstLine;
    while (pNumNode != NULL){
        printf(", %d", pNumNode->num);
        pNumNode = pNumNode->next;
    }
    printf("\n");

    printTreeNode(pTreeNode->rightChild);
}

void printBinaryTree(){
    soLuongTu = 0;
    soLuongTuLoai = 0;

    printTreeNode(treeRoot);

    printf("\nSo luong tu: %d\nSo luong tu khac loai: %d\n", soLuongTu, soLuongTuLoai);
}

//FREE
void freeTreeNode(TreeNode *pTreeNode){
    if (pTreeNode == NULL) return;

    freeTreeNode(pTreeNode->leftChild);
    freeTreeNode(pTreeNode->rightChild);

    NumNode *pCurrNumNode = pTreeNode->firstLine;
    NumNode *pNextNumNode = NULL;

    while (pCurrNumNode != NULL){
        pNextNumNode = pCurrNumNode->next;
        free(pCurrNumNode);
        pCurrNumNode = pNextNumNode;
    }

    free(pTreeNode);
}

void freeBinaryTree(){
    freeTreeNode(treeRoot);
}

//INIT END
void initBinaryTree(){
    treeRoot = NULL;
}

void endBinaryTree(){
    freeBinaryTree();
}
