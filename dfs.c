#include <stdio.h>

#include "err_malloc.h"

#define TRUE 1
#define FALSE 0

void dfs(int **g, int *used, int v, int n)
{
    used[v] = TRUE;
    int i;
    for (i = 0; i < n; i++)
        if ((used[i] == FALSE) && (g[v][i] == TRUE))
            dfs(g, used, i, n);
}

int main() 
{

    int i, j;
    int **graph;
    int *used;
    int n, s;
    int count = 0;

    // n - graph dim
    // s - start 
    scanf("%d%d", &n, &s);
    s--; // numbering start with 0

    graph = (int**) err_malloc(sizeof(int*) * n);
    used = (int*) err_malloc(sizeof(int) * n);

    /* Graph Example 
        n = 3
       --------------
        0 1 1
        1 0 0
        1 0 0
       --------------
                      */  

    for (i = 0; i < n; i++)
    {
        graph[i] = err_malloc(sizeof(int) * n);
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

        used[i] = FALSE;
    }
    dfs(graph, used, s, n);

    for (i = 0; i < n; i++)
        free(graph[i]);

    free(graph);
    free(used);
    return 0;
}
