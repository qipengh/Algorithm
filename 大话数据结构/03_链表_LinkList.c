/* 线性表的链式存储结构
* 单链表中，我们可以在C语言中用结构指针来描述
*/

#include<stdio.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int ElemType;
/* 线性表的单链表存储结构 */
typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node;
typedef struct Node *LinkList;

// 单链表的读取
/* 初始条件： 顺序线性表L已存在， 1 <= i <=ListLength (L) */
/* 操作结果： 用e返回L中第i个数据元素的值 */
Status GetElem(LinkList L, int i, ElemType *e)
{
    int j;
    LinkList p;  /*声明一结点 p*/
    p = L->next;  /* 初始化p指向链表L的第一个结点 */
    j = 1;
    while (p && j < i)  /* p不为空或者计数器j还没有等于i时，循环继续*/
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i)  /* 第i个元素不存在*/
        return ERROR;
    *e = p->data;
    return OK;
}

// 单链表第i个数据插入结点
/* 初始条件： 顺序线性表L已存在， 1 <= i <=ListLength (L) */
/* 操作结果： 在L中第i个位置之前插入新的数据元素e, L的长度加1 */
Status ListInsert(LinkList *L, int i, ElemType e)
{
    int j;
    LinkList p, s;
    p = *L;
    j = 1;
    while (p || j < i) {
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR;
    s = (LinkList) malloc(sizeof(Node)); /* 生成新结点*/
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}
