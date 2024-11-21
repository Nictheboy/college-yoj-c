#include <stdio.h>

int n, tree[5000];
int n_stack, stack[5000], status_stack[5000];

int parent(int idx) { return (idx - 1) / 2; }
int lchild(int idx) { return idx * 2 + 1; }
int rchild(int idx) { return idx * 2 + 2; }

void access(int idx)
{
    printf("%d ", tree[idx]);
}

void preorder(int idx)
{
    stack[n_stack++] = idx;
    while (n_stack > 0)
    {
        int parent = stack[--n_stack];
        int l = lchild(parent);
        int r = rchild(parent);
        access(parent);
        if (r < n)
            stack[n_stack++] = r;
        if (l < n)
            stack[n_stack++] = l;
    }
}

// Status Machine:
// enqueued -> 0 -[enqueue lchild]-> 1 -[access]-> 2 -[enqueue rchild]-> 3 -> dequeued
void inorder(int idx)
{
    status_stack[n_stack] = 0;
    stack[n_stack++] = idx;
    while (n_stack > 0)
    {
        int status = status_stack[n_stack - 1];
        int idx = stack[n_stack - 1];
        int l, r;
        switch (status)
        {
        case 0:
            status_stack[n_stack - 1] = 1;
            l = lchild(idx);
            if (l < n)
            {
                status_stack[n_stack] = 0;
                stack[n_stack++] = l;
            }
            break;
        case 1:
            status_stack[n_stack - 1] = 2;
            access(idx);
            break;
        case 2:
            status_stack[n_stack - 1] = 3;
            r = rchild(idx);
            if (r < n)
            {
                status_stack[n_stack] = 0;
                stack[n_stack++] = r;
            }
            break;
        case 3:
            --n_stack;
            break;
        }
    }
}

// Status Machine:
// enqueued -> 0 -[enqueue lchild]-> 1 -[enqueue rchild]-> 2 -[access]-> 3 -> dequeued
void postorder(int idx)
{
    status_stack[n_stack] = 0;
    stack[n_stack++] = idx;
    while (n_stack > 0)
    {
        int status = status_stack[n_stack - 1];
        int idx = stack[n_stack - 1];
        int l, r;
        switch (status)
        {
        case 0:
            status_stack[n_stack - 1] = 1;
            l = lchild(idx);
            if (l < n)
            {
                status_stack[n_stack] = 0;
                stack[n_stack++] = l;
            }
            break;
        case 1:
            status_stack[n_stack - 1] = 2;
            r = rchild(idx);
            if (r < n)
            {
                status_stack[n_stack] = 0;
                stack[n_stack++] = r;
            }
            break;
        case 2:
            status_stack[n_stack - 1] = 3;
            access(idx);
            break;
        case 3:
            --n_stack;
            break;
        }
    }
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
