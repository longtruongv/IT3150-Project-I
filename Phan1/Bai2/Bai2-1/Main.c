//////////////////////////////
// BAI TOAN QUAN MA DI TUAN //
//////////////////////////////

#include<stdio.h>
#include <ctype.h> // toupper()
#include "PrintBoard.h"

//Goc toa do o phia tren ben trai ban co
//Truc Y nam ngang, sang phai, toa do dem tu 0
//Truc X nam doc, xuong duoi, toa do dem tu 0

int mark[8][8]; //danh dau nhung o da di
int step[64][2]; //luu lai toa do cac buoc -> X[k]

//Vi tri cac buoc di tiep theo so voi hien tai
int nextMove[8][2] = {{+1, -2}, {+2, -1}, {+2, +1}, {+1, +2},
                      {-1, +2}, {-2, +1}, {-2, -1}, {-1, -2}};

//Khoi tao
void init(int startRow, int startColumn){
    for (int i = 0; i < 8; i++){
        for  (int j = 0; j < 8; j++){
            mark[i][j] = 0;
        }
    }

    //Thay gia tri de chon vi tri xuat phat khac
    step[0][0] = startRow;
    step[0][1] = startColumn;

    mark[ step[0][0] ][ step[0][1] ] = 1;
}

//Kiem tra xem buoc di tiep theo co hop le
int isNextMoveValid(int stepIndex, int nextMoveIndex){
    int x = step[stepIndex][0] + nextMove[nextMoveIndex][0];
    int y = step[stepIndex][1] + nextMove[nextMoveIndex][1];
    return x >= 0 && x < 8 && y >= 0 && y < 8 && mark[x][y] == 0;
}

//BACKTRACKING
int TRY(int k){
    // for ( [Lan luot tung phuong an] )
    for (int nextMoveIndex = 0; nextMoveIndex < 8; nextMoveIndex++){
        
        // if ( [Thanh cong] ) [Dua ra ket qua]; 
        if (k == 64){
            printBoard(step);
            printf("\nTim duong thanh cong!\n");
            return 0;
        }
        
        // if ( [Phuong an chap nhan duoc] )
        if (!isNextMoveValid(k - 1, nextMoveIndex)) continue;

        //Cap nhat theo phuong an chap nhan duoc
        step[k][0] = step[k-1][0] + nextMove[nextMoveIndex][0];
        step[k][1] = step[k-1][1] + nextMove[nextMoveIndex][1];

        mark[ step[k][0] ][ step[k][1] ] = 1;

        // backtracking(k+1);
        //Khong tiep tuc khi da ra ket qua
        if (TRY(k + 1) == 0) return 0;

        //Bo chon phuong an
        mark[ step[k][0] ][ step[k][1] ] = 0;
    }
    return 1;
}

int main(){
    int startRow, startColumn;
    printf("Ban muon xuat phat tu dau?\n");
    printf("LUU Y: Chon o giua Ban Co tinh toan se RAT LAU!\n");

    do {
        printf("Cot (A - H): ");
        fflush(stdin);
        startColumn = toupper(getchar());
        startColumn -= 65;
    } while (startColumn < 0 || startColumn > 7);
    
    do {
        printf("Hang (1 - 8): "); 
        scanf("%d", &startRow);
        startRow--;
    } while (startRow < 0 || startRow > 7);

    init(startRow, startColumn);

    printf("\nDang tinh toan...\n");
    TRY(1);
    
    return 0;
}

