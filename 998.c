#include <stdio.h>
#include <stdlib.h>

#define unlikely(A) __builtin_expect((A), 0)

typedef struct
{
    int index;
    int data;
} indexed_int;

int cmp(const void *pa, const void *pb)
{
    return ((indexed_int *)pa)->data - ((indexed_int *)pb)->data;
}

int main()
{
    int n, target;
    scanf("%d%d", &n, &target);
    indexed_int *x = malloc(sizeof(indexed_int) * n);

    for (int i = 0; i < n; i++)
    {
        x[i].index = i;
        scanf("%d", &x[i].data);
    }

    qsort(x, n, sizeof(indexed_int), cmp);

    indexed_int *p = x, *q = x + n - 1;
    while (1)
    {
        if (unlikely(!(p < q)))
        {
            printf("-1\n");
            break;
        }
        int sum = p->data + q->data;
        if (sum > target)
            q--;
        if (sum < target)
            p++;
        if (unlikely(sum == target))
        {
            if (p->index < q->index)
                printf("%d %d\n", p->index, q->index);
            else
                printf("%d %d\n", q->index, p->index);
            break;
        }
    }

    free(x);
    return 0;
}
