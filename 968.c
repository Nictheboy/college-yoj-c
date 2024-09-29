#include <stdio.h>
#include <stdlib.h>

int try_d(int *x, int *end, int m, int d)
{
    int cnt = 1, prev = *x;
    for (int *p = x + 1; p < end; p++)
    {
        if (*p - prev >= d)
            cnt++, prev = *p;
    }
    return cnt >= m;
}

int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int solve(int *x, int *end, int m)
{
    qsort(x, end - x, sizeof(int), cmp);
    int min, max, guess = (*(end - 1) - *x) / m;
    if (try_d(x, end, m, guess))
    {
        min = guess;
        do
        {
            guess *= 2;
        } while (try_d(x, end, m, guess));
        max = guess;
    }
    else
    {
        max = guess;
        do
        {
            guess /= 2;
        } while (!try_d(x, end, m, guess));
        min = guess;
    }
    while (max - min >= 2)
    {
        guess = min + (max - min) / 2;
        if (try_d(x, end, m, guess))
            min = guess;
        else
            max = guess;
    }
    return min;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int *x = malloc(sizeof(int) * n);
    int *end = x + n;
    for (int *p = x; p < end; p++)
        scanf("%d", p);
    int d_max = solve(x, end, m);
    printf("%d\n", d_max);
}
