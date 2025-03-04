#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

int l, n, m, x[50000];

// return d <= ans, that is, removed_points <= m
bool test(int d)
{
    int removed_points = 0;
    int x_start = 0;
    for (int i = 0; i < n; i++)
    {
        if (x[i] - x_start >= d)
            x_start = x[i];
        else
            removed_points++;
    }
    if (l - x_start < d)
        removed_points++;
    return removed_points <= m;
}

int main()
{
    scanf("%d%d%d", &l, &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);
    int low = 1, high = l + 1;
    while (low + 1 < high)
    {
        int mid = (low + high) / 2;
        bool result = test(mid);
        if (result)
            low = mid;
        else
            high = mid;
    }
    assert(low + 1 == high);
    printf("%d\n", low);
    return 0;
}
