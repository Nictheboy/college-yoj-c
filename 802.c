#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int max(int x, int y) { return x < y ? y : x; }

typedef struct
{
    int begin, end, weight, prev;
} task;

int cmp(const void *a, const void *b)
{
    return ((task *)a)->end - ((task *)b)->end;
}

int n;
task x[100000];

typedef struct
{
    int task_idx;
    bool is_begin;
} time;
time times[200000];
int cmp2(const void *a, const void *b)
{
    time *a2 = (time *)a;
    time *b2 = (time *)b;
    int ta = a2->is_begin ? x[a2->task_idx].begin : x[a2->task_idx].end;
    int tb = b2->is_begin ? x[b2->task_idx].begin : x[b2->task_idx].end;
    int det = ta - tb;
    if (!det)
        det = a2->task_idx - b2->task_idx;
    return det;
}
void init_prev()
{
    for (int i = 0; i < n; i++)
    {
        times[i].is_begin = true;
        times[i].task_idx = i;
    }
    for (int i = 0; i < n; i++)
    {
        times[n + i].is_begin = false;
        times[n + i].task_idx = i;
    }
    qsort(times, 2 * n, sizeof(time), cmp2);
    int prev = -1;
    for (int i = 0; i < 2 * n; i++)
    {
        if (times[i].is_begin)
            x[times[i].task_idx].prev = prev;
        else
            prev = times[i].task_idx;
    }
}

int cache[100000];
int solve(int k);
int solve_impl(int k)
{
    return max(solve(x[k].prev) + x[k].weight, solve(k - 1));
}
int solve(int k)
{
    if (k < 0)
        return 0;
    if (cache[k] >= 0)
        return cache[k];
    int result = solve_impl(k);
    cache[k] = result;
    return result;
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d%d", &x[i].begin, &x[i].end, &x[i].weight);
    for (int i = 0; i < n; i++)
        cache[i] = -1;
    qsort(x, n, sizeof(task), cmp);
    init_prev();
    printf("%d\n", solve(n - 1));
    return 0;
}
