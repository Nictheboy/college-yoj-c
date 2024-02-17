#include <stdio.h>
#include <stdlib.h>

int n, m;
int *weight;   // m*n,index=i+j*m
int *distance; // m*n,index=i+j*m

int cal(int i, int j, int i0) // j>=2
{
    int ret = 0;
    int *row = weight + j * m;
    if (i0 <= i) {
        for (int k = i0; k <= i; k++)
            ret += row[k];
    } else {
        for (int k = i0; k >= i; k--)
            ret += row[k];
    }
    return ret;
}

void search(int i, int j) // j>=2
{
    int *row = distance + (j - 1) * m;
    int best = row[0] + cal(i, j, 0);
    for (int i0 = 1; i0 < m; i0++) {
        int res = row[i0] + cal(i, j, i0);
        if (res > best)
            best = res;
    }
    distance[i + j * m] = best;
}

int main()
{
    scanf("%d %d", &n, &m);
    weight = (int *)malloc(sizeof(int) * n * m);
    distance = (int *)malloc(sizeof(int) * n * m);
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            scanf("%d", &weight[i + j * m]);
        }
    }

    distance[0] = weight[0];
    for (int i = 1; i < m; i++) {
        distance[i] = distance[i - 1] + weight[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < m; i++) {
            search(i, j);
        }
    }

    printf("%d", distance[m - 1 + (n - 1) * m]);
    return 0;
}
