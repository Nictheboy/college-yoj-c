#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define EMPTY INT_MIN

int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

// assert: size > 0
int merge(int *data, int size)
{
    qsort(data, size, sizeof(int), cmp);
    int old = data[0] - 1;
    for (int i = 0, j = 0; j < size; i++)
    {
        if (data[i] == old)
        {
            size--;
            continue;
        }
        old = data[j++] = data[i];
    }
    return size;
}

int main()
{
    int n;
    scanf("%d", &n);
    int *data = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &data[i]);
    int n2 = merge(data, n);
    printf("%d\n", n - n2);
    free(data);
    return 0;
}
