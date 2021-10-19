//////////////////////////////
// BAI TOAN QUAN MA DI TUAN //
//////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> //sleep()

int graph[8][8];
int result[64];

void init(){

}

void printBoard(){
    int a;
    printf("1. Auto\n2. Manual\n");
    scanf("%d", &a); a--;

    int i = 0, j = 0;
    int step = 0;
    
    while (step < 64){
        system("cls");
        printf ("Ban co: \n\n");
        printf("     A     B     C     D     E     F     G     H  \n");

        while (i < 31){
            if (i % 2 == 0){
                printf("        |     |     |     |     |     |     |     \n");
            } else if (i % 4 == 3){
                printf("   ----- ----- ----- ----- ----- ----- ----- -----\n");
            } else {
                printf("%d  ", ++j);

                //in quan co vao day
                printf("     |     |     |     |     |     |     |     \n");
            }
            i++;
        }
        printf("\n");

        i = 0;
        j = 0;
        step++;
        printf("%d\n", step);
        
        if (a){
            system("pause");
        } else {
            system("cls");
        }
    }
}

int isValidPos(int x, int y){
    return x >= 0 && x <= 8 && y >= 0 && y <= 8;
}

int main(){
    printBoard();
}

