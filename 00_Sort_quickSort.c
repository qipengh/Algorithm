/** 快速排序
*  基本思想：通过一趟排序将待排序记录分割车成独立的两部分，一部分记录的关键字比另一部分记录
*     的关键字小，则迭代地对两部分的记录进行排序，以达到整个序列有序的目的
*  复杂度分析(递归树)：
*     时间：最优 O(nlogn), 最坏O(n^2), 平均 O(nlogn)
*     空间：最优 O(logn), 最坏O(n), 平均 O(logn)
*  稳定性： 不稳定
*/

#include<stdio.h>

#define MAXSIZE 20      /* 存储空间初始分配量 */
typedef int ElemType;   /* ElemType 类型根据实际情况而定 */
typedef struct
{
    ElemType data[MAXSIZE]; /* 数组存储数据元素， 最大值为 MAXSIZE */
    int length;             /* 线性表当前长度 */
}SqList;


void swap(SqList *L, int x, int y) {
    int tmp;
    tmp = L->data[x];
    L->data[x] = L->data[y];
    L->data[y] = tmp;
}

/* 交换顺序表 L 中子表的记录， 使枢轴记录到位，并返回其所在位置 */
/* 此时在它之前（后）的记录均不大（小）于它。 */
int Partition(SqList *L, int low, int high)
{
    int pivotkey;
    pivotkey = L->data[low];
    while (low < high) {
        while (low < high && L->data[high] >= pivotkey) high--;
        swap(L, low, high);             /* 比枢轴小的值交换到低端 */
        while (low < high && L->data[low] <= pivotkey) low++;
        swap(L, low, high);             /* 比枢轴大的值交换到高端 */
    }
    return low;                     /* 返回枢轴所在的位置 */
}

/* 对顺序表 L 中的子序列 L->data[low..high] 作快速排序*/
void QSort (SqList *L, int low, int high) {
    int pivot;
    if (low < high) {
        pivot = Partition(L, low, high);    /* 将 L->data[row..high] 一分为二 , 算出枢轴值 pivot.*/
        QSort(L, low, pivot-1);             /* 对低子表递归排序 */
        QSort(L, pivot+1, high);            /* 对高子表递归排序 */
    }
}

/* 对顺序表 L 作直接插入排序 */
void InsertSort(SqList *L) {
    int i, j;
    for (i = 2; i <= L->length; i++) {
        if (L->data[i] < L->data[i-1]) {    /* 需将 L->data[i] 插入有序表 */
            L->data[0] = L->data[i];        /* 设置哨兵 */
            for (j = i-1; L->data[j] > L->data[0]; j--)
                L->data[j+1] = L->data[j];  /* 记录后移 */
            L->data[j+1] = L->data[0];      /* 插入到正确位置 */
        }
    }
}

/* 快速排序优化算法 */

/* 1. 优化选取枢轴：排序速度的快慢取决于L.data[1]的关键字处在整个序列的位置 */
/* 优化方法： 随机选取法(不稳定)， 三数取中法(左中右)，九数取中法(适合大序列)*/
/* 2. 优化不必要的交换： 不需要交换枢轴 */

int Partition_Optimum(SqList *L, int low, int high)
{
    int pivotkey;
    /* 三数取中法(median-of-three): start */
    int m = low + (high - low) / 2; /* 计算数组中间元素的下标 */
    if (L->data[low] > L->data[high])
        swap(L, low, high);         /* 交换左端与右端数据， 保证左端较小 */
    if (L->data[m] > L->data[high])
        swap(L, high, m);           /* 交换中间与右端数据， 保证中间较小 */
    if (L->data[m] > L->data[low])
        swap(L, m, low);            /* 交换中间与左端数据， 保证左端较小 */
    /* 此时 L.data[low] 已经是整个序列左中右三个关键字的中间值。 */
    /* 三数取中法(median-of-three): end */

    pivotkey = L->data[low];
    /* 替换代替交换： start */
    L->data[0] = pivotkey;                  /* 将枢轴关键字备份到L->data[0] */
    while (low < high) {
        while (low < high && L->data[high] >= pivotkey) high--;
        // swap(L, low, high);              /* 比枢轴小的值交换到低端 */
        L->data[low] = L->data[high];       /* 采用替换而不是交换的方式进行操作 */
        while (low < high && L->data[low] <= pivotkey) low++;
        // swap(L, low, high);              /* 比枢轴大的值交换到高端 */
        L->data[high] = L->data[low];       /* 采用替换而不是交换的方式进行操作 */
    }
    L->data[low] = L->data[0];              /* 将枢轴数值替换回L.data[low]*/
    /* 替换代替交换： end */
    return low;                             /* 返回枢轴所在的位置 */
}

/* 3. 优化小数组时的排序方案： 解决大材小用问题 */
/* 数组较小时， 快速排序(使用了递归)不如直接插入排序 (直接插入排序时简单排序中性能最好的) */

#define MAX_LENGTH_INSERT_SORT 7    /* 最优数组长度阈值：7 或是 50 */
/* 对顺序表 L 中的子序列 L->data[low..high] 作快速排序*/
void QSort_Optimum_SetThreshold (SqList *L, int low, int high) {
    int pivot;
    if ((high - low) > MAX_LENGTH_INSERT_SORT) {
        /* 当high-low 大于常数时用快速排序 */
        pivot = Partition_Optimum(L, low, high);    /* 利用三数取中法，算出枢轴值 pivot. 并用替换法排序*/
        QSort(L, low, pivot-1);                     /* 对低子表递归排序 */
        QSort(L, pivot+1, high);                    /* 对高子表递归排序 */
    }
    else    /* 当high - low 小于等于常数时用直接插入排序 */
        InsertSort(L);
}

/* 4.优化递归操作：减少递归调用，提高性能 */
/* 对QSort实施尾递归优化 */
/* 对顺序表 L 中的子序列 L->data[low..high] 作快速排序*/
void QSort_Optimum_TailRecursion (SqList *L, int low, int high) {
    int pivot;
    if ((high - low) > MAX_LENGTH_INSERT_SORT) {
        while (low < high) {
            // pivot = Partition(L, low, high);    /* 将 L->data[row..high] 一分为二 , 算出枢轴值 pivot.*/
            pivot = Partition_Optimum(L, low, high);    /* 利用三数取中法，算出枢轴值 pivot. 并用替换法排序*/
            QSort_Optimum_TailRecursion(L, low, pivot-1);   /* 对低子表递归排序 */
            low = pivot + 1;                                /* 尾递归 */
        }
    }
    else
        InsertSort(L);
}

/* 对顺序表L作快速排序 */
void QuickSort (SqList *L) {
    // QSort(L, 1, L->length);         /* 1.调用原始快速排序算法 */
    // QSort_Optimum_SetThreshold(L, 1, L->length);   /* 2.优化选择快速或是直接插入排序 */
    QSort_Optimum_TailRecursion(L, 1, L->length);       /* 3.尾递归优化算法 */
}

void PrintValue(SqList *L, int start, int length) {
    for (int i = 0; i < L->length; i++) {
        printf("%3d ", L->data[i+start]);
    }
    printf("\n");
    printf("length: %d\n", L->length);
}


int main(int argc, char const *argv[]) {
    SqList *L;
    SqList L1 = {{0, 50, 10, 90, 30, 70, 40, 80, 60, 20}, 9};
    // L.length = 9;
    // L.data = {50, 10, 90, 30, 70, 40, 80, 60, 20};  /* error: 声明后的结构体数组只能一个一个赋值 */
    L = &L1;

    QuickSort(L);
    PrintValue(L, 1, L->length);
    return 0;
}
