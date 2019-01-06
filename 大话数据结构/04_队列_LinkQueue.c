#include <stdio.h>

/*
    ADT 队列（Queue）
    Data
        同线性表。元素具有相同的类型，相邻元素具有前驱和后继关系。
    Operation
        InitQueue (*Q)      : 初始化操作，建立一个空队列 Q 。
        DestoryQueue (*Q)   : 若队列 Q 存在， 则销毁它。
        ClearQueue (*Q)     : 将队列清空。
        QueueEmpty (*Q)     : 若队列 Q 为空，返回 true，否则返回false。
        GetHead (Q, *e)     : 若队列 Q 存在且非空，用 e 返回队列Q的队头元素。
        EnQueue (*Q, e)     : 若队列Q存在，插入新元素e到队列Q中并成为队尾元素。
        DeQueue (*Q, *e)    : 删除队列Q中的队头元素，并用e返回其值。
        QueueLength (Q)     : 返回队列Q的元素个数。

    endADT
*/

/* 定义相关参数 */
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 5
typedef int Status;


typedef int QElemType;  // QElemType类型根据实际情况而定，这里假设为int。

/* 队列的链式存储结构 */
typedef struct QNode    // 结点结构
{
    QElemType data;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct              // 队列的链表结构
{
    QueuePtr front, rear;   // 队头、队尾指针
}LinkQueue;

/* 链队列的入队操作: 插入元素e为Q的新的队尾元素 */
Status EnQueue(LinkQueue *Q, QElemType e)
{
    QueuePtr s = (QueuePtr) malloc(sizeof(QNode));  // 给指针分配内存空间
    if (!s)     // 存储分配失败
        exit(OVERFLOW);
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;  // 把拥有元素e新节点s赋值给原队列结点的后继
    Q->rear = s;        // 把当前的s设置为队尾结点，rear指向s

    return OK;
}

/* 链队列的出队列操作： 若队列不空，删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR */
Status DeQueue(LinkQueue *Q, QElemType *e)
{
    QueuePtr p;
    if (Q->front == Q->rear)    // 判断队列是否为空
        return ERROR;
    p = Q->front->next;         // 将欲删除的队头结点暂存给p
    *e = p->data;               // 将欲删除的队头结点的值赋值给e
    Q->front->next = p->next;   // 将原队头结点后继p->next赋值给头结点后继。

    if (Q->rear == p)   // 若队头是队尾，则删除后将rear指向头结点
        Q->rear = Q->front;
    free(p);

    return OK;
}

/* 打印队列的元素值 */
int PrintValue(SqQueue Q)
{
    if (Q.front == Q.rear)  // 判断队列是否为空
        return ERROR;

    int i = Q.front;
    while(i != Q.rear)
    {
        printf("%3d ", Q.data[i]);
        i = (i+1) % MAXSIZE;
    }
    printf("\n");

    return OK;
}

int main(int argc, char const *argv[]) {
    printf("%s\n", "队列的链式存储结构");
    printf("%s\n", "初始化...");
    LinkQueue queue;
    QElemType e = 0;
    QElemType arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    return 0;
}
