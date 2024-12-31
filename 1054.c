#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int *quick_partition(int *begin, int *end)
{
    int random_idx = rand() % (end - begin);
    int pivot = begin[random_idx];
    begin[random_idx] = *begin;
    int *low = begin, *high = end - 1;
    while (low < high)
    {
        while (low < high && pivot <= *high)
            high--;
        *low = *high;
        while (low < high && pivot >= *low)
            low++;
        *high = *low;
    }
    assert(low == high);
    *low = pivot;
    return low;
}

int quick_select(int *begin, int *end, int k)
{
    assert(0 <= k && k < end - begin);
    if (end - begin == 1)
        return *begin;
    int *pivot = quick_partition(begin, end);
    if (k < pivot - begin)
        return quick_select(begin, pivot, k);
    else if (k == pivot - begin)
        return *pivot;
    else
        return quick_select(pivot + 1, end, k - (pivot + 1 - begin));
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    int *x = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);
    printf("%d\n", quick_select(x, x + n, k - 1));
    free(x);
    return 0;
}
