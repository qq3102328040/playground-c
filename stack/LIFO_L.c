#include "../c1.h"
#include <stdio.h>

typedef int SElemType;

typedef struct SNode{
	SElemType		data;
	struct SNode*	next;
}SNode;

typedef SNode* StackPtr;

typedef struct{
	StackPtr	top;
	StackPtr	base;
}LinkStack;

Status InitStack_L(LinkStack *S){
	(*S).top = (*S).base = (StackPtr)malloc(sizeof(SNode));
	if(!(*S).top) return OVERFLOW;
	(*S).top->data = 0;
	(*S).top->next = NULL;
	return OK;
}

Status Push_L(LinkStack *S, SElemType e){
	if((*S).top->data == 0){
		(*S).top->data = e;
		return OK;
	}
	StackPtr p;
	p = (StackPtr)malloc(sizeof(SNode));
	p->data = e;
	p->next = (*S).top;
	(*S).top = p;
	return OK;
}

Status StackTraverse_L(LinkStack S, void(visit)(SElemType)){
	StackPtr p;
	p = S.top;
	while(p){
		visit(p->data);
		p = p->next;
	}
	return OK;
}

void PrintElem(SElemType e){
    printf("%d ", e);
}

int StackLength_L(LinkStack S){
	if(S.base->data == 0) return 0;
	int count = 0;
	StackPtr p;
	p = S.top;
	while(p){
		count++;
		p = p->next;
	}
	return count;
}

Status StackEmpty_L(LinkStack S){
    if(S.base->data == 0){
        return TRUE;
    }else{
        return FALSE;
    }
}

Status GetTop_L(LinkStack S, SElemType *e){
	if(StackEmpty_L(S)) return ERROR;
	(*e) = S.top->data;
	return OK;
}

Status Pop_L(LinkStack *S, SElemType *e){
	if((*S).base->data == 0) return ERROR;
	if(!((*S).top->next)){
		(*e) = (*S).top->data;
		(*S).top->data = 0;
		return OK;
	}
	StackPtr p;
	p = (*S).top;
	(*e) = p->data;
	(*S).top = p->next;
	free(p);
	return OK;
}

int main(){
	SElemType e;
	LinkStack S;
	int i;

	printf("初始化栈S\n");
    InitStack_L(&S);

    printf("请输入元素个数:");
    int elem_sum;
    scanf("%d", &elem_sum);
    printf("请输入元素:\n");
    for(i = 1; i <= elem_sum; i++){
        scanf("%d", &e);
        Push_L(&S, e);
    }

    printf("输出栈:\n");
    StackTraverse_L(S, PrintElem);
    printf("\n");

    int length = StackLength_L(S);
    printf("栈长度为 : %d\n", length);

    printf("栈是否为空:");
    if(StackEmpty_L(S)){
        printf("是\n");
    }else{
        printf("否\n");
    }

    SElemType top = -1;
    GetTop_L(S, &top);
    printf("栈顶元素为 : %d\n", top);

    printf("请输入入栈元素 : ");
    scanf("%d", &e);
    Push_L(&S, e);
    printf("输出栈:\n");
    StackTraverse_L(S, PrintElem);
    printf("\n");

    printf("栈顶元素出栈\n");
    Pop_L(&S, &e);
    printf("输出栈:\n");
    StackTraverse_L(S, PrintElem);
    printf("\n");

    printf("出栈:\n");
    for(i = 0; i < length; i++){
        Pop_L(&S, &e);
        printf("%d ", e);
    }

	printf("\n");
	return 0;
}