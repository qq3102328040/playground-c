#include "../c1.h"
#include <stdio.h>

typedef char TElemType;
typedef struct BiTNode{
    TElemType   data;
    struct  BiTNode* lchild;
    struct 	BiTNode* rchild;
}BiTNode;
typedef BiTNode* BiTree;

Status InitBiTree(BiTree *T){
    (*T) = NULL;
}

Status CreateBiTree(BiTree *T){
	char ch;
	scanf("%c", &ch);
	if(ch == '#') (*T) = NULL;
	else{
		if(!((*T) = (BiTNode*)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		(*T)->data = ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
	return OK;
}

int BiTreeDepth(BiTree T){
	int leftDepth, rightDepth;
	if(T == NULL) return 0;
	leftDepth = BiTreeDepth(T->lchild);
	rightDepth = BiTreeDepth(T->rchild);
	return (leftDepth >= rightDepth ? leftDepth : rightDepth) + 1;
}

void PrintElem(TElemType e){
	printf("%c ", e);
}

Status PreOrderTraverse(BiTree T, void(visit)(TElemType e)){
	if(T){
		visit(T->data);
		PreOrderTraverse(T->lchild, visit);
		PreOrderTraverse(T->rchild, visit);
	}
	return OK;
}

Status InOrderTraverse(BiTree T, void(visit)(TElemType e)){
	if(T){
		InOrderTraverse(T->lchild, visit);
		visit(T->data);
		InOrderTraverse(T->rchild, visit);
	}
}

Status PostOrderTraverse(BiTree T, void(visit)(TElemType e)){
	if(T){
		PostOrderTraverse(T->lchild, visit);
		PostOrderTraverse(T->rchild, visit);
		visit(T->data);
	}
}

int leavesTraverse(BiTree T, void(visit)(TElemType e)){
	int count = 0;
	if(T){
		if(T->lchild || T->rchild){
			count += leavesTraverse(T->lchild, visit);
			count += leavesTraverse(T->rchild, visit);
			return count;
		}else{
			visit(T->data);
			return 1;
		}
		
	}
}

Status LevelOrderTraverse(BiTree T, void(visit)(TElemType e)){
	if(T){
		BiTree p[100];
		int i, j;
		i = j = 0;

		p[j++] = T;

		while(i < j){
			visit(p[i]->data);
			if(p[i]->lchild)
				p[j++] = p[i]->lchild;
			if(p[i]->rchild)
				p[j++] = p[i]->rchild;
			i++;
		}
		return OK;
	}
}

Status exchangeTraverse(BiTree T){
	if(T){
		exchangeTraverse(T->lchild);
		exchangeTraverse(T->rchild);
		BiTree p = T->lchild;
		T->lchild = T->rchild;
		T->rchild = p;
	}
}

int main(){
    BiTree T;

    printf("初始化二叉树T\n");
    InitBiTree(&T);

    printf("输入扩展先序序列, 创建二叉树\n");
    CreateBiTree(&T);

    printf("输出二叉树的深度\n");
    printf("%d\n", BiTreeDepth(T));

    printf("输出二叉树的先序遍历序列\n");
    PreOrderTraverse(T, PrintElem);
    printf("\n");

    printf("输出二叉树的中序遍历序列\n");
    InOrderTraverse(T, PrintElem);
    printf("\n");

    printf("输出二叉树的后序遍历序列\n");
    PostOrderTraverse(T, PrintElem);
    printf("\n");

    printf("输出二叉树的层次遍历序列\n");
    LevelOrderTraverse(T, PrintElem);
    printf("\n");

    printf("统计二叉树中叶子结点的个数，并输出所有的叶子结点\n");
    printf("%d个\n", leavesTraverse(T, PrintElem));

    printf("交换二叉树的左右子树\n");
    exchangeTraverse(T);

    printf("输出二叉树的先序遍历序列\n");
    PreOrderTraverse(T, PrintElem);
    printf("\n");

    printf("输出二叉树的中序遍历序列\n");
    InOrderTraverse(T, PrintElem);
    printf("\n");

    printf("输出二叉树的后序遍历序列\n");
    PostOrderTraverse(T, PrintElem);
    printf("\n");

    printf("输出二叉树的层次遍历序列\n");
    LevelOrderTraverse(T, PrintElem);
    printf("\n");

    return 0;
}
