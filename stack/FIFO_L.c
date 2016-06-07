#include "../c1.h"
#include <stdio.h>

typedef int QElemType;

typedef struct QNode{
	QElemType		data;
	struct QNode	*next;
}QNode;

typedef QNode* QueuePtr;

typedef struct{
	QueuePtr	front;
	QueuePtr	rear;
}LinkQueue;

Status InitQueue(LinkQueue *Q){
	(*Q).front = (*Q).rear = (QueuePtr)malloc(sizeof(QNode));
	if(!(*Q).front) exit(OVERFLOW);
	(*Q).front->next = NULL;
	return OK;
}

Status EnQueue(LinkQueue *Q, QElemType e){
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	(*Q).rear->next = p;
	(*Q).rear = p;
	return OK;
}

Status TraverseQueue(LinkQueue Q, void(visit)(QElemType)){
	QueuePtr p;
	p = Q.front->next;
	while(p){
		visit(p->data);
		p = p->next;
	}
}

void printElem(QElemType e){
	printf("%d ", e);
}

int QueueLength(LinkQueue Q){
	QueuePtr p;
	p = Q.front->next;
	int count = 0;
	while(p){
		count++;
		p = p->next;
	}
	return count;
}

int isEmpty(LinkQueue Q){
	if(Q.front->next) return 0;
	else return 1;
}

Status GetHead(LinkQueue Q, QElemType *e){
	if(!Q.front->next) return ERROR;
	(*e) = Q.front->next->data;
	return OK;
}

Status DeQueue(LinkQueue *Q, QElemType *e){
	if(!(*Q).front->next) return ERROR;
	QueuePtr p;
	p = (*Q).front->next;
	(*e) = p->data;
	(*Q).front->next = p->next;
	free(p);
	return OK;
}

int main(){
	QElemType e;
	int i;
	LinkQueue Q;

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