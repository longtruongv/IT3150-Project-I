#include<stdio.h>
#include"Utility.h"

#ifndef HASH_TABLE
#define HASH_TABLE

typedef struct Node {
    char* keyWord;
    int count;
    NumNode *firstLine, *lastLine;
    struct Node *prev, *next;
} Node;

Node *HashTale[100];

#endif