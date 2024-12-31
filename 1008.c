#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int main()
{
    int n;
    scanf("%d", &n);
    int *x = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);
    qsort(x, n, sizeof(int), cmp);
    int max = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int curr = x[i + 1] - x[i];
        max = curr > max ? curr : max;
    }
    printf("%d\n", max);
    free(x);
    return 0;
}
