#include "../c1.h"
#include <stdio.h>

#define     STACK_INIT_SIZE     100
#define     STACKINCREMENT      10

typedef int SElemType;

typedef struct{
    SElemType   *base;
    SElemType   *top;
    int         stacksize;
}SqStack;

Status InitStack_Sq(SqStack *S){
    (*S).base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!(*S).base) exit(OVERFLOW);
    (*S).top = (*S).base;
    (*S).stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop_Sq(SqStack S, SElemType *e){
    if(S.top == S.base) return ERROR;
    *e = *(S.top - 1);
    return OK;
}

Status Push_Sq(SqStack *S, SElemType e){
    if((*S).top - (*S).base >= (*S).stacksize){
        (*S).base = (SElemType*)realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
        if(!(*S).base) exit(OVERFLOW);

        (*S).top = (*S).base + (*S).stacksize;
        (*S).stacksize += STACKINCREMENT;
    }
    *((*S).top) = e;
    *((*S).top)++;
}

Status Pop_Sq(SqStack *S, SElemType *e){
    if((*S).top == (*S).base) return ERROR;
    *e = *--(*S).top;
    return OK;
}

Status StackTraverse_Sq(SqStack S, void(Visit)(SElemType)){
    SElemType *p = S.base;
    while(p < S.top){
        Visit(*p++);
    }
    return OK;
}

void PrintElem(SElemType e){
    printf("%d ", e);
}

int StackLength_Sq(SqStack S){
    return S.top - S.base;
}

Status StackEmpty_Sq(SqStack S){
    if(S.base == S.top){
        return TRUE;
    }else{
        return FALSE;
    }
}

int main(){
    SElemType e;
    SqStack S;
    int i;

    printf("初始化栈S\n");
    InitStack_Sq(&S);

    printf("请输入元素个数:");
    int elem_sum;
    scanf("%d", &elem_sum);
    printf("请输入元素:\n");
    for(i = 1; i <= elem_sum; i++){
        scanf("%d", &e);
        Push_Sq(&S, e);
    }

    printf("输出栈:\n");
    StackTraverse_Sq(S, PrintElem);
    printf("\n");

    printf("栈长度为 : %d\n", StackLength_Sq(S));

    printf("栈是否为空:");
    if(StackEmpty_Sq(S)){
        printf("是\n");
    }else{
        printf("否\n");
    }

    SElemType top;
    GetTop_Sq(S, &top);
    printf("栈顶元素为 : %d\n", top);

    printf("请输入入栈元素 : ");
    scanf("%d", &e);
    Push_Sq(&S, e);
    printf("输出栈:\n");
    StackTraverse_Sq(S, PrintElem);
    printf("\n");

    printf("栈顶元素出栈\n");
    Pop_Sq(&S, &e);
    printf("输出栈:\n");
    StackTraverse_Sq(S, PrintElem);
    printf("\n");

    printf("出栈:\n");
    int length = StackLength_Sq(S);
    for(i = 0; i < length; i++){
        Pop_Sq(&S, &e);
        printf("%d ", e);
    }

    printf("\n");

    return 0;
}
