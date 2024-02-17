#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int n;
    int n_queen;
    int *queen;
    bool *column;
    bool *diagonal_1; // index = r + c
    bool *diagonal_2; // index = r + (n-1) - c
} problem;

void problem_init(problem *p, int n)
{
    p->n = n;
    p->n_queen = 0;
    p->queen = (int *)malloc(sizeof(int) * n);
    p->column = (bool *)malloc(sizeof(bool) * n);
    p->diagonal_1 = (bool *)malloc(sizeof(bool) * (2 * n - 1));
    p->diagonal_2 = (bool *)malloc(sizeof(bool) * (2 * n - 1));
}

bool problem_legal_to_put(const problem *p, int c) // p->n_queen < n
{
    int r = p->n_queen;
    if (p->column[c])
        return false;
    if (p->diagonal_1[r + c])
        return false;
    if (p->diagonal_2[r + p->n - 1 - c])
        return false;
    return true;
}

void problem_put(problem *p, int c) // p->n_queen < n
{
    int r = p->n_queen;
    p->n_queen++;
    p->queen[r] = c;
    p->column[c] = true;
    p->diagonal_1[r + c] = true;
    p->diagonal_2[r + p->n - 1 - c] = true;
}

void problem_leave(problem *p, int c) // p->n_queen < n
{
    int r = p->n_queen - 1;
    p->n_queen--;
    p->column[c] = false;
    p->diagonal_1[r + c] = false;
    p->diagonal_2[r + p->n - 1 - c] = false;
}

/*
Recursive:
solve()
{
    if(n_queen == n-1){
        i:0->n-1
            if legal_to_put i
                count++
    }
    else{
        i:0->n-1
            if legal_to_put i{
                put(i)
                solve()
                leave(i)
            }
    }
}
*/

int solve(int n)
{
    problem p;
    problem_init(&p, n);
    int count = 0;
    int recursive_depth = 0;
    int *i_stack = (int *)malloc(sizeof(int) * n);
    int status = 0; // 0: from call 1: from return 2: next loop
    while (recursive_depth >= 0) {
        if (status == 1) {
            problem_leave(&p, i_stack[recursive_depth]);
            status = 2;
            continue;
        }
        if (status == 2) {
            i_stack[recursive_depth]++;
            if (i_stack[recursive_depth] < n) {
                if (problem_legal_to_put(&p, i_stack[recursive_depth])) {
                    problem_put(&p, i_stack[recursive_depth]);
                    recursive_depth++;
                    status = 0;
                    continue;
                } else {
                    status = 2;
                    continue;
                }
            } else {
                status = 1;
                recursive_depth--;
                continue;
            }
        }
        if (p.n_queen == n - 1) {
            for (int c = 0; c < n; c++) {
                if (problem_legal_to_put(&p, c)) {
                    count++;
                }
            }
            status = 1;
            recursive_depth--;
            continue;
        } else {
            i_stack[recursive_depth] = 0;
            if (problem_legal_to_put(&p, i_stack[recursive_depth])) {
                problem_put(&p, i_stack[recursive_depth]);
                recursive_depth++;
                status = 0;
                continue;
            }
            status = 2;
            continue;
        }
    }
    return count;
}

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d", solve(n));
    return 0;
}
