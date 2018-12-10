/*
*
* 题目： 在一个二维数组中(每个一维数组的长度相同)，每行都按照从左到右递增的顺序排序，
* 每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，
* 判断数组中是否有该整数。
*/

#include<stdio.h>

// 解法1：对于从左下到右上的对角线上的所有元素来说，该元素上面的元素依次递减，右面的元素依次递增。
// 因此可从左下角开始遍历地比较元素(避免进入交叉路口)：若大于目标值，向上走；若小于目标值，向右走。
int Find(int target, int[][] array) {
    int len = array.length - 1;
    int i = 0;
    while ((len >= 0) && (i < array[0].length)) {
        if (array[len][i] > target) {
            len--;
        }else if (array[len][i] < target) {
            i++;
        }else{
            return true;
        }
    }
    return false;
}

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}
