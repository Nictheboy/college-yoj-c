#include <stdio.h>
#include <stdlib.h>

int *cal_pmax(int *begin, int *end)
{
    int *pmax = begin;
    for (int *p = begin; p < end; p++)
        if (*p > *pmax)
            pmax = p;
    return pmax;
}

int *cal_pmin(int *begin, int *end)
{
    int *pmin = begin;
    for (int *p = begin; p < end; p++)
        if (*p < *pmin)
            pmin = p;
    return pmin;
}

int max(int a, int b, int c)
{
    if (a >= b && a >= c)
        return a;
    if (b >= a && b >= c)
        return b;
    return c;
}

int cal_max_delta(int *begin, int *end, int *pmin, int *pmax)
{
    if (pmin <= pmax)
        return *pmax - *pmin;
    int *mid = begin + (end - begin) / 2;
    int *pmin_of_frag_1 = cal_pmin(begin, mid);
    int *pmax_of_frag_1 = cal_pmax(begin, mid);
    int *pmin_of_frag_2 = cal_pmin(mid, end);
    int *pmax_of_frag_2 = cal_pmax(mid, end);
    int max_delta_of_frag_1 = cal_max_delta(begin, mid, pmin_of_frag_1, pmax_of_frag_1);
    int max_delta_of_frag_2 = cal_max_delta(mid, end, pmin_of_frag_2, pmax_of_frag_2);
    return max(max_delta_of_frag_1, max_delta_of_frag_2, *pmax_of_frag_2 - *pmin_of_frag_1);
}

int main()
{
    int n;
    scanf("%d", &n);
    int *sigma = malloc(sizeof(int) * (n + 1));

    sigma[0] = 0;
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        sigma[i + 1] = sigma[i] + x;
    }

    int *pmin = cal_pmin(sigma, sigma + n + 1);
    int *pmax = cal_pmax(sigma, sigma + n + 1);
    int answer = cal_max_delta(sigma, sigma + n + 1, pmin, pmax);

    printf("%d\n", answer);

    free(sigma);
    return 0;
}
