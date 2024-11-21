#include <stdio.h>

int n, tree[5000];

int parent(int idx) { return (idx - 1) / 2; }
int lchild(int idx) { return idx * 2 + 1; }
int rchild(int idx) { return idx * 2 + 2; }

void access(int idx)
{
    printf("%d ", tree[idx]);
}

void preorder(int idx)
{
    int l = lchild(idx);
    int r = rchild(idx);
    access(idx);
    if (l < n)
        preorder(l);
    if (r < n)
        preorder(r);
}

void inorder(int idx)
{
    int l = lchild(idx);
    int r = rchild(idx);
    if (l < n)
        inorder(l);
    access(idx);
    if (r < n)
        inorder(r);
}

void postorder(int idx)
{
    int l = lchild(idx);
    int r = rchild(idx);
    if (l < n)
        postorder(l);
    if (r < n)
        postorder(r);
    access(idx);
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &tree[i]);
    preorder(0);
    printf("\n");
    inorder(0);
    printf("\n");
    postorder(0);
    printf("\n");
    return 0;
}
