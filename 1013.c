#include <stdio.h>

#define int long long

int n, height, tree[2000000];
int begin(int h) { return (1 << h) - 1; }
int lchild(int idx) { return 2 * idx + 1; }
int rchild(int idx) { return 2 * idx + 2; }
int parent(int idx) { return (idx - 1) >> 1; }

void increase(int id, int val)
{
    int idx = begin(height) + id;
    while (idx >= 0)
    {
        tree[idx] += val;
        idx = parent(idx);
    }
}

int count(int id_low, int id_high)
{
    int h = -1, sum = 0, current_low = 0, current_high = 0;
    while (current_low >= current_high)
    {
        ++h;
        current_low = (id_low >> (height - h)) + (h != height);
        current_high = id_high >> (height - h);
    }
    for (int i = begin(h) + current_low; i < begin(h) + current_high; i++)
        sum += tree[i];
    for (++h; h <= height; h++)
    {
        int old_low = current_low << 1;
        int old_high = current_high << 1;
        int new_low = (id_low >> (height - h)) + (h != height);
        int new_high = id_high >> (height - h);
        for (int i = begin(h) + new_low; i < begin(h) + old_low; i++)
            sum += tree[i];
        for (int i = begin(h) + old_high; i < begin(h) + new_high; i++)
            sum += tree[i];
        current_low = new_low, current_high = new_high;
    }
    return sum;
}

signed main()
{
    int q;
    scanf("%lld%lld", &n, &q);
    for (height = 0; 1 << height < n; height++)
        ;
    for (int i = begin(height); i < begin(height) + n; i++)
        scanf("%lld", &tree[i]);
    for (int h = height - 1; h >= 0; h--)
        for (int i = begin(h); i < begin(h + 1); i++)
            tree[i] = tree[lchild(i)] + tree[rchild(i)];
    for (int i = 0; i < q; i++)
    {
        int op, x1, x2;
        scanf("%lld%lld%lld", &op, &x1, &x2);
        if (op == 1)
            increase(x1 - 1, x2);
        else
            printf("%lld\n", count(x1 - 1, x2));
    }
    return 0;
}
