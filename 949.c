#include <stdio.h>
#include <limits.h>

void print(int *x, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", x[i]);
    printf("\n");
}

void swap(int *i, int *j)
{
    int t = *i;
    *i = *j;
    *j = t;
}

typedef struct
{
    int flag;
    int *first;
    int *last;
} ret;

// Assert: x[-1] == INT_MIN; x[n] == INT_MAX
ret through(int *x, int *end)
{
    ret r;
    r.flag = 0;
    r.first = end;
    for (int *i = x, *j = x + 1; j < end; i++, j++)
    {
        if (!(*i <= *j))
        {
            swap(i, j);
            r.flag |= 1;
            (i < r.first) ? (r.first = i) : 0;
            r.last = i;
        }
    }
    return r;
}

int main()
{
    int n;
    scanf("%d", &n);
    int x[n + 2];
    x[0] = INT_MIN;
    x[n + 1] = INT_MAX;
    for (int i = 1; i < n + 1; i++)
        scanf("%d", x + i);
    ret r;
    r.first = x + 1;
    r.last = x + 1 + n;
    do
    {
        r = through(r.first - 1, r.last + 1);
        print(x + 1, n);
    } while (!(!r.flag || r.first == x + n + 1 || r.last == x + 1));
    return 0;
}
