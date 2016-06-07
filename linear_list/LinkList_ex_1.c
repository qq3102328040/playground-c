#include <stdio.h>
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

Status InsertBbeforeA_L(LinkList L, ElemType a, ElemType b){
	LinkList s, p, q;
	p = L->next;
	q = L;
	while(p){
		if(p->data == a){
			s = (LinkList)malloc(sizeof(LNode));
			s->data = b;
			s->next = q->next;
			q->next = s;
			break;
		}
		if(!p->next){
			s = (LinkList)malloc(sizeof(LNode));
			s->data = b;
			s->next = p->next;
			p->next = s;
			break;
		}
		q = p;
		p = p->next;
	}
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

Status ListDeleteBetweenXAndY_L(LinkList L, int x, int y){
	LinkList p, q;
	q = L;
	int e;
	p = L->next;
	while(p){
		e = p->data;
		if(e >= x && e <= y){
			q->next = p->next;
			free(p);
			p = q->next;
			continue;
		}
		q = p;
		p = p->next;
	}
	return OK;
}

Status LinkListToCircularLinkList(LinkList L){
	LinkList p;
	p = L->next;
	while(p){
		if(!p->next){
			p->next = L->next;
			break;
		}
		p = p->next;
	}
	return OK;
}

Status ListTraverse_CL(LinkList L, void(visit)(ElemType)){
	LinkList p;
	if(!L) return ERROR;
	else p = L->next;
	int i = 0;
	while(p){
		visit(p->data);
		p = p->next;
		if(p == L->next) break;
	}
	return OK;
}

Status Joseph(LinkList L, int m){
	LinkList p, q;
	p = L->next;
	q = L->next;
	while(q){
		if(q->next == p) break;
		q = q->next;
	}
	int i = 0;
	while(true){
    	i++;
    	if(i == m){
    		m = p->data;
    		PrintElem(m);
    		q->next = p->next;
    		// free(p);
    		if(p == q) return OK;
    		p = q->next;
    		i = 0;
    		continue;
    	}
    	q = p;
    	p = p->next;
    }
    return ERROR;
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

    // printf("请输入x和y\n");
    // int x, y;
    // scanf("%d", &x);
    // scanf("%d", &y);
    // ListDeleteBetweenXAndY_L(L, x, y);

    // int a, b;
    // printf("请输入a和b\n");
    // scanf("%d", &a);
    // scanf("%d", &b);
    // InsertBbeforeA_L(L, a, b);

    LinkListToCircularLinkList(L);

    printf("输出顺序表L\n");
    ListTraverse_CL(L, PrintElem);
    printf("\n");

    int m;
    printf("请输入m:\n");
    scanf("%d", &m);

    Joseph(L, m);

    printf("\n");

	return 0;
}