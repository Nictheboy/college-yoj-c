#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define EMPTY INT_MIN

int merge(int *data, int size)
{
    int new_size = size;
    for (int i = 0; i < size; i++)
    {
        if (data[i] == EMPTY)
            continue;
        for (int j = i + 1; j < size; j++)
        {
            if (data[i] == data[j])
            {
                data[j] = EMPTY;
                new_size--;
            }
        }
    }
    for (int i = 0, j = 0; j < new_size; i++)
    {
        if (data[i] == EMPTY)
            continue;
        data[j++] = data[i];
    }
    return new_size;
}

int main()
{
    int n;
    scanf("%d", &n);
    int *data = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &data[i]);
    n = merge(data, n);
    printf("%d\n", n);
    for (int i = 0; i < n; i++)
        printf("%d ", data[i]);
    free(data);
}
