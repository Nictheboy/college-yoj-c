#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdint.h>

#define int long long

int N, M, A[300000], B[300000];

// 除法（向上取整）
int div_up(int a, int b) { return a % b == 0 ? a / b : a / b + 1; }

// 推倒过程见草稿纸
int min_V_i(int A_i, int B_i, int F_0)
{
    assert(A_i >= 0 && B_i >= 0);
    if (A_i == 0 && B_i == 0)
        return INT_MAX;
    if (B_i >= A_i)
        return div_up(F_0, B_i);
    if (B_i == 0)
        return div_up(F_0, A_i);
    if (M * A_i >= F_0)
        return div_up(F_0, A_i);
    else
        return M + div_up(F_0 - M * A_i, B_i);
}

__int128_t min_V(int F_0)
{
    __int128_t sum = 0;
    for (int i = 0; i < N; i++)
        sum += min_V_i(A[i], B[i], F_0);
    // fprintf(stderr, "min_V(%lld) = %lld\n", (long long)F_0, (long long)sum);
    return sum;
}

// 二分搜索
int search(int begin, int end)
{
    if (end - begin == 1)
        return begin;
    int mid = begin + (end - begin) / 2;
    if (min_V(mid) <= (__int128_t)M * N)
        return search(mid, end);
    else
        return search(begin, mid);
}

// 计算 F 上限
int upper_bound()
{
    int max = 0;
    for (int i = 0; i < N; i++)
        if (A[i] > max)
            max = A[i];
    for (int i = 0; i < N; i++)
        if (B[i] > max)
            max = B[i];
    return max * M;
}

signed main()
{
    scanf("%lld%lld", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%lld", &A[i]);
    for (int i = 0; i < N; i++)
        scanf("%lld", &B[i]);
    printf("%lld\n", (long long)search(0, upper_bound() + 1));
    return 0;
}
