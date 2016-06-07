#include "../c1.h"
#include <stdio.h>
#include "queue.c"

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

Boolean visited[MAX_VERTEX_NUM];
Status (*visitfunc)(VertexType v);


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
	for(k = 0; k < (2 * (*G).arcnum); k++){
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

int FirstAdjVex(ALGrapth G, int v){
	int rv = -1;
	if(G.vertices[v].firstarc){
		rv = G.vertices[v].firstarc->adjvex;
	}
	return rv;
}

int NextAdjVex(ALGrapth G, int v, int w){
	int rv = -1;
	ArcNode *an = G.vertices[v].firstarc;
	while(an){
		if(an->adjvex == w){
			if(an->nextarc){
				rv = an->nextarc->adjvex;
			}
		}
		an = an->nextarc;
	}
	return rv;
}

Status DFS(ALGrapth G, int v){
	// printf("%d\n", v);
	// printf("visited%d: %d\n", v, visited[v]);
	visited[v] = TRUE;
	// printf("visited%d: %d\n", v, visited[v]);
	visitfunc(G.vertices[v].data);
	int w;
	for(w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)){
		// printf("w:%d\n", w);
		if(!visited[w]) DFS(G, w);
		// printf("step\n");
	}
	// printf("stop\n");
	return OK;
}

Status DFSTraverse(ALGrapth G, Status(visit)(VertexType), int num = 0){
	int i;
	visitfunc = visit;
	for(i = 0; i < G.vexnum; i++){
		visited[i] = FALSE;
	}
	// printf("test1\n");exit(1);
	DFS(G, num);
	for(i = 0; i < G.vexnum; i++){
		if(!visited[i]) DFS(G, i);
		// printf("end\n");
	}
	// printf("test\n");
}

Status BFSTraverse(ALGrapth G, Status(visit)(VertexType), int num = 0){
	int i;
	visitfunc = visit;
	for(i = 0; i < G.vexnum; i++){
		visited[i] = FALSE;
	}
	LinkQueue Q;
	InitQueue(&Q);
	int j;
	for(i = num, j = 0; j < G.vexnum; i++, j++){
		if(i == G.vexnum) i = 0;
		if(!visited[i]){
			visited[i] = TRUE;
			visitfunc(G.vertices[i].data);
			EnQueue(&Q, i);
			int u;
			while(!isEmpty(Q)){
				DeQueue(&Q, &u);
				int w;
				for(w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)){
					// printf("w: %d\n", w);
					visited[w] = TRUE;
					visitfunc(G.vertices[w].data);
					EnQueue(&Q, w);
					// printf("step\n");
				}
				// printf("stop\n");
			}
		}
		// printf("end\n");
	}
}

Status printVex(VertexType v){
	printf("%c ", v);
}

void printGraph(ALGrapth G){
	int i, j;
	printf("输出顶点\n");
	for(i = 0; i < G.vexnum; i++){
		printf("序号:%d---", i);
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

	printf("从顶点1开始深度优先遍历序列");
	DFSTraverse(G, printVex);
	printf("\n");

	printf("从顶点7开始深度优先遍历序列");
	DFSTraverse(G, printVex, 6);
	printf("\n");

	printf("从顶点1开始广度优先遍历序列");
	BFSTraverse(G, printVex);
	printf("\n");

	printf("从顶点7开始广度优先遍历序列");
	BFSTraverse(G, printVex, 6);
	printf("\n");

	printf("\n");
	return 0;
}