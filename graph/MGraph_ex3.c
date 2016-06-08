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

typedef struct{
	VertexType adjvex;
	VRType lowcost;
}closedge;

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

int minimum(MGraph G, closedge closedge[]){
	int i;
	int min = INFINITY;
	int k = -1;
	for(i = 0; i < G.vexnum; i++){
		if(closedge[i].lowcost > 0 && min > closedge[i].lowcost){
			min = closedge[i].lowcost;
			k = i;
		}
	}
	return k;
}

void MiniSpanTree_PRIM(MGraph G, VertexType v){
	closedge closedge[MAX_VERTEX_NUM];

	int k;
	k = LocateVex(G, v);
	// printf("k: %d\n", k);

	int j;
	for(j = 0; j < G.vexnum; j++){
		if(j != k){
			closedge[j].adjvex = v;
			closedge[j].lowcost = G.arcs[k][j].adj;
			// printf("j: %d\n", j);
		}
	}
	// printf("step1\n");
	closedge[k].lowcost = 0;

	// int ii;
	// for(ii = 0; ii < G.vexnum; ii++){
	// 	printf("%d--%c\n", closedge[ii].lowcost, closedge[ii].adjvex);
	// }

	int i;
	for(i = 0; i < G.vexnum; i++){
		k = minimum(G, closedge);
		// printf("k: %d\n", k);
		if(k < 0) break;
		printf("%c %c\n", closedge[k].adjvex, G.vexs[k]);
		closedge[k].lowcost = 0;

		for(j = 0; j < G.vexnum; j++){
			if(G.arcs[k][j].adj < closedge[j].lowcost){
				closedge[j].adjvex = G.vexs[k];
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
			// printf("step2\n");
		}
		// printf("step3\n");
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
	printGraph(G);
	MiniSpanTree_PRIM(G, '1');

	return 0;
}