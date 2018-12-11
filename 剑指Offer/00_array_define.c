/**
* 数组的定义与初始化
*/
#include<stdio.h>
#include<stdlib.h>
#define N 4

/* 一维数组的定义与初始化 */
void define_arr1() {
    // 定义1
    int a[10] = {1, 2, 3, 4, 6, 7, 8, 9, 10};

    // 定义2: 使用变量来定义数组长度时，数组可定义，却不能同时进行初始化赋值，需要在之后单个赋值。
    int n = 10;
    // int b[n] = {0};

    // 定义3
    const int i = 4;
    int c[i];
    //c[i] = {1, 2, 3, 4};
    int d[N] = {1, 2, 3, 4};

    // 初始化1
    int e[] = {1, 2, 3, 4};

    // 初始化2
    int f[4] = {1, 2};

    // 初始化3
    int g[4] = {0};
}

/* 二维数组的定义与初始化 */
void define_arr2() {

    int a[12] = {1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12};

    // 初始化1
    int aa[3][4] = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } };

    // 初始化2
    int bb[3][4] =  {1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12};

    // 初始化3
    int cc[][4] =  {1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12};

    // 初始化4
    int dd[][4] = {{1}, {5, 6}, {0, 0, 11}};

    // 初始化5
    int ee[3][4] =  {0};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            ee[i][j] = 4 * i + j + 1;
}

/* 函数返回二维数组 */
int **foo(int rows, int columns) {
    // 定义二维数组，并合理申请内存
    int **result = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        result[i] = (int *)malloc(columns * sizeof(int));
    }

    // 初始化
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            result[i][j] = 4 * i + j + 1;

    return result;
}

int main(int argc, char const *argv[]) {
    int **arr2;
    int rows, columns;
    rows = 3;
    columns = 4;

    arr2 = foo(rows, columns);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%3d", arr2[i][j]);
        }
        printf("\n");
    }
    return 0;
}
