#include <stdio.h>

int n, tree[5000];

int parent(int idx) { return (idx - 1) / 2; }
int lchild(int idx) { return idx * 2 + 1; }
int rchild(int idx) { return idx * 2 + 2; }

void access(int idx)
{
    printf("%d ", tree[idx]);
}

int find(int idx, int val)
{
    if (tree[idx] == val)
        return idx;
    int l = lchild(idx);
    int r = rchild(idx);
    if (l < n)
    {
        int ret = find(l, val);
        if (ret >= 0)
            return ret;
    }
    if (r < n)
    {
        int ret = find(r, val);
        if (ret >= 0)
            return ret;
    }
    return -1;
}

int prev(int idx)
{
    int l = lchild(idx);
    if (l < n)
    {
        int r = l;
        while (1)
        {
            int rr = rchild(r);
            if (!(rr < n))
                return r;
            else
                r = rr;
        }
    }
    int p = idx;
    while (1)
    {
        idx = p;
        p = parent(idx);
        if (p == idx)
            return -1;
        if (idx == rchild(p))
            return p;
    };
}

int next(int idx)
{
    int r = rchild(idx);
    if (r < n)
    {
        int l = r;
        while (1)
        {
            int ll = lchild(l);
            if (!(ll < n))
                return l;
            else
                l = ll;
        }
    }
    int p = idx;
    while (1)
    {
        idx = p;
        p = parent(idx);
        if (p == idx)
            return -1;
        if (idx == lchild(p))
            return p;
    };
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &tree[i]);
    int val;
    scanf("%d", &val);
    int idx = find(0, val);
    access(prev(idx));
    access(next(idx));
    printf("\n");
    return 0;
}
