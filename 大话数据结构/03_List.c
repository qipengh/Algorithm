/**
* ADT 线性表（List）
* Data
* 线性表的数据对象集合为{a1,a2,a3,...,an}, 每个元素的类型均为DataType.其中，除第一个元素a1外，
* 每一个元素有且仅只有一个直接前驱元素，除了最后一个元素an外，每一个元素有且只有一个直接后继元素。
* 数据元素之间的关系是一对一的关系
* Operation
* InitList (*L)
* ListEmpty (L)  判断线性表是否为空
* ClearList (*L)
* GetElem (L, i, *e)  将线性表L中的第i个位置元素值返回给e
* LocateElem (L, e)  在线性表中查找与给定值e相逢的元素
* ListInsert (*L, i, e)
* ListDelete (*L, i, *e)
* ListLength (*L, i, e)
*/

#include<stdio.h>

// 定义顺序存储结构
#define MAXSIZE 20
typedef int ElemType;
typedef struct
{
    ElemType data[MAXSIZE];
    int length;
}SqList;

/* 顺序存储结构的插入与删除 */
// 获得元素操作
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
/* Status 是函数类型，其值是函数结果状态代码， 如OK等 */
/* 初始条件： 顺序线性表L已存在， 1 <= i <=ListLength (L) */
/* 操作结果： 用e返回L中第i个数据元素的值 */
Status GetElem(SqList L, int i, ElemType *e)
{
    if (L.length == 0 || i<1 || i>L.length) {
        return ERROR;
    }
    *e = L.data[i-1];
    return OK;
}

// 顺序线性表的插入算法
/* 初始条件： 顺序线性表L已存在， 1 <= i <=ListLength (L) */
/* 操作结果： 在L中第i个位置之前插入新的数据元素e, L的长度加1 */
Status ListInsert (SqList *L, int i, ElemType e)
{
    int k;
    if (L->length == MAXSIZE)  /* 顺序线性表已满 */
        return ERROR;
    if (i < 1 || i > L->length+1)  /* 当 i 不在范围内时 */
        return ERROR;
    if (i <= L->length) {  /* 若插入的位置不在表尾 */
        for(k = L->length-1; k >= i-1; k--)
            L->data[k+1] = L->data[k];
    }
    L->data[i-1] = e;
    L->length ++;
    return OK;
}

// 顺序线性表的删除操作
/* 初始条件： 顺序线性表L已存在， 1 <= i <=ListLength (L) */
/* 操作结果： 删除L的第i个的数据元素，并用e返回其值, L的长度减1 */
Status ListDelete(SqList *L, int i, ElemType *e)
{
    int k;
    if (L->length == 0)  /* 线性表为空*/
        return ERROR;
    if (i < 1 || i > L->length)  /* 删除位置不正确*/
        return ERROR;
    *e = L->data[i-1];
    if (i < L->length)  /* 如果删除的不是最后位置 */
    {
        for(k = i; k < L->length; k++)  /* 将删除位置后继元素后移 */
            L->data[k-1] = L->data[k];
    }
    L->length --;
    return OK;
}

int main(int argc, char const *argv[]) {
    int i, k, num;
    SqList L;
    ElemType *e;
    e = &k; /* 指针变量必须初始化才能使用， 必须存放某个地址*/
    num = 0;
    for (i = 0; i < 10; i++) {
        L.data[i] = i;
        num ++;
    }
    L.length = num;
    printf("List\n");
    for (i = 0; i < num; i++) {
        printf(" %d", L.data[i]);
    }
    printf("\n");

    Status x = GetElem(L, 5, e);
    printf("%d\n", *e);

    SqList *L1;
    L1 = &L;
    int y = ListInsert(L1, 5, 10);
    for (i = 0; i < num + 1; i++) {
        printf(" %d", L.data[i]);
    }
    printf("\n");

    int z = ListDelete(L1, 5, e);
    for (i = 0; i < num + 1; i++) {
        printf(" %d", L.data[i]);
    }
    printf("\n");
    return 0;
}
