/* 栈与队列：
*   栈是限定在表尾进行插入和删除操作的“线性表”
*   队列是只允许在一端进行插入操作，而在另一端进行删除操作的”线性表”
*/

/* 栈的形象化理解：左轮手枪和弹夹式手枪(后进先出)
*   应用：浏览器的网页后退键的实现，文档和图像编辑软件中的撤销操作(undo)
*/

/* 栈：允许插入和删除的一端为栈顶(top), 另一端为栈底(bottom)
*   栈又称后进先出(Last In First Out)的线性表，简称LIFO结构
*/

/* 栈的抽象数据类型：
*   ADT 栈（stack)
*   Data
*       同线性表。元素具有相同的数据类型，相邻元素具有前驱和后继关系。
*   Operation
*       InitStack(*S): 初始化操作，建立一个空栈 S 。
*       DestroyStack(*S): 若栈存在，则销毁它。
*       ClearStack(*S): 清空栈。
*       StackEmpty(S): 若栈为空，返回true, 否则返回false。
*       GetTop(S, *e): 若栈存在且非空，用 e 返回 S 的栈顶元素。
*       Push(*S，e): 若栈 S 存在，插入新的元素 e 到栈 S 中并成为栈顶元素。
*       Pop(*S, *e): 删除栈 S 的栈顶元素， 并用 e 返回其值。
*       StackLength(S): 返回栈 S 的元素个数。
*   endADT
*/

#include <stdio.h>
#define MAXSIZE 20

/* 栈的顺序存储结构(游标卡尺)及其实现 */
// 栈的结构定义
typedef int SElemType;  // 定义 SElemType 为 int 型
typedef struct
{
    SElemType data[MAXSIZE];
    int top;    // 用于栈顶指针
}SqStack;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
/* Status 是函数类型，其值是函数结果状态代码， 如OK等 */

// 进栈操作Push: 若栈不满，则插入元素 e 为新的栈顶指针
Status Push(SqStack *S, SElemType e) {
    if (S->top == MAXSIZE -1) {
        return ERROR;
    }
    S->top++;               // 栈顶指针加一
    S->data[S->top] = e;    // 将新插入元素赋值给栈顶空间
    return OK;
}

// 出栈操作Pop: 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK; 否则返回ERROR；
Status Pop(SqStack *S, SElemType *e) {
    if (S->top == -1)
        return ERROR;
    *e = S->data[S->top];   // 要删除的栈顶元素赋值给e
    S->top--;               // 栈顶指针减一
    return OK;
}

/* 两栈共享空间
*   单栈的缺陷：必须事先确定数组存储空间的大下
*   共享空间的形象化理解：合租两居室(各有卧室，共享客厅、厨房和卫生间), 两个一居室利用率低
*   实现方式：顶对顶
*   栈空：top1 = -1, top2 = n
*   栈满： top1 + 1 = top2
*/
// 两栈共享空间结构
typedef struct
{
    SElemType data[MAXSIZE];
    int top1;   // 栈1栈顶指针
    int top2;   // 栈2栈顶指针
}SqDoubleStack;

// 两栈共享空间的Push方法：需要判断栈1还是栈2需要判断栈1还是栈2的栈号参数stackNumber
Status DoublePush(SqDoubleStack *S, SElemType e, int stackNumber)
{
    if (S->top1 + 1 == S->top2) {   // 栈已满，不能再push新元素
        return ERROR;
    }
    if (stackNumber == 1)           // 栈1有元素进栈
        S->data[++S->top] = e       // top先加一，再插入元素
    else if (stackNumber == 2)      // 栈2有元素进栈
        S->data[--S->top2] = e;

    return OK;
}

// 两栈共享空间的Pop方法：判断stackNumer
Status DoublePop(SqDoubleStack *S, SElemType *e, int stackNumber) {
    if (stackNumber == 1) {
        if (S->top1 == -1)          // 判断栈1是否为空
            return ERROR;
        *e = S->data[S->top--];     // 将栈1的栈顶元素出栈
    } else if (stackNumber == 2) {
        if (S->top2 == MAXSIZE)     // 判断栈2是否为空，避免溢出
            return ERROR;
        *e = S->data[S->top--];     // 将栈2的栈顶元素出栈
    }
}

/* 栈的链式存储结构及实现 */
// 栈顶放在单链表的头部，对于链栈，不需要头结点
// 链栈的结构代码
typedef struct StackNode
{
    SElemType data;
    struct StackNode *next;
}StackNode,*LinkStackPtr;

typedef struct LinkStack
{
    LinkStackPtr top;
    int count;
}LinkStack;

// 链栈的进栈操作： 插入元素 e
Status LinkStack_Push(LinkStack *S, SElemType e) {
    LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
    s->data = e;
    s->next = S->top;   // 将当前的栈顶元素赋值给新节点的直接后继
    S->top = s;         // 将新的结点s赋值给栈顶指针
    S->count += 1;

    return OK;
}

// 链栈的出栈操作Pop：三步：变量p存储要删除的结点；栈顶指针下移；释放p
Status LinStack_Pop(LinkStack *S, SElemType *e) {
    LinkStackPtr p;
    // if (S->top == NULL)
    //     return ERROR;
    if (StackEmpty(*S))
        return ERROR;
    *e = S->top->data;
    p = S->top;             // 栈顶结点赋值给 p
    S->top = S->top->next;  // 栈顶指针下移一位，指向后一结点
    free(p);                // 释放结点p
    S->count += 1;

    return OK;
}

/* 顺序栈和链栈的区别
*   时间复杂度均为O(1)。空间性能：顺序栈需要事先固定长度，可能存在内存空间浪费，但存取时定位方便
*   链栈要求每个元素都有指针域，增加内存开销，但对于栈长度无限制。
*/
