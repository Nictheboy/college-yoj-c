#include <stdio.h>
#include <assert.h>

int n_nodes, tree[10000], lchild[10000], rchild[10000];

int read()
{
    int c = getchar();
    assert(c == ',');
    c = getchar();
    if (c == '#')
        return -1;
    ungetc(c, stdin);
    int val;
    scanf("%d", &val);
    int idx_new = n_nodes++;
    tree[idx_new] = val;
    lchild[idx_new] = read();
    rchild[idx_new] = read();
    return idx_new;
}

int max_branch[10000], l_max_branch[10000], r_max_branch[10000];

int max(int a, int b) { return a < b ? b : a; }

void cal_max_branch(int idx)
{
    l_max_branch[idx] = 0, r_max_branch[idx] = 0;
    int l = lchild[idx], r = rchild[idx];
    if (l >= 0)
    {
        cal_max_branch(l);
        l_max_branch[idx] = max(0, tree[l] + max_branch[l]);
    }
    if (r >= 0)
    {
        cal_max_branch(r);
        r_max_branch[idx] = max(0, tree[r] + max_branch[r]);
    }
    max_branch[idx] = max(l_max_branch[idx], r_max_branch[idx]);
}

int main()
{
    int val_root;
    scanf("%d", &val_root);
    tree[n_nodes++] = val_root;
    lchild[0] = read();
    rchild[0] = read();
    cal_max_branch(0);

    int max_path = 0;
    for (int i = 0; i < n_nodes; i++)
        max_path = max(max_path, tree[i] + l_max_branch[i] + r_max_branch[i]);
    printf("%d\n", max_path);
    return 0;
}
