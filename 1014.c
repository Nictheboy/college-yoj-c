#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#define MAX_N 10000

int n_children[MAX_N];
int children[MAX_N][MAX_N];

int i_queue, j_queue;
int queue[MAX_N];
bool enqueued[MAX_N];
int distance[MAX_N];

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
        distance[i] = -1;
    queue[j_queue++] = 0;
    enqueued[0] = true;
    distance[0] = 0;
    while (j_queue != i_queue)
    {
        int x = queue[i_queue++];
        for (int i = 0; i < n_children[x]; i++)
        {
            int neighbor = children[x][i];
            if (!enqueued[neighbor])
            {
                queue[j_queue++] = neighbor;
                enqueued[neighbor] = true;
                distance[neighbor] = distance[x] + 1;
            }
        }
    }
    for (int i = 0; i < n; i++)
        printf("%d ", distance[i]);
    printf("\n");
    return 0;
}
