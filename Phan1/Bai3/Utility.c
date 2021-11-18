#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

#include "HeaderBai3.h"

//DECLARE
int lineCount = 1;
FILE *inputFile, *stopWordFile;
char c;
char word[WORD_SIZE], stopWord[WORD_SIZE];
int indexInWord = 0;
int isPrevAStopPunctuation = 0;

//FUNCTIONS
void init(char *inputFileName, void (* initStruct)()){
    inputFile = fopen(inputFileName, "r");
    stopWordFile = fopen("stopw.txt", "r");

    if (inputFile == NULL || stopWord == NULL){
        printf("\nFILE KHONG TON TAI!\n");
        fclose(inputFile);
        fclose(stopWordFile);
        exit(EXIT_FAILURE);
    }

    initStruct();
}

void end(void (* endStruct)()){
    fclose(inputFile);
    fclose(stopWordFile);
    endStruct();
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
