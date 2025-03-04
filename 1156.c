#include <stdio.h>

#define int long long
int max(int a, int b) { return a > b ? a : b; }

int n, m, a[200000], b[200000];

int solve()
{
    int low = 0, high = 0;
    int a_sum = 0, b_sum = 0, b_sum_max = 0;
    for (; high < n; high++)
    {
        a_sum += a[high], b_sum += b[high];
        while (a_sum > m)
        {
            a_sum -= a[low], b_sum -= b[low];
            low++;
        }
        b_sum_max = max(b_sum_max, b_sum);
    }
    return b_sum_max;
}

signed main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++)
        scanf("%lld", &b[i]);
    int result = solve();
    printf("%lld\n", result);
    return 0;
}
