#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>

bool is_cal_max = false;
int empty() { return is_cal_max ? INT_MIN : INT_MAX; }
int minmax(int a, int b) { return (is_cal_max ^ (a > b)) ? b : a; }

int n, x[200];
int incr(int i) { return (i + 1) % n; }

int cache[200][200];
int sum[200][200];
int solve(int start, int end);
int solve_impl(int start, int end)
{
    if (end == incr(start))
        return x[start];
    int answer = empty();
    for (int mid = incr(start); mid != end; mid = incr(mid))
        answer = minmax(answer, solve(start, mid) + solve(mid, end) + sum[start][end]);
    return answer;
}
int solve(int start, int end)
{
    if (cache[start][end] >= 0)
        return cache[start][end];
    int answer = solve_impl(start, end);
    cache[start][end] = answer;
    fprintf(stderr, "solve(%d, %d) = %d\n", start, end, answer);
    return answer;
}
void init()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cache[i][j] = -1;
    for (int i = 0; i < n; i++)
        sum[i][incr(i)] = x[i];
    for (int l = 2; l < n; l++)
        for (int i = 0; i < n; i++)
            sum[i][(i + l) % n] = sum[i][(i + l - 1) % n] + x[(i + l - 1) % n];
}

int solve_ring()
{
    // int total = 0;
    // for (int i = 0; i < n; i++)
    //     total += x[i];
    int answer = empty();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j)
                answer = minmax(answer, solve(i, j) + solve(j, i));
    return answer;
}

signed main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);
    init();
    is_cal_max = false;
    printf("%d\n", solve_ring());
    init();
    is_cal_max = true;
    printf("%d\n", solve_ring());
    return 0;
}
