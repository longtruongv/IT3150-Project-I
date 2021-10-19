#include<stdio.h>
#include <stdlib.h> // rand()
#include <time.h> // time()

//
int n;         //So luong thanh pho
int **graph;   //Chi phi di lai giua 2 thanh pho
int bestCost;  //Tong chi phi tot nhat
int currCost;  //Tong chi phi tinh toi thoi diem hien tai
int *mark;     //Danh dau nhung thanh pho da di
int *cityList; //Danh sach thu tu cac thanh pho da di

void init();
void end();

void inputTerminal();
void inputFile();
void inputRandom();

//Vi bai toan nay khong co rang buoc Implicit
//Nen thuat toan Vet can se giong thuat toan Quay lui
//Thuat toan Vet can




//Thuat toan Nhanh can
void TRY(int k){
    for (int i = 1; i < n; i++){
        if (k == n){
            if (currCost + graph[cityList[n-1], 0] < bestCost){
                
            }
        }

        if (mark[i] == 1) continue;

        cityList[k] = i;
    }
}



int main(){
    void (* input)();
    void (* algorithm)();

    int i;

    //Chon phuong thuc input
    system("cls");

    printf("Chon phuong thuc input:\n");
    printf("1 - Nhap vao tu Terminal\n");
    printf("2 - Doc tu file \"input.txt\" \n");
    printf("3 - Random day so\n");
    printf("Khac - Thoat chuong trinh\n");

    scanf("%d", &i);
    switch (i){
        case 1:
            input = inputTerminal;
            break;
        case 2:
            input = inputFile;
            break;
        case 3:
            input = inputRandom;
            break;
        default:
            return 0;
    }

    //Chon thuat toan
    printf("Chon thuat toan:\n");
    printf("1 - Vet can (Brute Force)\n");
    printf("2 - Sap xep lua chon (Selection Sort)\n");
    printf("Khac - Thoat chuong trinh\n");

    scanf("%d", &i);
    switch (i){
        case 1:
            //algorithm = bf;
            break;
        case 2:
            //algorithm = bt;
            break;
        default:
            return 0;
    }

    input();
    





    for (int i = 0; i < n; i++){
        free(graph[i]);
    }
    free(graph);
    free(mark);
    free(cityList);

    return 0;
} 

void inputTerminal(){
    printf("Nhap so thanh pho: ");
    scanf("%d", &n);

    printf("Nhap ma tran chi phi:\n");
    graph = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++){
        graph[i] = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++){
            scanf("%d", &graph[i][j]);
        }
    }
}

void inputFile(){
    FILE *file;
    file = fopen("input.txt", "r");

    fscanf(file, "%d", &n);

    graph = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++){
        graph[i] = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++){
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);
}

void inputRandom(){
    printf("Nhap so thanh pho: ");
    scanf("%d", &n);

    graph = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++){
        graph[i] = (int *) malloc(n * sizeof(int));
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            graph[i][j] = rand();
            graph[j][i] = graph[i][j];
        }
    }
}
