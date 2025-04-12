#include <stdio.h>
#include <assert.h>
#include <limits.h>

#define int long long
#define N_MAX 10000

int n, shape[N_MAX + 1];

int cache[N_MAX + 1][N_MAX + 1];
void init_cache()
{
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            cache[i][j] = -1;
}
int solve(int first, int last);
int solve_impl(int first, int last)
{
    assert(first < last);
    if (last - first == 1)
        return 0;
    int min = LLONG_MAX;
    for (int mid = first + 1; mid < last; mid++)
    {
        int curr = solve(first, mid) + solve(mid, last);
        curr += shape[first] * shape[mid] * shape[last];
        if (curr < min)
            min = curr;
    }
    return min;
}
int solve(int first, int last)
{
    if (cache[first][last] >= 0)
        return cache[first][last];
    int result = solve_impl(first, last);
    // fprintf(stderr, "solve(%lld, %lld) = %lld\n", first, last, result);
    cache[first][last] = result;
    return result;
}

signed main()
{
    scanf("%lld", &n);
    assert(n <= N_MAX);
    for (int i = 0; i < n; i++)
        scanf("%lld%lld", &shape[i], &shape[i + 1]);
    init_cache();
    printf("%lld\n", solve(0, n));
    return 0;
}
