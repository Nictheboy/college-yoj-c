#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#define MAX_N 10000

int n_children[MAX_N];
int children[MAX_N][MAX_N];
bool removed[MAX_N];
int n_stack, stack[MAX_N];

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
    }
    for (int i = 0; i < n; i++)
        qsort(children[i], n_children[i], sizeof(int), cmp);
    while (true)
    {
        int x = -1;
        for (int i = n - 1; i >= 0; i--)
        {
            bool flag = !removed[i];
            if (flag)
                for (int j = 0; j < n_children[i]; j++)
                    if (!removed[children[i][j]])
                    {
                        flag = false;
                        break;
                    }
            if (flag)
            {
                x = i;
                break;
            }
        }
        if (x == -1)
            break;
        stack[n_stack++] = x;
        removed[x] = true;
    }
    while (n_stack > 0)
        printf("%d ", stack[--n_stack] + 1);
    printf("\n");
    return 0;
}