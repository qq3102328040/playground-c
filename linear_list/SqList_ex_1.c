#include "../c1.h"

#define LIST_INIT_SIZE  100
#define LISTINCREMENT   10

typedef int ElemType;

typedef struct{
    ElemType    *elem;
    int         length;
    int         listsize;
}SqList;

Status InitList_Sq(SqList *L){
    (*L).elem = (ElemType * )malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!(*L).elem) exit(OVERFLOW);
    (*L).length = 0;
    (*L).listsize = LIST_INIT_SIZE;
    return OK;
}

Status ListInsert_Sq(SqList *L, int i, ElemType e){
    ElemType *newbase;
    ElemType *q, *p;
    //正确性处理
    if(i < 1 || i > (*L).length + 1) return ERROR;
    //超出长度处理
    if((*L).length >= (*L).listsize){
        newbase = (ElemType * )realloc((*L).elem, ((*L).listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!newbase) exit(OVERFLOW);
        (*L).elem = newbase;
        (*L).listsize += LISTINCREMENT;
    }
    
    q = &((*L).elem[i-1]);
    for(p = &((*L).elem[(*L).length - 1]); p >= q; --p){
        *(p + 1) = *p;
    }
    *q = e;
    (*L).length++;
    return OK;
}

Status GetElem_Sq(SqList L, int i, ElemType *e){
    if(i < 1 || i > L.length) return ERROR;
    else *e = L.elem[i-1];
    return OK;
}

Status ListTraverse_Sq(SqList L, void(Visit)(ElemType)){
    int i;
    for(i = 0; i < L.length; i++){
        Visit(L.elem[i]);
    }
    return OK;
}

void PrintElem(ElemType e){
    printf("%d ", e);
}

Status ListEmpty_Sq(SqList L){
    if(!L.length) return TRUE;
    return FALSE;
}

Status LocateElem_Sq(SqList L, ElemType e, int(compare)(ElemType, ElemType)){
    int i = 0;
    while(i < L.length){
        if(compare(e, L.elem[i])) break;
        i++;
    }
    if(i < L.length) return ++i;
    return 0;
}

int equil(ElemType e1, ElemType e2){
    if(e1 == e2) return 1;
    else return 0;
}

Status ListDelete_Sq(SqList *L, int i, ElemType *e){
    ElemType *p, *q;
    if((i < 1) || (i > (*L).length)) return ERROR;
    p = &((*L).elem[i-1]);
    *e = *p;
    q = (*L).elem + (*L).length - 1;
    for(++p; p <= q; ++p)
        *(p - 1) = *p;
    --(*L).length;
    return OK;
}

Status ListDeleteBetweenXAndY_Sq(SqList *L, int x, int y){
    if(x > y || x < 0 || y < 0) return ERROR;
    int step = 0;
    ElemType *e;
    for(int i = 0; i < (*L).length; i++){
        e = &((*L).elem[i]);
        if((*e) >= x && (*e) <= y){
            step++;
            continue;
        }
        *(e - step) = *e;
    }
    (*L).length = (*L).length - step;
    return OK;
}

Status ListDeleteAscendingRemoveRepeat_Sq(SqList *L){
    if(!(*L).length) return ERROR;
    int step = 0;
    ElemType *p, *q;
    p = &((*L).elem[0]);
    for (int i = 1; i < (*L).length; ++i){
        q = &((*L).elem[i]);
        // printf("前%d\n", (*q));
        if((*p) == (*q)){
            step++;
            // printf("step : %d\n", step);
            continue;
        }
        *(++p) = *q;
    }
    (*L).length = (*L).length - step;
    return OK;
}

int main(){

    SqList L;
    int i;
    ElemType e;

    printf("初始化顺序表L\n");
    InitList_Sq(&L);

    printf("请输入插入元素个数：");
    int elem_sum;
    scanf("%d", &elem_sum);
    printf("请输入元素\n");
    for(i = 1; i <= elem_sum; i++){
        scanf("%d", &e);
        ListInsert_Sq(&L, L.length + 1, e);
    }

    printf("输出顺序表L\n");
    ListTraverse_Sq(L, PrintElem);
    printf("\n");

    ListDeleteAscendingRemoveRepeat_Sq(&L);

    printf("输出顺序表L\n");
    ListTraverse_Sq(L, PrintElem);
    printf("\n");


}
