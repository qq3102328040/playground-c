#include<string.h>
#include<ctype.h>
#include<malloc.h>  //malloc( )
#include<limits.h>  // INT ,MAX
#include<stdio.h> //EOF,NULL
#include<stdlib.h> //atoi( )
#include<io.h>  //eof( )
#include<math.h>  //floor( ),ceil( ),abs( )
#include<process.h> //exit( )
#include<iostream.h>  //cout,cin
//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//OVERFLOW �� math.h ���Ѷ���Ϊ3

typedef int Status;
typedef int Boolean; // ��������

//Ϊ�˲����ķ��㣬���鱾��ÿһ�����򶼰�c1��h������ȥ