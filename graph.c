#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"

typedef int VTYPE;

typedef struct 
{
    VTYPE v[N];
    int matrix[N][N];
}graph_t;


graph_t *create_empty_graph()
{
    graph_t *g;
    int i = 0;

    g = (graph_t *)malloc(sizeof(graph_t));
    memset(g,0,sizeof(graph_t));

    for(i = 0;i < N;i ++)
    {
        g->v[i] = i;
    }

    return g;
}

int input_graph_edge(graph_t *g)
{
    int i,j;

    //输入边的关系
    //(V0,V1) (V0,V2) ... a回车

    while(scanf("(V%d,V%d)",&i,&j) == 2)
    {
        getchar();//去掉空格
        g->matrix[i][j] = g->matrix[j][i] = 1;
    }

    //清缓存的非法字符
    while(getchar() != '\n');

    return 0;
}

//输出顶点，和链接矩阵
int printf_graph(graph_t *g)
{
    int i = 0;
    int j = 0;

    for(i = 0;i < N;i ++)
    {
        printf("V%d ",g->v[i]);
    }
    printf("\n");

    for(i = 0;i < N;i ++)
    {
        for(j = 0;j < N;j ++)
        {
            printf("%d ",g->matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int visited[N];

void BFS(graph_t *g,int v)
{
    //1.创建一个队列
    //2.访问v , visited[v] = 1
    //3.将v进队
    //4.从队列中出队 v = delete_linkqueue(q);
    //  --打印
    //5.找出出队顶点的邻接点
    //for(i = 0;i < N;i ++)
    //{
    // !visited[i] && matrix[v][i] == 1
    // =>条件成立，则i为v的链接点，并且没有被访问 
    // ,访问后进队
    //}

    int i;
    LinkQueue *p = create_linkqueue();
    
    visited[v] = 1; 
    enter_linkqueue(p,v);
    while (!is_empty_linkqueue(p))
    {
       v = delete_linkqueue(p); 
       printf("V%d ",v);

       for (i = 0; i < N; i++)
       {
           if (!visited[i] && g->matrix[v][i] == 1)
           {
               visited[i] = 1;
               enter_linkqueue(p,i);
           }
       }
    }
    return;
}

int main()
{
    graph_t *g = create_empty_graph();

    input_graph_edge(g);

    printf_graph(g);

    BFS(g,0);

    return 0;
}
