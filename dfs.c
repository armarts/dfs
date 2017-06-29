#include <stdio.h>

#include "err_malloc.h"
#include "fatal.h"

#define TRUE 1
#define FALSE 0

enum ERROR
{
    OK,
    INVALIDARG,
    BADARG
};

int dfs(int **g, char *used, int v, int n)
{
    if (g == NULL || used == NULL)
        return INVALIDARG;

    if ((n < 0) || (v < 0) || (v > n))
        return BADARG;

    used[v] = TRUE;
    int i;
    for (i = 0; i < n; i++)
        if ((used[i] == FALSE) && (g[v][i] == TRUE))
        {
            int err = dfs(g, used, i, n);
            if (err != OK)
                return err;
        }
    
    return OK;
}

int main() 
{

    int i, j;
    int **graph;
    int n, s;
    int count = 0;

    char *used;
    // n - graph dim
    // s - start 
    scanf("%d%d", &n, &s);
    s--; // numbering start with 0

    if (n < 0)
        fatal("Error: n must be positive");

    if (s < 0 || s > n)
        fatal("Error: 1 <= s <= n");

    graph = (int**) err_malloc(sizeof(int*) * n);
    used = (char*) err_malloc(sizeof(char) * n);

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
        graph[i] = (int*) err_malloc(sizeof(int) * n);
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

        used[i] = FALSE;
    }
    int err = dfs(graph, used, s, n);
    if (err != OK)
        printf("Error: error code - %d\n", err);

    for (i = 0; i < n; i++)
        free(graph[i]);

    free(graph);
    free(used);
    return 0;
}
