/* 题目： 找出数组中重复的数字
*  要求：在一个长度为n的数组里的所有数字都在0～n-1的范围内。
*  数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。
*  请找出数组中任意一个重复的数字。例如输入长度为7的数组{2,3,1,0,2,5,3},那么对应的输出为2或3.
*/

#include <stdio.h>

typedef enum{
    true,
    false
} bool;

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
bool find_with_sort(int data[], int length) {
    // 鲁棒性代码：错误处理，特殊输入
    if (data == NULL || length <= 0) {
        return false;
    }
    // 高质量代码： 边界条件
    for (int i = 0; i < length; i++) {
        if (data[i] < 0 || data[i] > length - 1)
            return false;
    }

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

    return true;
}

int find_max_of_array(int data[], int length) {
    int max = data[0];
    for (int i = 0; i < length; i++)
        if (max < data[i])
            max = data[i];

    return max;
}
/* 创建哈希表找到重复元素。时间复杂度：O(n),空间复杂度：O(n) */
bool find_with_hash(int data[], int length) {
    // 鲁棒性代码：错误处理，特殊输入
    if (data == NULL || length <= 0) {
        return false;
    }
    // 高质量代码： 边界条件
    for (int i = 0; i < length; i++) {
        if (data[i] < 0 || data[i] > length - 1)
            return false;
    }
    PrintArray(data, length);
    const int hash_length = length;
    int hashMap[hash_length];
    for (int i = 0; i < length; i++) {
        if (hashMap[data[i]] != data[i])
            hashMap[data[i]] = data[i];
        else
            printf("%3d", data[i]);
    }
    printf("\n");

    return true;
}

/* 重排数组：从头到尾依次扫描整个数组的每个数字，比较是否和下标相等 */
// 总的时间复杂度是O(n),空间复杂度是O(1)
bool find_with_resort(int data[], int length, int* duplication) {
    // 鲁棒性代码：错误处理，特殊输入
    if (data == NULL || length <= 0) {
        return false;
    }
    // 高质量代码： 边界条件
    for (int i = 0; i < length; i++) {
        if (data[i] < 0 || data[i] > length - 1)
            return false;
    }
    PrintArray(data, length);
    for (int i = 0; i < length; i++) {
        while (data[i] != i) {
            PrintArray(data, length);
            if (data[i] == data[data[i]]) {
                *duplication = data[i];
                return true;
            }
            // swap data[i] and data[data[i]]
            int temp = data[i];
            data[i] = data[temp];
            data[temp] = temp;
        }
    }
    return true;
}

int main(int argc, char const *argv[]) {
    // 测试用例1:长度为n的数组里包含一个或多个重复的数字
    int data1[] = {2, 3, 1, 0, 2, 5, 3};
    // 测试用例2：数组中不包含重复的数字
    int data2[] = {2, 3, 1, 0, 4, 5, 6};
    // 测试用例3：无效输入用例(输入空指针；长度为n的数组中包含0～n-1以外的数字)
    int data3[] = {2, 3, 1, 0, 7, 9, 3};
    int length = sizeof(data1) / sizeof(int);

    /* 方案一： 排序和遍历 */
    printf("find_with_sort:\n");
    bool x = find_with_sort(data3, length);
    /* 方案二： 利用哈希表查找 */
    printf("find_with_hash:\n");
    bool y = find_with_hash(data2, length);
    /* 方案三： 重排数组,比较 */
    int num;
    printf("find_with_resort:\n");
    if (find_with_resort(data1, length, &num) == true) {
         printf("repeatable num:%d\n", num);
    }
    return 0;
}
