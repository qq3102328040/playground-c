#include "../c1.h"
#include <stdio.h>

typedef struct{
	unsigned int weight;

	unsigned int parent;
	unsigned int lchild;
	unsigned int rchild;
}HTNode;
typedef HTNode *HuffmanTree;

typedef char *HCNode;
typedef HCNode *HuffmanCode;


Status initHuffmanTree(HuffmanTree *HT){
    (*HT) = NULL;
}

Status initHuffmanCode(HuffmanCode *HC){
	(*HC) = NULL;
}

Status select(HuffmanTree HT, int n, int *ss1, int *ss2){
	int i = 0;
	int s1 = 0, s2 = 0;
	for(i = 1; i <= n; i++){
		if(HT[i].parent == 0){
			if(s2 == 0){
				if(s1 == 0){
					s1 = i;
					continue;
				}
				if(HT[i].weight < HT[s1].weight){
					s2 = s1;
					s1 = i;
					continue;
				}
				s2 = i;
			}
			if(HT[i].weight < HT[s2].weight){
				if(HT[i].weight < HT[s1].weight){
					s2 = s1;
					s1 = i;
					continue;
				}
				s2 = i;
			}
		}
	}
	(*ss1) = s1;
	(*ss2) = s2;

	return OK;
}

Status createHuffmanTree(HuffmanTree *HT, int *w, int n){	
	int i;
	int m = 2 * n - 1;
	(*HT) = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	HuffmanTree p = (*HT);
	for(i = 1; i <= n; i++){
		p[i].weight = w[i];
		p[i].parent = 0;
		p[i].lchild = 0;
		p[i].rchild = 0;
	}
	for(i = n + 1; i <= m; i++){
		p[i].weight = 0;
		p[i].parent = 0;
		p[i].lchild = 0;
		p[i].rchild = 0;
	}
	int s1, s2;
	for(i = n + 1; i <= m; i++){
		select(p, i - 1, &s1, &s2);
		p[s1].parent = i;
		p[s2].parent = i;
		p[i].lchild = s1;
		p[i].rchild = s2;
		p[i].weight = p[s1].weight + p[s2].weight;
	}
}

void printHuffmanTree(HuffmanTree HT, int n){
	int i;
	int m = 2 * n - 1;
	for(i = 1; i <= m; i++){
		printf("%d::", i);
		printf("%d---", HT[i].weight);
		printf("%d---", HT[i].parent);
		printf("%d---", HT[i].lchild);
		printf("%d", HT[i].rchild);
		printf("\n");
	}
}

void printHuffmanCode(HuffmanCode HC, int n){
	int i;
	for(i = 1; i <= n; i++){
		printf("%s\n", HC[i]);
	}
}

Status HuffmanCoding(HuffmanTree HT, HuffmanCode *HC, int n){
	(*HC) = (HuffmanCode)malloc((n + 1) * sizeof(HCNode));
	HCNode cd = (HCNode)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	int i;
	for(i = 1; i <= n; i++){
		int start = n - 1;
		int c, f;
		for(c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent){
			if(HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';
		}
		(*HC)[i] = (HCNode)malloc((n - start) * sizeof(char));
		strcpy((*HC)[i], &cd[start]);
	}
	free(cd);
}

int main()
{	
	HuffmanTree HT;
	HuffmanCode HC;
	int i, j;
	int n;

	int *weight;//权重表
	char *name;//字符表

	printf("请输入个数\n");
	scanf("%d", &n);

	weight = (int*)malloc((n + 1) * sizeof(int));
	name = (char*)malloc((n + 1) * sizeof(char));

	printf("输入字符表\n");
	getchar();//吃一个字符
	name[1] = '@';
	for (i = 1; i <= n; ++i){
		name[i] = getchar();
	}
	name[n + 1] = '\0';

	printf("输入权重表\n");
	for(i = 1; i <= n; ++i){
		scanf("%d", &weight[i]);
	}

	createHuffmanTree(&HT, weight, n);

	printf("输出赫夫曼树\n");
	printHuffmanTree(HT, n);

	HuffmanCoding(HT, &HC, n);
	printf("输出赫夫曼编码表\n");
	printHuffmanCode(HC, n);

	printf("输入查询字符\n");
	char queryString[20];
	scanf("%s", queryString);

	for(i = 0; i < strlen(queryString); i++){
		for(j = 1; j <= n; j++){
			if(queryString[i] == name[j]){
				printf("%s ", HC[j]);
				break;
			}
		}
	}
	printf("\n");

	printf("请输入编码\n");
	char queryCode[20];
	scanf("%s", queryCode);

	int flag;
	int bigFlag;
	int start = 0;
	while(true){
		if((strlen(queryCode) - start) < 2) break;
		bigFlag = 1;
		for(i = 1; i <= n; i++){
			flag = 1;
			for(j = 0; j < strlen(HC[i]); j++){
				if(HC[i][j] != queryCode[j + start]){
					flag = 0;
					break;
				}
			}
			if(flag){
				start += strlen(HC[i]);
				printf("%c", name[i]);
				bigFlag = 0;
			}
		}
		if(bigFlag) break;
	}
	printf("\n");

	return 0;
}
