#include "../c1.h"
#include <stdio.h>

#define MAX_VERTEX_NUM 20

typedef enum{DG, UDG} GraphKind;

typedef struct{} InfoType;
typedef struct ArcNode{
	int adjvex;
	struct ArcNode *nextarc;
	InfoType *info;
}ArcNode;

typedef char VertexType;
typedef struct{
	VertexType data;
	ArcNode *firstarc;
}VNode;
typedef VNode AdjList[MAX_VERTEX_NUM];

typedef struct{
	AdjList vertices;
	int vexnum, arcnum;
	GraphKind kind;
}ALGrapth;

int LocateVex(ALGrapth G, VertexType v){
	int i;
	for(i = 0; i < G.vexnum; i++){
		if(G.vertices[i].data == v) return i;
	}
}

Status CreateDG(ALGrapth *G){}
Status CreateUDG(ALGrapth *G){
	int IncInfo;
	printf("输入顶点数, 弧数, 其他信息\n");
	scanf("%d %d %d", &(*G).vexnum, &(*G).arcnum, &IncInfo);

	int i, j, k;
	printf("输入顶点\n");
	for(i = 0; i < (*G).vexnum; i++){
		getchar();
		scanf("%c", &(*G).vertices[i].data);
		(*G).vertices[i].firstarc = NULL;
	}
	// for(i = 0; i < (*G).vexnum; i++){
	// 	printf("%c\n", (*G).vertices[i].data);
	// }

	VertexType v1, v2;
	int w;
	printf("输入弧的初始点和终端点\n");
	for(k = 0; k < (*G).arcnum; k++){
		getchar();
		scanf("%c %c", &v1, &v2);
		// printf("%c %c %d\n", v1, v2);
		i = LocateVex((*G), v1);
		j = LocateVex((*G), v2);
		// printf("%d %d\n", i, j);

		ArcNode *an;
		an = (ArcNode*)malloc(sizeof(ArcNode));
		an->adjvex = j;
		an->nextarc = NULL;
		// printf("test1\n");

		if((*G).vertices[i].firstarc){
			ArcNode *last = (*G).vertices[i].firstarc;
			// printf("test2\n");
			while(last->nextarc) last = last->nextarc;
			// printf("test3\n");

			last->nextarc = an;
			// printf("test4\n");
		}else{
			(*G).vertices[i].firstarc = an;
		}
		if((*G).vertices[j].firstarc){
			ArcNode *last = (*G).vertices[j].firstarc;
			// printf("test2\n");
			while(last->nextarc) last = last->nextarc;
			// printf("test3\n");

			last->nextarc = an;
			// printf("test4\n");
		}else{
			(*G).vertices[j].firstarc = an;
		}

		if(IncInfo){
			// Input(*(*G).arcs[i][j].info);
		}
	}

}

Status CreateGraph(ALGrapth *G){
	int kind;
	printf("输入图种类\n");
	scanf("%d", &kind);
	(*G).kind = (GraphKind)kind;
	switch((*G).kind){
		case  DG: return CreateDG(&*G);
		case UDG: return CreateUDG(&*G);
		default: return ERROR;
	}
}

void printGraph(ALGrapth G){
	int i, j;
	printf("输出顶点\n");
	for(i = 0; i < G.vexnum; i++){
		printf("序号: %d\n", i);
		printf("%c", G.vertices[i].data);

		ArcNode *an;
		an = G.vertices[i].firstarc;

		while(an){
			printf("---");
			printf("%d", an->adjvex);
			an = an->nextarc;
		}
		printf("\n");
	}
}

int main(){
	ALGrapth G;
	int i, j;

	CreateGraph(&G);

	printGraph(G);

	return 0;
}