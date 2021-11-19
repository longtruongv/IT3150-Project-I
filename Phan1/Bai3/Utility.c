#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

#include "HeaderBai3.h"

//DECLARE
int lineCount = 1;
int soLuongTu = 0, soLuongTuLoai = 0;
TXHN1D *dsTXHN1D = NULL;
TXHN1D *lastTXHN1D = NULL;

FILE *inputFile, *stopWordFile;
char c;
char word[WORD_SIZE], stopWord[WORD_SIZE];
int indexInWord = 0;
int isPrevAStopPunctuation = 0;

//FUNCTIONS
void init(char *inputFileName, void (* initStruct)()){
    inputFile = fopen(inputFileName, "r");
    stopWordFile = fopen("stop_words_english.txt", "r");

    if (inputFile == NULL || stopWord == NULL){
        printf("\nFILE KHONG TON TAI!\n");
        fclose(inputFile);
        fclose(stopWordFile);
        exit(EXIT_FAILURE);
    }

    initStruct();
}

void endTXHN1D();
void end(void (* endStruct)()){
    fclose(inputFile);
    fclose(stopWordFile);
    endStruct();
    endTXHN1D();
}

int isStopWord(char *lowerCaseWord){
    rewind(stopWordFile);
    while (fscanf(stopWordFile, "%s", stopWord) != EOF){
        if (strcmp(lowerCaseWord, stopWord) == 0) return 1;
    }
    return 0;
}

int isEndingPunctuation(char c){
    switch (c){
        case '.':
        case '!':
        case '?':
            return 1; 
        default:
            return 0;
    }
}

void processing(void (* insertFunc)(char *)){
    while ((c = fgetc(inputFile)) != EOF){
        if (isalpha(c)){
            if (isPrevAStopPunctuation){
                c = tolower(c);
                isPrevAStopPunctuation = 0;
            }

            word[indexInWord] = c;
            indexInWord++;
            continue;
        } else {
            word[indexInWord] = '\0';
            indexInWord = 0;

            if (word[0] != '\0' && !isupper(word[0])) {
                for (int i = 1; word[i]; i++){
                    word[i] = tolower(word[i]);
                }

                if (!isStopWord(word)){
                    insertFunc(word);   
                }
            }

            if (c == '\n'){
                lineCount++;
            } else if (isEndingPunctuation(c)) {
                isPrevAStopPunctuation = 1;
            }
        }
    }
}



void insertTXHN1D(char *keyWord){
    TXHN1D *newTXHN1D = (TXHN1D *) malloc(sizeof(TXHN1D));
    strcpy(newTXHN1D->keyWord, keyWord);
    newTXHN1D->next = NULL;

    if (dsTXHN1D == NULL) {
        dsTXHN1D = newTXHN1D;
    } else {
        lastTXHN1D->next = newTXHN1D;
    }

    lastTXHN1D = newTXHN1D;
}

void endTXHN1D(){
    TXHN1D *pCurr = dsTXHN1D, *pNext = NULL;

    while (pCurr != NULL){
        pNext = pCurr->next;
        free(pCurr);
        pCurr = pNext;
    }

    dsTXHN1D = NULL;
}

void printTXHN1D(){
    TXHN1D *ptr = dsTXHN1D;
    printf("\nDanh sach cac tu xuat hien nhieu 1 dong:\n");

    while (ptr != NULL){
        printf ("%-31s\n", ptr->keyWord);
        ptr = ptr->next;
    }
}
