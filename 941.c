
//          Warning:
//      This algrithm is NOT CORRECT!
//      DO NOT COMMIT IT TO OJ!


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(A, B) ((A) < (B) ? (A) : (B))

int m, n;
int *p;  // [n]
int *p2; // [n]
int *q;  // [m]
int target;

int p2_for(int u)
{
    int x1 = p[u];
    int min = abs(x1 - p[q[0]]);
    for (int k = 1; k < m; k++) {
        min = MIN(min, abs(x1 - p[q[k]]));
    }
    return min;
}

void reset_p2()
{
    for (int u = 0; u < n; u++) {
        p2[u] = p2_for(u);
    }
}

int cal_target()
{
    int tar = 0;
    for (int u = 0; u < n; u++)
        tar += p2[u];
    return tar;
}

void init()
{
    scanf("%d%d", &n, &m);
    p = (int *)malloc(sizeof(int) * n);
    p[0] = 0;
    for (int u = 1; u < n; u++) {
        int d;
        scanf("%d", &d);
        p[u] = p[u - 1] + d;
    }
    q = (int *)malloc(sizeof(int) * m);
    for (int k = 0; k < m; k++)
        q[k] = k;
    p2 = (int *)malloc(sizeof(int) * n);
    reset_p2();
    target = cal_target();
}

int p2_aft_for(int u, int k, int u2)
{
    int pqk = p[q[k]];
    int pu = p[u];
    int dis = abs(pu - p[u2]);
    int p2u = p2[u];
    if (dis < p2u) {
        return dis;
    } else {
        if (abs(pu - pqk) == p2u) {
            int resetter = q[k];
            q[k] = u2;
            int ret = p2_for(u);
            q[k] = resetter;
            return ret;
        } else {
            return p2u;
        }
    }
}

int delta(int k, int u2)
{
    int delta = 0;
    for (int u = 0; u < n; u++) {
        delta += p2_aft_for(u, k, u2) - p2[u];
    }
    return delta;
}

void commit(int k, int u2)
{
    target = 0;
    for (int u = 0; u < n; u++) {
        int v = p2_aft_for(u, k, u2);
        p2[u] = v;
        target += v;
    }
    q[k] = u2;
}

bool try_opt_first()
{
    int u_qka1 = q[1];
    for (int u2 = 0; u2 < u_qka1; u2++) {
        if (delta(0, u2) < 0) {
            commit(0, u2);
            return true;
        }
    }
    return false;
}

bool try_opt_last()
{
    int u_qkm1 = q[m - 2];
    for (int u2 = u_qkm1 + 1; u2 < m; u2++) {
        if (delta(m - 1, u2) < 0) {
            commit(m - 1, u2);
            return true;
        }
    }
    return false;
}

bool try_opt(int k) // 1 <= k <= m-2
{
    int u_qkm1 = q[k - 1];
    int u_qka1 = q[k + 1];
    for (int u2 = u_qkm1 + 1; u2 < u_qka1; u2++) {
        if (delta(k, u2) < 0) {
            commit(k, u2);
            return true;
        }
    }
    return false;
}

int main()
{
    init();
    bool flag = true;
    while (flag) {
        flag = false;
        if (try_opt_first()) {
            flag = true;
        }
        for (int k = 1; k < m - 1; k++) {
            if (try_opt(k)) {
                flag = true;
            }
        }
        if (try_opt_last()) {
            flag = true;
        }
    }
    printf("%d", target);
    return 0;
}
