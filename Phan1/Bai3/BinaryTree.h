#include<stdio.h>
#include"Utility.h"

#ifndef BINARY_TREE
#define BINARY_TREE

typedef struct Node {
    char* keyWord;
    int count;
    NumNode *firstLine, *lastLine;
    struct Node *parent, *leftChild, *rightChild;
} Node;

#endif
