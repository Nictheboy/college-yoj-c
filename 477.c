#include <stdio.h>

void print(int *x, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", x[i]);
    printf("\n");
}

void swap(int *x, int i, int j)
{
    int t = x[i];
    x[i] = x[j];
    x[j] = t;
}

int through(int *x, int n)
{
    int flag = 0;
    for (int i = 0, j = 1; j < n; i++, j++)
    {
        if (!(x[i] >= x[j]))
        {
            swap(x, i, j);
            flag |= 1;
        }
    }
    print(x, n);
    return flag;
}

int main()
{
    int n;
    scanf("%d", &n);
    int x[n];
    for (int i = 0; i < n; i++)
        scanf("%d", x + i);
    while (through(x, n))
        ;
    return 0;
}
