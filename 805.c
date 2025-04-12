#include <stdio.h>
#include <limits.h>
#include <assert.h>

int min(int a, int b) { return a < b ? a : b; }
int add(int a, int b)
{
    assert(a >= 0 && b >= 0);
    return (a == INT_MAX || b == INT_MAX) ? INT_MAX : a + b;
}

int n, e[100][100];
int d[100][100][100]; // d[i][j][k] := dist from i to j with <= k edges

void floyd()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            d[i][j][0] = i == j ? 0 : INT_MAX;
    for (int k = 1; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                int d_min = d[i][j][k - 1];
                for (int p = 0; p < n; p++)
                    d_min = min(d_min, add(d[i][p][k - 1], e[p][j]));
                d[i][j][k] = d_min;
            }
}

int main()
{
    int m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            e[i][j] = INT_MAX;
    for (int i = 0; i < m; i++)
    {
        int p, q, l;
        scanf("%d%d%d", &p, &q, &l);
        e[p - 1][q - 1] = l;
    }
    floyd();
    for (int i = 0; i < q; i++)
    {
        int p, q;
        scanf("%d%d", &p, &q);
        int ans = d[p - 1][q - 1][n - 1];
        if (ans == INT_MAX)
            printf("inf\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}
