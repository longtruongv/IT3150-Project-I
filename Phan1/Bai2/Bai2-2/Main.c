#include <stdio.h>
#include <stdlib.h> // rand()
#include <time.h> // time()

int n;              //So luong thanh pho
int **graph;        //Chi phi di lai giua 2 thanh pho
int minWeight;      //Chi phi di lai nho nhat tu mot thanh pho bat ky ve 0
int bestCost;       //Tong chi phi tot nhat
int currCost;       //Tong chi phi tinh toi thoi diem hien tai
int *mark;          //Danh dau nhung thanh pho da di
int *cityList;      //Danh sach thu tu cac thanh pho da di
int *minCityList;   //Danh sach thu tu cac thanh pho voi chi phi nho nhat

void init();
void end();

void inputTerminal();
void inputFile();
void inputRandom();


////////////////////////
// Thuat toan Vet can //
////////////////////////

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Tim ra hoan vi tiep theo cua cityList
//return 1 neu tim ra hoan vi tiep theo
//return 0 neu la hoan vi cuoi cung
int nextPermutation(){
    //Tim vi tri lon nhat thoa man arr[i] < arr[i+1]
    int i = n - 2;
    while (i >= 0 && cityList[i] > cityList[i+1]){
        i--;
    }

    //Neu khong ton tai vi tri -> hoan vi cuoi cung
    //O day ta chi xet hoan vi phan tu thu 1 toi thu n-1
    //Phan tu dau tien luon la xuat phat nen khong xet hoan vi
    if (i == 0) return 0;

    //Tim vi tri lon nhat ma gia tri lon hon gia tri tai i
    int j = n - 1;
    while (cityList[j] <= cityList[i]){
        j--;
    }

    //Doi cho gia tri o 2 vi tri tren
    swap(cityList + i, cityList + j);

    //Tu sau vi tri i o tren, ta lat nguoc cac gia tri
    i++; j = n - 1;
    while (i < j){
        swap(cityList + i, cityList + j);
        i++; j--;
    }

    //Tim duoc hoan vi tiep theo
    return 1;
}

void bruteForce(){
    bestCost = INT_MAX;
    currCost = 0;

    for (int i = 0; i < n; i++){
        cityList[i] = i;
    }

    do {
        //Tinh toan chi phi theo mot hoan vi
        for (int i = 0; i < n - 1; i++){
            currCost += graph[ cityList[i] ][ cityList[i + 1] ];
        }
        currCost += graph[ cityList[n-1] ][0];

        //Kiem tra co phai chi phi toi uu
        if (currCost < bestCost){
            bestCost = currCost;
            for (int j = 0; j < n; j++){
                minCityList[j] = cityList[j];
            }
        }

        currCost = 0;
    } while (nextPermutation());
    
    printf("\nChi phi nho nhat: %d\n", bestCost);
    printf("Cach di chuyen chi phi nho nhat:\n");
    for (int i = 0; i < n; i++){
        printf("%d -> ", minCityList[i] + 1);
    }
    printf("1\n");
}
//end thuat toan Vet can


//////////////////////////
// Thuat toan Nhanh can //
//////////////////////////

void tryBranchAndBound(int k){
    if (k == n){
        currCost += graph[cityList[k-1]][0];
        if (currCost < bestCost){
            bestCost = currCost;
            for (int j = 0; j < n; j++){
                minCityList[j] = cityList[j];
            }
        }
        currCost -= graph[cityList[k-1]][0];
        return;
    }

    for (int i = 1; i < n; i++){
        if (mark[i]) continue;

        cityList[k] = i;
        mark[i] = 1;
        currCost += graph[cityList[k-1]][i];
        
        if (currCost + minWeight * (n - k + 1) < bestCost)
            tryBranchAndBound(k + 1);

        mark[i] = 0;
        currCost -= graph[cityList[k-1]][i];
    }
}

void branchAndBound(){
    bestCost = INT_MAX;
    currCost = 0;

    cityList[0] = 0;
    mark[0] = 1;

    tryBranchAndBound(1);
    
    printf("\nChi phi nho nhat: %d\n", bestCost);
    printf("Cach di chuyen chi phi nho nhat:\n");
    for (int i = 0; i < n; i++){
        printf("%d -> ", minCityList[i] + 1);
    }
    printf("1\n");
}
//end thuat toan Nhanh can


int main(){
    void (* input)();
    void (* algorithm)();

    int i;

    //Chon phuong thuc input
    system("cls");

    printf("Chon phuong thuc input:\n");
    printf("1 - Nhap vao tu Terminal\n");
    printf("2 - Doc tu file \"input.txt\" \n");
    printf("3 - Random\n");
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
    printf("\nChon thuat toan:\n");
    printf("1 - Vet can (Brute Force)\n");
    printf("2 - Nhanh can (Branch and Bound)\n");
    printf("Khac - Thoat chuong trinh\n");

    scanf("%d", &i);
    switch (i){
        case 1:
            algorithm = bruteForce;
            break;
        case 2:
            algorithm = branchAndBound;
            break;
        default:
            return 0;
    }

    init(input);

    printf("\nDang tinh toan...\n");

    clock_t start, stop;
    start = clock();
    algorithm();
    stop = clock();

    double time_taken = (double) (stop - start) / (double)(CLOCKS_PER_SEC);
    printf("\nThuat toan voi %d thanh pho chay trong: %.9lf giay", n, time_taken);

    end();
    return 0;
} 

void init(void (* input)()){
    input();

    mark = (int *) malloc(n * sizeof(int));
    cityList = (int *) malloc(n * sizeof(int));
    minCityList = (int *) malloc(n * sizeof(int));

    minWeight = INT_MAX;
    for (int i = 0; i < n; i++){
        mark[i] = 0;

        for (int j = i + 1; j < n; j++){
            if (graph[i][j] < minWeight) minWeight = graph[i][j];
        }
    }
}

void end(){
    for (int i = 0; i < n; i++){
        free(graph[i]);
    }
    free(graph);

    free(mark);
    free(cityList);
    free(minCityList);
}

void inputTerminal(){
    printf("\nNhap so thanh pho: ");
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
    printf("\nNhap so thanh pho: ");
    scanf("%d", &n);

    graph = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++){
        graph[i] = (int *) malloc(n * sizeof(int));
    }

    srand(time(NULL));
    for (int i = 0; i < n; i++){
        graph[i][i] = 0;
        for (int j = i + 1; j < n; j++){
            graph[i][j] = rand();
            graph[j][i] = graph[i][j];
        }
    }

    printf("Ma tran chi phi:\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%7d", graph[i][j]);
        }
        printf("\n");
    }
}
