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
        //printf("%d", ListInsert_Sq(&L, L.length, e));
        //printf("%d", e);
    }
    //test ListInsert
    //ListInsert_Sq(&L, 1, 1);
    //ListInsert_Sq(&L, 2, 2);
    //ListInsert_Sq(&L, 3, 3);
    //ListInsert_Sq(&L, 4, 5);

    printf("输出顺序表L\n");
    ListTraverse_Sq(L, PrintElem);
    printf("\n");

    printf("顺序表L长度为%d\n", L.length);
    
    if(ListEmpty_Sq(L)){
        printf("线性表为空\n");    
    }else{
        printf("线性表不为空\n");
    }

    printf("请输入要查询的元素序号：");
    int elem_num;
    scanf("%d", &elem_num);
    GetElem_Sq(L, elem_num, &e);
    printf("第 %d 个元素为 %d \n", elem_num, e);

    printf("请输入要查询的元素: ");
    scanf("%d", &e);
    int location;
    location = LocateElem_Sq(L, e, equil);
    if(location){
        printf("%d 所在的位置为 %d \n", e, location);
    }else{
        printf("元素不存在 \n");
    }

    printf("请输入要插入元素的位置：");
    scanf("%d", &elem_num);
    printf("请输入要插入的元素：");
    scanf("%d", &e);
    ListInsert_Sq(&L, elem_num, e);
    ListTraverse_Sq(L, PrintElem);
    printf("\n");

    printf("请输入删除要元素的序号：");
    scanf("%d", &elem_num);
    ListDelete_Sq(&L, elem_num, &e);
    ListTraverse_Sq(L, PrintElem);
    printf("\n");
}
