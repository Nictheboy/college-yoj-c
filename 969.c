#include <stdio.h>
#include <stdlib.h>

int try(int *x, int *end, int m, int h)
{
    long long sum = 0;
    for (int *p = x; p < end; p++)
        sum += (*p > h) ? (*p - h) : 0;
    // printf("try(%d): sum = %lld\n", h, sum);
    return sum >= m;
}

int h_max(int *x, int *end, int m)
{
    int min, max, guess = m / (end - x) + 1;
    if (try(x, end, m, guess))
    {
        min = guess;
        do
            guess *= 2;
        while (try(x, end, m, guess));
        max = guess;
    }
    else
    {
        max = guess;
        do
            guess /= 2;
        while (!try(x, end, m, guess));
        min = guess;
    }
    while (max - min > 1)
    {
        int mid = min + (max - min) / 2;
        if (try(x, end, m, mid))
            min = mid;
        else
            max = mid;
    }
    return min;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int *x = malloc(sizeof(int) * n), *end = x + n;
    for (int *p = x; p < end; p++)
        scanf("%d", p);
    int h = h_max(x, end, m);
    printf("%d\n", h);
    free(x);
    return 0;
}
