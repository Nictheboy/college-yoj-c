#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int max(int a, int b) { return a > b ? a : b; }

int k, n, m;
int man[100][100];  // 要塞 j 被玩家 i 的 man[i][j] 名士兵攻击
int cost[100][100]; // 第 j + 1 次获得要塞 i 总计需要 cost[i][j] 名士兵

int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }
void init_values()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
            cost[i][j] = 2 * man[j][i] + 1;
        qsort(cost[i], k, sizeof(int), cmp);
    }
}

int solve(int n0, int m0); // 如果只有前 k0 个要塞和 m0 个士兵，问题的答案是多少
int cache[101][20001];
void init_cache()
{
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            cache[i][j] = -1;
}
int solve_impl(int n0, int m0)
{
    if (n0 == 0)
        return 0;
    int max_score = solve(n0 - 1, m0);
    for (int i = 0; i < k; i++)
        if (m0 >= cost[n0 - 1][i])
            max_score = max(max_score, solve(n0 - 1, m0 - cost[n0 - 1][i]) + (i + 1) * n0);
    return max_score;
}
int solve(int n0, int m0)
{
    assert(0 <= n0 && n0 <= n && 0 <= m0 && m0 <= m);
    if (cache[n0][m0] >= 0)
        return cache[n0][m0];
    int result = solve_impl(n0, m0);
    // fprintf(stderr, "solve(%d, %d) = %d\n", n0, m0, result);
    return cache[n0][m0] = result;
}

int main()
{
    scanf("%d%d%d", &k, &n, &m);
    for (int i = 0; i < k; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &man[i][j]);
    init_values();
    init_cache();
    printf("%d\n", solve(n, m));
    return 0;
}
