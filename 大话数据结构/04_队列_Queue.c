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

/* 循环队列的理解
    解决：“假溢出”问题
    定义：队列这种头尾相接的顺序存储结构称为循环队列。
    判断队列空但还是满的两种办法：
        1. 设置标识变量flag。当front==rear,且flag=0时队列空；当front==rear,且flag=1时队列满。
        2. 保留一个元素空间。设队列的最大尺寸为QueueSize,
            队列满的条件是：(rear+1)%QueueSize == front。
            通用的计算队列长度公式：(rear-front+QueueSize)%QueueSize。
    队列长度：
        rear>front时，队列长度为rear-front。
        rear<front时，两段长度：QueueSize-front, 0+rear
*/

typedef int QElemType;  // QElemType类型根据实际情况而定，这里假设为int。
/* 循环队列的顺序存储结构 */
typedef struct {
    QElemType data[MAXSIZE];
    int front;  // 头指针
    int rear;   // 尾指针，若队列不空，指向队列尾元素的下一个位置。
}SqQueue;

/* 循环队列初始化 */
Status InitQueue(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

/* 循环队列求队列长度 */
int QueueLength(SqQueue Q)
{
    return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

/* 循环队列的入队操作 */
Status EnQueue(SqQueue *Q, QElemType e)
{
    if ((Q->rear + 1) % MAXSIZE == Q->front)    // 判断队列是否满
        return ERROR;
    Q->data[Q->rear] = e;               // 将元素e赋值给队尾。
    Q->rear = (Q->rear + 1) % MAXSIZE;  // rear 指针向后移动一位置。若到最后则转到数组头部。

    return OK;
}

/* 循环队列的出队列 */
Status DeQueue(SqQueue *Q, QElemType *e)
{
    if (Q->front == Q->rear)    // 判断队列是否为空
        return ERROR;
    *e = Q->data[Q->front];     // 将队头元素赋值给e
    Q->front = (Q->front + 1) % MAXSIZE;    // front指针后移一位置，若到最后则转到数组头部。

    return OK;
}

/* 打印循环队列的元素值 */
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
    printf("%s\n", "循环队列的顺序存储结构");
    printf("%s\n", "初始化...");
    SqQueue queue;
    QElemType e = 0;
    QElemType arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    /* 循环队列： 创建队列 */
    InitQueue(&queue);  // 初始化循环队列
    for (int i = 0; i < MAXSIZE; i++){
        if (EnQueue(&queue, arr[i]))    // 数组元素逐个入队列
            printf("%s ", "入队成功");
        else
            printf("%s ", "入队失败");

        printf("%s：%d", "入队元素", arr[i]);
        printf("%s：", "队内元素");
        if (!PrintValue(queue))
            printf("%s\n", "空");
    }

    if (!PrintValue(queue))
        printf("%s\n", "队列为空");
    else
        printf("%s\n", "队列初始化完成");

    /* 循环队列： 出队列 */
    printf("%s\n", "出队列...");
    for (int i = 0; i < MAXSIZE; i++)
    {
        DeQueue(&queue, &e);    // 队头元素出队列
        printf("队头元素：%d ", e);
        printf("队内元素：");
        if (!PrintValue(queue))
            printf("%s\n", "空");
    }
    printf("%s\n", "出队列完成");

    return 0;
}
