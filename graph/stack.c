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