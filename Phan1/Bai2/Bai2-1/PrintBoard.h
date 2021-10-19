#include<stdio.h>
#include<stdlib.h> //system()
#include<unistd.h> //sleep()

#ifndef PRINT_BOARD
#define PRINT_BOARD

void printBoard(int step[64][2]){
    int a;
    printf("\nCac buoc se xuat hien nhu the nao?\n");
    printf("0. Auto\n1. Manual\n");
    scanf("%d", &a);

    //line la dong in ra man hinh, KHONG PHAI la hang cua Ban Co
    //row la hang cua Ban Co
    int line = 0, row = 0;

    int stepIndex = 0; //Chi so buoc di hien tai

    char board[8][8]; //Danh dau cac buoc di tren ban co
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){  
            board[i][j] = ' ';
        }

        board[ step[0][0] ][ step[0][1] ] = 'X';
    }
    
    while (stepIndex < 64){
        system("cls");
        printf("\n     A     B     C     D     E     F     G     H  \n\n");

        while (line < 31){
            if (line % 2 == 0){
                printf("        |     |     |     |     |     |     |     \n");
            } else if (line % 4 == 3){
                printf("   ----- ----- ----- ----- ----- ----- ----- -----\n");
            } else {
                printf("%d  ", row + 1);

                //in quan co vao day
                printf("  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  |  %c  \n",
                    board[row][0], board[row][1], board[row][2], board[row][3],
                    board[row][4], board[row][5], board[row][6], board[row][7]);

                row++;
            }
            line++;
        }
        printf("\nThuc hien buoc di: %c %d\n", step[stepIndex][1] + 65, step[stepIndex][0] + 1);
        if (stepIndex > 0) printf("Buoc di truoc do:  %c %d\n", step[stepIndex-1][1] + 65, step[stepIndex-1][0] + 1);

        line = 0;
        row = 0;

        stepIndex++;
        board[ step[stepIndex][0] ][ step[stepIndex][1] ] = 'X';

        if (a){
            system("pause");
        } else {
            sleep(1);
        }
    }
}

#endif