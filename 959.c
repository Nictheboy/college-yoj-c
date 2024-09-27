#include <stdio.h>

void merge(int *begin, int *mid, int *end)
{
    int temp[end - begin];
    int *i = temp, *p = begin, *q = mid;
    while (p < mid && q < end)
    {
        int a = *p, b = *q;
        int cond = a < b;
        *(i++) = cond ? a : b;
        p += cond;
        q += !cond;
    }
    for (; p < mid; p++)
        *(i++) = *p;
    for (; q < end; q++)
        *(i++) = *q;
    for (int *j = temp, *r = begin; r < end; j++, r++)
        *r = *j;
}

void sort(int *begin, int *end)
{
    if (end - begin <= 1)
        return;
    int *mid = begin + (end - begin) / 2;
    sort(begin, mid);
    sort(mid, end);
    merge(begin, mid, end);
}

int main()
{
    int n;
    scanf("%d", &n);
    int x[n];
    for (int i = 0; i < n; i++)
        scanf("%d", x + i);
    sort(x, x + n);
    for (int i = 0; i < n; i++)
        printf("%d ", x[i]);
}
