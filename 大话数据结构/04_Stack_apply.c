/*  栈的应用1：递归
*   递归的理解：两面镜子面对面放着，会产生一连串的“像中像”，这是一种递归现象
*   递归函数的定义：把一个直接调用自身或通过一系列的调用语句间接地调用自身的函数，称作递归函数。
*   条件：每个递归定义必须至少有一个条件，满足时递归不再执行，即不再引用自身而是返回值退出。
*/
/* 经典的递归例子： 斐波那契数列（Fibonacci）
*   函数表示：            0, n = 0
*           F(n) =      1, n = 1
*                       F(n-1) + F(n+1), n > 1
*/
#include <stdio.h>
/*  常规迭代法实现
    int a[40];
    a[0] = 0;
    a[1] = 1;
    for (int i = 0; i < 40; i++) {
        a[i] = a[i-1] + a[i-2];
    }
*/
/*
    迭代和递归的区别是：迭代使用的是循环结构，递归使用的是选择结构。
    递归：结构更清晰、更简洁，更容易理解。但大量的递归会建立函数的副本，耗费大量的时间和内存。
    迭代：不需要反复调用函数和占用额外的内存。
    应视不同的情况选择不同的代码实现方式
*/
/* 斐波那契数列的递归实现 */
int Fbi(int i) {
    if (i < 2)
        return i == 0 ? 0 : 1;
    return Fbi(i-1) + Fbi(i-2);     // 调用自身
}

/* 栈的应用2：四则运算表达式求值
*   表达式求解法则：先乘除，后加减，从左到右，先括号内后括号外
*   括号的实现思路： 括号是成对出现的，有左括号就一定有右括号。用栈结构正合适：
*       遇到左括号就进栈，出现右括号就让栈顶的左括号出栈。
*   四则运算的实现思路： 一种不需要括号的后缀表达法：逆波兰(Reverse Polish Notation, RPN)表示
*/
/*  逆波兰表达式求解四则运算
    1. 中缀表达式(9+(3-1)*3+10/2) 转 后缀表达式("9 3 1 - 3 × + 10 2 / +")：
        用法：栈用来进出运算的符号
        规则：从左到右遍历中缀表达式的每个数字和符号，若是数字就输出，即成为后缀表达式的一部分；
            若是符号，则判断其与栈顶符号的优先级，是右括号或优先级低于栈顶符号(乘除优于加减)，
            则栈顶元素依次出栈并输出，并将当前符号进栈，一直到最终输出后缀表达式为止。

    2. 后缀表达式计算："9 3 1 - 3 × + 10 2 / +"
        用法：栈用来进出运算的数字
        规则：从左到右遍历表达式的每个数字和符号，遇到数字就进栈，遇到符号，就将栈顶的两个数字出栈，进行运算，运算结果进栈。
*/

int main(int argc, char const *argv[]) {
    for (int i = 0; i < 40 ; i++) {
        printf("Fbi[%d]:%d\n", i, Fbi(i));
    }
    return 0;
}
