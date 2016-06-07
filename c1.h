#include<string.h>
#include<ctype.h>
#include<malloc.h>  //malloc( )
#include<limits.h>  // INT ,MAX
#include<stdio.h> //EOF,NULL
#include<stdlib.h> //atoi( )
#include<math.h>  //floor( ),ceil( ),abs( )
//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//OVERFLOW 在 math.h 中已定义为3

typedef int Status;
typedef int Boolean; // 布尔类型

//为了操作的方便，建议本书每一个程序都把c1．h包含进去
