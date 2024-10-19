#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>

int max(int a, int b) { return a > b ? a : b; }

void batch(int *primes, int *pn_primes, int begin, int end)
{
    if (begin % 2 == 0)
        begin += 1;
    int factor_upper_limit = 1 + (int)round(sqrt(end - 2));
    factor_upper_limit += 1 - factor_upper_limit % 2;

    for (int i = begin; i < factor_upper_limit; i += 2)
    {
        int flag = 0;
        for (int j = 0; j < *pn_primes; j++)
            if (i % primes[j] == 0)
            {
                flag = 1;
                break;
            }
        if (!flag)
            primes[(*pn_primes)++] = i;
    }

    int n_primes_factor_upper_limit = 0;
    while (n_primes_factor_upper_limit < *pn_primes && primes[n_primes_factor_upper_limit] < factor_upper_limit)
        n_primes_factor_upper_limit++;

    begin = max(begin, factor_upper_limit);
    char map[end - begin];
    memset(map, 0x00, end - begin);
    for (int j = 1; j < n_primes_factor_upper_limit; j++)
    {
        int p = primes[j];
        int first = begin / p * p;
        if (first < begin)
            first += p;
        for (int i = first; i < end; i += p)
            map[i - begin] = 1;
    }
    for (int i = begin; i < end; i += 2)
        if (!map[i - begin])
            primes[(*pn_primes)++] = i;
}

int main()
{
    int n;
    scanf("%d", &n);
    int *primes = malloc(sizeof(int) * n);
    int n_primes = 0;

    primes[n_primes++] = 2;

    int n_split = n / 2000 + 2;
    int split[n_split - 1];
    int delta = (n - 3) / n_split;
    split[0] = 3 + delta;
    for (int i = 1; i < n_split - 1; i++)
        split[i] = split[i - 1] + delta;

    batch(primes, &n_primes, 3, split[0]);
    for (int i = 1; i < n_split - 1; i++)
        batch(primes, &n_primes, split[i - 1], split[i]);
    batch(primes, &n_primes, split[n_split - 2], n + 1);

    for (int i = 0; i < n_primes; i++)
        printf("%d\n", primes[i]);

    free(primes);
    return 0;
}
