#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

int n, n_remain;
int cards[1000000];

bool judge4(int a, int b, int c, int d)
{
    bool ok = false;
    ok |= a == b + c + d;
    ok |= b == c + d + a;
    ok |= c == d + a + b;
    ok |= d == a + b + c;
    ok |= a + b == c + d;
    ok |= b + c == d + a;
    ok |= a + c == b + d;
    return ok;
}

bool judge3(int a, int b, int c)
{
    return a == b + c || b == c + a || c == a + b;
}

int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

bool handout()
{
    if (n_remain < 4)
        return false;
    if (judge4(cards[n_remain - 4], cards[n_remain - 3], cards[n_remain - 2], cards[n_remain - 1]))
    {
        n_remain -= 4;
        return true;
    }
    qsort(&cards[n_remain - 4], 4, sizeof(int), cmp);
    if (judge3(cards[n_remain - 3], cards[n_remain - 2], cards[n_remain - 1]))
    {
        n_remain -= 3;
        return true;
    }
    if (judge3(cards[n_remain - 4], cards[n_remain - 2], cards[n_remain - 1]))
    {
        cards[n_remain - 4] = cards[n_remain - 3];
        n_remain -= 3;
        return true;
    }
    if (judge3(cards[n_remain - 4], cards[n_remain - 3], cards[n_remain - 1]))
    {
        cards[n_remain - 4] = cards[n_remain - 2];
        n_remain -= 3;
        return true;
    }
    if (judge3(cards[n_remain - 4], cards[n_remain - 3], cards[n_remain - 2]))
    {
        cards[n_remain - 4] = cards[n_remain - 1];
        n_remain -= 3;
        return true;
    }
    if (cards[n_remain - 1] == cards[n_remain - 2])
    {
        n_remain -= 2;
        return true;
    }
    if (cards[n_remain - 2] == cards[n_remain - 3])
    {
        cards[n_remain - 3] = cards[n_remain - 1];
        n_remain -= 2;
        return true;
    }
    if (cards[n_remain - 3] == cards[n_remain - 4])
    {
        cards[n_remain - 3] = cards[n_remain - 1];
        cards[n_remain - 4] = cards[n_remain - 2];
        n_remain -= 2;
        return true;
    }
    return false;
}

int main()
{
    scanf("%d", &n);
    assert(n <= 1000000);
    n_remain = n;
    for (int i = 0; i < n; i++)
        scanf("%d", &cards[i]);
    while (handout())
        ;
    printf("%d\n", n - n_remain);
    return 0;
}
