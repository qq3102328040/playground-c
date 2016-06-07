#include "../c1.h"
#include <stdio.h>

#define MAX_VERTEX_NUM 20

typedef enum{DG, DN, UDG, UDN} GraphKind;

typedef int VRType;
typedef struct{}InfoType;
typedef struct{
	VRType adj;
	InfoType *info;
}ArcCell;
typedef ArcCell AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef char VertexType;
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum, arcnum;//定点数 弧数
	GraphKind kind;
}MGraph;

int LocateVex(MGraph G, VertexType v){
	int i;
	for(i = 0; i < G.vexnum; i++){
		if(G.vexs[i] == v) return i;
	}
}

Status CreateDG(MGraph *G){
	int IncInfo;
	printf("输入顶点数, 弧数, 其他信息\n");
	scanf("%d %d %d", &(*G).vexnum, &(*G).arcnum, &IncInfo);

	int i, j, k;
	printf("输入顶点\n");
	for(i = 0; i < (*G).vexnum; i++){
		getchar();
		scanf("%c", &(*G).vexs[i]);
	}

	for(i = 0; i < (*G).vexnum; i++){
		for(j = 0; j < (*G).vexnum; j++){
			(*G).arcs[i][j].adj = 0;
			(*G).arcs[i][j].info = NULL;
		}
	}

	VertexType v1, v2;
	int w;
	printf("输入弧的初始点和终端点\n");
	for(k = 0; k < (*G).arcnum; k++){
		getchar();
		scanf("%c %c", &v1, &v2);
		// printf("%c %c %d\n", v1, v2);
		i = LocateVex((*G), v1);
		j = LocateVex((*G), v2);
		// printf("%d %d %d\n", i, j, w);
		(*G).arcs[i][j].adj = 1;
		if(IncInfo){
			// Input(*(*G).arcs[i][j].info);
		}
	}
}
Status CreateDN(MGraph G){}
Status CreateUDG(MGraph *G){
	int IncInfo;
	printf("输入顶点数, 弧数, 其他信息\n");
	scanf("%d %d %d", &(*G).vexnum, &(*G).arcnum, &IncInfo);

	int i, j, k;
	printf("输入顶点\n");
	for(i = 0; i < (*G).vexnum; i++){
		getchar();
		scanf("%c", &(*G).vexs[i]);
	}

	for(i = 0; i < (*G).vexnum; i++){
		for(j = 0; j < (*G).vexnum; j++){
			(*G).arcs[i][j].adj = 0;
			(*G).arcs[i][j].info = NULL;
		}
	}

	VertexType v1, v2;
	int w;
	printf("输入一条边依附的两个顶点\n");
	for(k = 0; k < (*G).arcnum; k++){
		getchar();
		scanf("%c %c", &v1, &v2);
		// printf("%c %c %d\n", v1, v2);
		i = LocateVex((*G), v1);
		j = LocateVex((*G), v2);
		// printf("%d %d %d\n", i, j, w);
		(*G).arcs[i][j].adj = 1;
		if(IncInfo){
			// Input(*(*G).arcs[i][j].info);
		}
		(*G).arcs[j][i] = (*G).arcs[i][j];
	}
}
Status CreateUDN(MGraph (*G)){
	int IncInfo;
	printf("输入顶点数, 弧数, 其他信息\n");
	scanf("%d %d %d", &(*G).vexnum, &(*G).arcnum, &IncInfo);

	int i, j, k;
	printf("输入顶点\n");
	for(i = 0; i < (*G).vexnum; i++){
		getchar();
		scanf("%c", &(*G).vexs[i]);
	}
	// printf("%s\n", (*G).vexs);
	for(i = 0; i < (*G).vexnum; i++){
		for(j = 0; j < (*G).vexnum; j++){
			(*G).arcs[i][j].adj = INFINITY;
			(*G).arcs[i][j].info = NULL;
		}
	}

	VertexType v1, v2;
	int w;
	printf("输入一条边依附的两个顶点和权值\n");
	for(k = 0; k < (*G).arcnum; k++){
		getchar();
		scanf("%c %c %d", &v1, &v2, &w);
		// printf("%c %c %d\n", v1, v2, w);
		i = LocateVex((*G), v1);
		j = LocateVex((*G), v2);
		// printf("%d %d %d\n", i, j, w);
		(*G).arcs[i][j].adj = w;
		if(IncInfo){
			// Input(*(*G).arcs[i][j].info);
		}
		(*G).arcs[j][i] = (*G).arcs[i][j];
	}
}

Status CreateGraph(MGraph *G){
	int kind;
	printf("输入图种类\n");
	scanf("%d", &kind);
	(*G).kind = (GraphKind)kind;
	switch((*G).kind){
		case  DG: return CreateDG(&*G);
		case  DN: return CreateDN(*G);
		case UDG: return CreateUDG(&*G);
		case UDN: return CreateUDN(&*G);
		default: return ERROR;
	}
}

Status getDegree(MGraph G,int number,int *inDegree, int *outDegree){
	*inDegree = *outDegree = 0;
	int i, j;
	for(i = 0; i < G.vexnum; i++){
		switch(G.kind){
			case  DG:
			case UDG: 
				if(G.arcs[i][number].adj == 1) (*outDegree) += 1;
				if(G.arcs[number][i].adj == 1) (*inDegree) += 1;
				break;
			case  DN:
			case UDN:
				if(G.arcs[i][number].adj != INFINITY) (*outDegree) += 1;
				if(G.arcs[number][i].adj != INFINITY) (*inDegree) += 1;
				break;
			default: return ERROR;
		}
	}
}

void printVexs(MGraph G){
	int i;
	for(i = 0; i < G.vexnum; i++){
		int inDegree, outDegree;
		getDegree(G, i, &inDegree, &outDegree);
		printf("序号: %d, 名称: %c, 入度: %d, 出度: %d\n", i, G.vexs[i], inDegree, outDegree);
	}
}

void printGraph(MGraph G){
	printf("输出顶点\n");
	printf("%s\n", G.vexs);
	printf("输出邻接矩阵\n");
	int i, j;
	for(i = 0; i < G.vexnum; i++){
		for(j = 0; j < G.vexnum; j++){
			printf("%11d", G.arcs[i][j].adj);
		}
		printf("\n");
	}
}

int main(){
	MGraph G;
	CreateGraph(&G);
	VertexType v;
	printf("输入查询顶点\n");
	getchar();
	scanf("%c", &v);
	printf("顶点的位置为%d\n", LocateVex(G, v));
	printVexs(G);
	// printGraph(G);

	return 0;
}