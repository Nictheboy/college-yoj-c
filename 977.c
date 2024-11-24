#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#define MAX_N 10000

int n_children[MAX_N];
int children[MAX_N][MAX_N];

int n_stack, stack[MAX_N];
bool printed[MAX_N * MAX_N];

int cmp(const void *pa, const void *pb) { return *(int *)pa - *(int *)pb; }

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        --v1, --v2;
        children[v1][n_children[v1]++] = v2;
        children[v2][n_children[v2]++] = v1;
    }
    for (int i = 0; i < n; i++)
        qsort(children[i], n_children[i], sizeof(int), cmp);
    stack[n_stack++] = 0;
    while (n_stack > 0)
    {
        int x = stack[--n_stack];
        if (!printed[x])
        {
            printf("%d ", x + 1);
            printed[x] = true;
            for (int i = n_children[x] - 1; i >= 0; i--)
                stack[n_stack++] = children[x][i];
        }
    }
    printf("\n");
    return 0;
}
