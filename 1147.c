#include <stdio.h>
#include <assert.h>

#define int long long

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int n_remain_cnt, m_remain_cnt;
int n_remain[40], m_remain[40];

void build_remain(int n, int *remain_cnt, int remain[])
{
    for (*remain_cnt = 0; n > 1; (*remain_cnt)++)
    {
        remain[*remain_cnt] = n;
        n = (n + 1) / 2;
    }
    remain[(*remain_cnt)++] = 1;
}

int solve(int n, int m, int k)
{
    build_remain(n, &n_remain_cnt, n_remain);
    build_remain(m, &m_remain_cnt, m_remain);
    if (k >= (n_remain_cnt - 1) + (m_remain_cnt - 1))
        return n * m - 1;
    int remain_min = n * m;
    for (int x = max(0, k - (m_remain_cnt - 1)); x < min(n_remain_cnt, k + 1); x++)
    {
        assert(k - x < m_remain_cnt);
        remain_min = min(remain_min, n_remain[x] * m_remain[k - x]);
    }
    return n * m - remain_min;
}

signed main()
{
    int T;
    scanf("%lld", &T);
    for (int i = 0; i < T; i++)
    {
        int n, m, k;
        scanf("%lld%lld%lld", &n, &m, &k);
        int result = solve(n, m, k);
        printf("%lld\n", result);
    }
    return 0;
}
