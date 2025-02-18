#include <stdio.h>
#include <assert.h>

int x[4000000];

int *partition(int *begin, int *last)
{
    int pivot = *begin;
    while (begin != last)
    {
        while (begin != last && pivot <= *last)
            last--;
        if (begin == last)
            break;
        *(begin++) = *last;
        while (begin != last && *begin <= pivot)
            begin++;
        if (begin == last)
            break;
        *(last--) = *begin;
    }
    assert(begin == last);
    *begin = pivot;
    return begin;
}

int select_k(int *begin, int *last, int k)
{
    int *p_pivot = partition(begin, last);
    int idx_pivot = p_pivot - begin;
    if (idx_pivot == k)
        return *p_pivot;
    if (idx_pivot < k)
        return select_k(p_pivot + 1, last, k - idx_pivot - 1);
    if (idx_pivot > k)
        return select_k(begin, p_pivot - 1, k);
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);
    int y = select_k(x, x + n - 1, k - 1);
    printf("%d\n", y);
}
