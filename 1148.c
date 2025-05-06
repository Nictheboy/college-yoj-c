#include <stdio.h>
#include <assert.h>

int min(int a, int b) { return a > b ? b : a; }

int cache[201][201][7];
int solve(int n, int m, int k);
int solve_impl(int n, int m, int k)
{
    assert(n >= 1);
    if (k == 1)
        return n <= m;
    int cnt = 0;
    for (int i = 1; i <= min(m, n - 1); i++)
        cnt += solve(n - i, i, k - 1);
    // fprintf(stderr, "solve(%d, %d, %d) = %d\n", n, m, k, cnt);
    return cnt;
}
int solve(int n, int m, int k)
{
    if (cache[n][m][k] >= 0)
        return cache[n][m][k];
    return cache[n][m][k] = solve_impl(n, m, k);
}
void init(int n, int k)
{
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            for (int r = 0; r <= k; r++)
                cache[i][j][r] = -1;
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    init(n, k);
    printf("%d\n", solve(n, n, k));
    return 0;
}
