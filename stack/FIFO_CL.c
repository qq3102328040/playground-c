#include "../c1.h"
#include <stdio.h>

#define MAXQSIZE 100

typedef int QElemType;

typedef struct QNode{
	QElemType		data;
	struct QNode	*next;
}QNode;

typedef QNode* QueuePtr;

typedef struct{
	QElemType	*base;
	int			front;
	int			rear;
}SqQueue;

Status InitQueue(SqQueue *Q){
	(*Q).base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
	if(!(*Q).base) exit(OVERFLOW);
	(*Q).front = (*Q).rear = 0;
	return OK;
}

Status EnQueue(SqQueue *Q, QElemType e){
	if(((*Q).rear + 1) % MAXQSIZE == (*Q).front) return ERROR;
	(*Q).base[(*Q).rear] = e;
	(*Q).rear = ((*Q).rear + 1) % MAXQSIZE;
	return OK;
}

Status TraverseQueue(SqQueue Q, void(visit)(QElemType)){
	int i = Q.front;
	while(i != Q.rear){
		visit(Q.base[i]);
		i = (i + 1) % MAXQSIZE;
	}
}

void printElem(QElemType e){
	printf("%d ", e);
}

int QueueLength(SqQueue Q){
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

int isEmpty(SqQueue Q){
	if(Q.front == Q.rear) return 1;
	else return 0;
}

Status GetHead(SqQueue Q, QElemType *e){
	if(Q.front == Q.rear) return ERROR;
	(*e) = Q.base[Q.front];
	return OK;
}

Status DeQueue(SqQueue *Q, QElemType *e){
	if((*Q).front == (*Q).rear) return ERROR;
	(*e) = (*Q).base[(*Q).front];
	(*Q).front = ((*Q).front + 1) % MAXQSIZE;
	return OK; 
}

int main(){
	QElemType e;
	int i;
	SqQueue Q;

	printf("初始化队列Q\n");
	InitQueue(&Q);

	printf("请输入元素个数:");
    int elem_sum;
    scanf("%d", &elem_sum);
    printf("请输入元素:\n");
    for(i = 1; i <= elem_sum; i++){
        scanf("%d", &e);
        EnQueue(&Q, e);
    }

    printf("输出队头至队尾的元素\n");
    TraverseQueue(Q, printElem);
    printf("\n");

    int length = QueueLength(Q);
    printf("输出队列的长度:%d\n", length);

    printf("判断队列Q是否为空:");
    if(isEmpty(Q)) printf("是\n");
    else printf("否\n");

    GetHead(Q, &e);
    printf("输出队首元素:%d\n", e);

    printf("请输入入队元素:\n");
    scanf("%d", &e);
    EnQueue(&Q, e);
    printf("输出队头至队尾的元素\n");
    TraverseQueue(Q, printElem);
    printf("\n");

    DeQueue(&Q, &e);
    printf("出队列一个元素%d\n", e);
    printf("输出队头至队尾的元素\n");
    TraverseQueue(Q, printElem);
    printf("\n");

    printf("将队列中的元素依次出队\n");
    for(i = 0; i < length; i++){
    	DeQueue(&Q, &e);
    	printf("%d ", e);
    }
    printf("\n");

	return 0;
}