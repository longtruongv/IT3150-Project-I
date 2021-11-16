#ifndef UTILITY
#define UTILITY

#define WORD_SIZE 30

typedef struct NumberNode {
    int num;
    struct NumberNode *next;
} NumNode;

extern int lineCount;
extern int soLuongTu, soLuongTuLoai;

void init(char *inputFileName, void (* initStruct)());
void end(void (* endStruct)());

void processing(void (* insertFunction)(char *));

typedef struct tuXuatHienNhieu1Dong{
    char keyWord[WORD_SIZE];
    struct tuXuatHienNhieu1Dong *next;    
} TXHN1D;

extern TXHN1D *dsTXHN1D;
extern TXHN1D *lastTXHN1D;

void insertTXHN1D();
void printTXHN1D();

#endif


#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct Node {
    char keyWord[WORD_SIZE];
    int count;
    NumNode *firstLine, *lastLine;
    struct Node *prev, *next;
} Node;

Node *makeNewNode(char *str, Node *p, Node *n);
void insertLineToWord(Node *pNode);
void freeNode(Node *pNode);

void insertWordToLinkedList(char *str);
void printLinkedList();
void initLinkedList();
void endLinkedList();

#endif


#ifndef HASH_TABLE
#define HASH_TABLE

void insertWordToHashTable(char *str);
void printHashTable();
void initHashTable();
void endHashTable();

#endif


#ifndef BINARY_TREE
#define BINARY_TREE

void insertWordToBinaryTree(char *str);
void printBinaryTree();
void initBinaryTree();
void endBinaryTree();

#endif



