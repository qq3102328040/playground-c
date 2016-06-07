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