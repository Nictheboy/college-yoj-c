/*
 *      This code is modified from my solution of YOJ-143.
 *      Time complexity = O(n!), better than n^2O(n!).
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef long long ll;

int n;
ll sum;

ll *k;

void init_k()
{
    k = (ll *)malloc(sizeof(ll) * n);
    ll *temp = (ll *)malloc(sizeof(ll) * n);
    for (int r = 1; r <= n; r++) {
        memcpy(temp, k, sizeof(ll) * n);
        k[0] = 1;
        k[r - 1] = 1;
        for (int i = 1; i < r - 1; i++) {
            k[i] = temp[i - 1] + temp[i];
        }
    }
    free(temp);
}

bool search(ll *data, bool *used, int depth)
{
    if (depth == n) {
        ll count = 0;
        for (int i = 0; i < n; i++)
            count += k[i] * data[i];
        if (count == sum) {
            for (int i = 0; i < n; i++)
                printf("%lld ", data[i]);
            return true;
        } else
            return false;
    }
    for (int i = 0; i < n; i++) {
        if (used[i])
            continue;
        used[i] = true;
        data[depth] = i + 1;
        if (search(data, used, depth + 1))
            return true;
        used[i] = false;
    }
    return false;
}

int main()
{
    // scanf("%d%lld", &n, &sum);
    n = 5;
    scanf("%lld", &sum);
    init_k();
    ll data[n];
    bool used[n];
    for (int i = 0; i < n; i++)
        used[i] = false;
    search(data, used, 0);
    return 0;
}
