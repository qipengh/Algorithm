#include <stdio.h>

/*
    串(string)是由零个或多个字符组成的有限序列，又名字符串。
    ADT 串 (string)
    Data
        串中元素仅由一个字符组成，相邻元素具有前驱和后继关系。
    Operation
        StrAssign(T, *chars)    : 生成一个其值等于字符串常量chars的串T。
        StrCopy(T, S)           : 串S存在，由串S复制得串T。
        ClearString(S)          : 串S存在，将串清空。
        StringEmpty(S)          : 若串S为空，返回true,否则返回false。
        StrLength(S)            : 返回串S的元素个数，即串的长度。
        StrCompare(S, T)        : 若S>T，返回值>0,若S=T,返回0，若S<T，返回值>0。
        Concat(T, S1, S2)       : 用T返回由S1和S2联接而成的新串。
        SubString(Sub, S, pos, len) : 串S存在，1 <= pos <= StrLength(S)，
                                        且0 <= len <= StrLength(S) - pos + 1,
                                        用Sub返回串S的第pos个字符起长度为len的子串。
        Index(S, T, pos)        : 串S和T存在，T是非空串，1 <= pos <= StrLength(S)。
                                    若主串S中存在和串T值相同的子串，则返回它在主串S中
                                    第pos个字符之后第一次出现的位置，否则返回0。
        Replace(S, T, V)        : 串S、T和V存在，T是非空串。用V替换主串S中出现的
                                    所有与T相等的不重叠的子串。
        StrInsert(S, pos, T)    : 串S和T存在, 1 <= pos <= StrLength(S) + 1。
                                    在串S的第pos个字符之前插入串T。
        StrDelete(S, pos, len)  : 串S存在，1 <= pos <= StrLength(S) - len + 1,
                                    从串S中删除第pos个字符起长度为len的子串。
    endADT
*/

/* 查找子串 */
int Index(String S, String T, int pos)
{
    int n, m, i;
    String sub;
    if (pos > 0) {
        n = StrLength(S);   // 得到主串S的长度
        m = StrLength(T);   // 得到子串T的长度
        i = pos;
        while (i <= n-m+1) {
            SubString(sub, S, i, m);        // 取主串第i个位置，长度与T相等子串给sub
            if (StrCompare(sub, T) != 0)    // 若两串不相等
                ++i;
            else
                return i;                   // 若两串相等，则返回i值。
        }
    }

    return 0;   // 若无子串与T相等，返回0
}

/* 子串的定位操作：串的模式匹配
*   返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数返回值为0.
*   条件： T非空，1 <= pos <= StrLength(S)
*/
int Index_sample(String S, String T, int pos)
{
    int i = pos;    // i用于主串S中当前位置下标，若pos不为1， 则从pos位置开始匹配。
    int j = 1;      // j 用于子串T中当前位置下标值。
    while (i <= S[0]  && j <= T[0])     //  假设主串S和待匹配串T的长度存在S[0]和T[0]中。
    {
        if (S[i] == T[j]) {     // 两字母相等则继续
            ++i;
            ++j;
        }else {                 // 指针后退重新开始匹配
            i = i - j + 2;      // i退回到上次匹配首位的下一位
            j = 1;              // j退回到子串T的首位
        }
    }
    if (j > T[0])
        return i - T[0];
    else
        return 0;
}

/* KMP模式匹配算法 ： 利用子串的首字符与后续字符相等的特征，可大大避免重复遍历的情况
*   通过计算返回子串T的next数组。
*   抽象理解：尽量让S的索引i不动（不回溯），让T的索引j少动。
*
*   例如：S="abcdefgab";T="abcdex"。
*   既然“a”不与自己后面的子串中任何一个字符相等,并且S和T的前五位字符分别相等，这就意味着T的首字符“a”
*   不可能和S的第2位到第5位的字符相等。因此后面的步骤可省略。
*/
void get_next(String T, int *next)
{
    int i, j;
    i = 1;
    j = 0;
    next[1] = 0;
    while (i < T[0])    // T[0]表示串T的长度。
    {
        if (j == 0 || T[i] == T[j])     // T[i]表示后缀的单个字符；T[j]表示前缀的单个字符。
        {
            ++i;
            ++j;
            next[i] = j;
        }
        else
            j = next[j];        // 若字符不同，则j值回溯
    }
}

/* KMP模式匹配算法
*   返回子串T在主串S中第pos个字符之后的位置。若不存在,则函数返回0
*   条件：T非空，1 <= pos <= StrLength(S)
*   算法复杂度:O(n + m),仅在模式与主串之间存在许多“部分匹配”的情况优势才明显。
*/
int Index_KMP(String S, String T, int pos)
{
    int i = pos;    // i 用于主串S当前位置下标值，若pos不为1,则从pos位置开始匹配。
    int j = 1;      // j 用于子串T中当前下标值
    int next[255];      // 定义next数组
    get_next(T, next);  // 对串T作分析，得到next数组
    while (i <= S[0] && j <= T[0])  // 若i小于S的长度且j小于T的长度时，循环继续
    {
        if (j == 0 || S[i] == T[j]) // 两字母相等则继续。相比朴素算法增加了j=0判断
        {
            ++i;
            ++j;
        }
        else            // 指针后退重新开始匹配
            j = next[j];    // j退回到合适的位置，i值不变
    }
    if (j < T[0])
        return i - T[0];
    else
        return 0;
}

/* 改良的KMP模式匹配算法 */
/* 求模式串T的next函数修正值并存入数组nextval */
void get_nextval(String T, int *nextval)
{
    int i, j;
    i = 1;
    j = 0;
    nextval[1] = 0;
    while (i < T[0]) {                  // T[0]表示串T的长度。
        if (j == 0 && T[i] == T[j]) {    // T[i]表示后缀的单个字符；T[j]表示前缀的单个字符。
            ++i;
            ++j;
            if (T[i] != T[j])   // 若当前字符与前缀字符不同
                nextval[i] = j; // 则当前的j为nextval在i位置的值
            else
                nextval[i] = nextval[j];    // 若与前缀字符相同，则将前缀字符的nextval值
                                            // 赋值给nextval在i位置的值。
        }
        else
            j = nextval[j];     // 若字符不相同，则j值回溯
    }
}

int main(int argc, char const *argv[]) {
    char *str1 =
    return 0;
}
