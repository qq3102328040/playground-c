#include<stdio.h>
#include "../c1.h"

typedef int ElemType;

typedef struct LNode{
	ElemType		data;
	struct LNode*	next;
}LNode;
typedef LNode* LinkList;

Status InitList_L(LinkList *L){
	(*L) = (LinkList)malloc(sizeof(LNode));
	if(!(*L)) return OVERFLOW;
	(*L)->next = NULL;
	return OK;
}

Status ListInsert_L(LinkList L, int i, ElemType e){
	LinkList s, p;
	int j = 0;
	p = L;
	while(p && j < i - 1){
		p = p->next;
		j++;
	}
	if(!p || j > i - 1) return ERROR;
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

Status GetElem_L(LinkList L, int i, ElemType *e){
	LinkList p;
	p = L->next;
	int j = 1;
	while(p && j < i){
		p = p->next;
		j++;
	}
	if(!p || j > i) return ERROR;
	*e = p->data;
	return OK;
}

Status ListTraverse_L(LinkList L, void(visit)(ElemType)){
	LinkList p;
	if(!L) return ERROR;
	else p = L->next;
	while(p){
		visit(p->data);
		p = p->next;
	}
	return OK;
}

void PrintElem(ElemType e){
	printf("%d ", e);
}

int ListLength(LinkList L){
	LinkList p;
	int i = 0;
	if(L){
		p = L->next;
		while(p){
			p = p->next;
			i++;
		}
	}
	return i;
}

Status ListEmpty_L(LinkList L){
	if(L->next == NULL){
		return TRUE;
	}else{
		return FALSE;
	}
}

Status LocateElem_L(LinkList L, ElemType e, int(compare)(ElemType, ElemType)){
	int i = 1;
	int flag = 0;
	LinkList p;
	if(L){
		p = L->next;
		while(p){
			flag = compare(e, p->data);
			if(flag) break;
			p = p->next;
			i++;
		}
	}
	if(flag) return i;
	else return 0;
}

int equil(ElemType e1, ElemType e2){
	if(e1 == e2) return 1;
	else return 0;
}

Status ListDelete_L(LinkList L, int i, ElemType *e){
	LinkList p, q;
	int j = 0;
	p = L;
	while(p->next && j < i - 1){
		p = p->next;
		j++;
	}
	if(!(p->next) || j > i - 1) return ERROR;
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;
}

int main(){

	int i;
	LinkList L;
	ElemType e;

	printf("初始化顺序表L\n");
	InitList_L(&L);

	printf("请输入插入元素个数：");
    int elem_sum;
    scanf("%d", &elem_sum);
    printf("请输入元素\n");
    for(i = 1; i <= elem_sum; i++){
        scanf("%d", &e);
        ListInsert_L(L, i, e);
    }

	// ListInsert_L(L, 1, 12);
	// ListInsert_L(L, 2, 23);
	// ListInsert_L(L, 3, 34);

    printf("输出顺序表L\n");
    ListTraverse_L(L, PrintElem);
    printf("\n");

    printf("顺序表L长度为%d\n", ListLength(L));

    if(ListEmpty_L(L)){
        printf("线性表为空\n");    
    }else{
        printf("线性表不为空\n");
    }

    printf("请输入要查询的元素序号：");
    int elem_num;
    scanf("%d", &elem_num);
    GetElem_L(L, elem_num, &e);
    printf("第 %d 个元素为 %d \n", elem_num, e);

    printf("请输入要查询的元素: ");
    scanf("%d", &e);
    int location;
    location = LocateElem_L(L, e, equil);
    if(location){
        printf("%d 所在的位置为 %d \n", e, location);
    }else{
        printf("元素不存在 \n");
    }

    printf("请输入要插入元素的位置：");
    scanf("%d", &elem_num);
    printf("请输入要插入的元素：");
    scanf("%d", &e);
    ListInsert_L(L, elem_num, e);
    ListTraverse_L(L, PrintElem);
    printf("\n");

    printf("请输入删除要元素的序号：");
    scanf("%d", &elem_num);
    ListDelete_L(L, elem_num, &e);
    ListTraverse_L(L, PrintElem);
    printf("\n");

    printf("\n");
	return 0;
}