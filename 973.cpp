#include <stdio.h>
#include <queue>

int n, tree[5000];

int parent(int idx) { return (idx - 1) / 2; }
int lchild(int idx) { return idx * 2 + 1; }
int rchild(int idx) { return idx * 2 + 2; }

void access(int idx)
{
    printf("%d ", tree[idx]);
}

void iterate(int idx)
{
    std::queue<int> q;
    q.push(idx);
    while (!q.empty())
    {
        idx = q.front();
        q.pop();
        access(idx);
        int l = lchild(idx);
        int r = rchild(idx);
        if (l < n)
            q.push(l);
        if (r < n)
            q.push(r);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &tree[i]);
    iterate(0);
    printf("\n");
    return 0;
}
