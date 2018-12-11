/* 题目： 找出数组中重复的数字
*  要求：在一个长度为n的数组里的所有数字都在0～n-1的范围内。
*  数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。
*  请找出数组中任意一个重复的数字。例如输入长度为7的数组{2,3,1,0,2,5,3},那么对应的输出为2或3.
*/

#include <stdio.h>

void PrintArray(int data[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", data[i]);
    }
    printf("\n");
}

/* 修改后的直接插入排序 */
void InsertSort(int data[], int length) {
    int i, j;
    int tmp = 0;
    for(i = 1; i < length; i++) {
        if (data[i] < data[i-1]) {      /* 将data[i] 插入有序数组 */
            tmp = data[i];              /* 设置哨兵 */
            for (j = i-1; data[j] > tmp && j >= 0; j--) {  /* 防止j越界 */
                data[j+1] = data[j];    /* 记录后移 */
            }
            data[j+1] = tmp;            /* 插入到正确位置 */
        }
        PrintArray(data, length);
    }
}

/* 先将数组排序， 再遍历。时间复杂度：O(nlogn);空间复杂度：O(1)*/
int find_with_sort(int data[], int length) {
    InsertSort(data, length);
    PrintArray(data, length);

    int tmp = data[0];
    for (int i = 1; i < length; i++) {
        if (tmp == data[i])
            printf("%3d", data[i]);
        else
            tmp = data[i];
    }
    printf("\n");
}

int find_max_of_array(int data[], int length) {
    int max = data[0];
    for (int i = 0; i < length; i++)
        if (max < data[i])
            max = data[i];

    return max;
}
/* 创建哈希表找到重复元素。时间复杂度：O(n),空间复杂度：O(n) */
void find_with_hash(int data[], int length) {
    const int hash_length = length;
    int hashMap[hash_length];
    for (int i = 0; i < length; i++) {
        if (hashMap[data[i]] != data[i])
            hashMap[data[i]] = data[i];
        else
            printf("%3d", data[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[]) {
    int data[] = {2, 3, 1, 0, 2, 5, 3};
    int length = sizeof(data) / sizeof(int);

    /* 方案一： 排序和遍历 */
    find_with_sort(data, length);
    /* 方案二： 利用哈希表查找 */
    find_with_hash(data, length);
    /* 方案三： 重排数组,比较 */
    // find_with_compare(data, length);
    return 0;
}
