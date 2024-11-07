#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

int n, k;
int nums[100000];
int sums[100001];
int next[100001];
int prev[100001];

void build_next()
{
    next[n] = -1;
    for (int i = n - 1; i >= 0; i--)
    {
        next[i] = -1;
        for (int j = i + 1; j != -1; j = next[j])
            if (sums[i] < sums[j])
            {
                next[i] = j;
                break;
            }
    }
}

int min(int a, int b) { return a < b ? a : b; }

int solve()
{
    int to = 1, shortest = INT_MAX;
    for (int from = 0; from < n; from++)
    {
        int target = sums[from] + k;
        while (sums[to] < target)
        {
            int previous_to = to;
            to = next[to];
            if (to < 0)
                goto next_from;
            prev[to] = previous_to;
        }
        assert(sums[to] >= target);
        while (true)
        {
            int previous_to = prev[to];
            if (previous_to > from)
            {
                if (sums[previous_to] >= target)
                    to = previous_to;
                else
                    break;
            }
            else
            {
                for (to = from + 1; to <= n && sums[to] < target; to++)
                    prev[to] = to - 1;
                if (to > n)
                    goto next_from;
                break;
            }
        }
        assert(sums[to] >= target);
        shortest = min(shortest, to - from);
    next_from:
        to = from + 2;
    }
    return shortest == INT_MAX ? -1 : shortest;
}

int main()
{
    scanf("%d%d", &n, &k);
    int sum = 0;
    sums[0] = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &nums[i]);
        sum += nums[i];
        sums[i + 1] = sum;
    }
    build_next();
    int result = solve();
    printf("%d", result);
    return 0;
}
