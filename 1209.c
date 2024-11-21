#include <stdio.h>
#include <string.h>

int n, tree[100], lchild[100], rchild[100];

void insert(int idx, int val)
{
    if (val <= tree[idx])
    {
        if (lchild[idx] >= 0)
            insert(lchild[idx], val);
        else
        {
            lchild[idx] = n;
            lchild[n] = -1;
            rchild[n] = -1;
            tree[n++] = val;
        }
    }
    else
    {
        if (rchild[idx] >= 0)
            insert(rchild[idx], val);
        else
        {
            rchild[idx] = n;
            lchild[n] = -1;
            rchild[n] = -1;
            tree[n++] = val;
        }
    }
}

int n_stack, length_stack[100], direction_stack[100]; // 0: left, 1: right

void print_prefix()
{
    for (int i = 0; i < n_stack; i++)
    {
        for (int j = 0; j < length_stack[i]; j++)
            putchar('.');
        if (i + 1 < n_stack && direction_stack[i] == direction_stack[i + 1])
            putchar('.');
        else
            putchar('|');
    }
    if (n_stack > 0)
        putchar('-');
}

void print(int idx)
{
    char val_str[8];
    sprintf(val_str, "%d", tree[idx]);
    if (rchild[idx] >= 0)
    {
        length_stack[n_stack] = (n_stack > 0) + strlen(val_str) + 1;
        direction_stack[n_stack++] = 1;
        print(rchild[idx]);
        --n_stack;
    }
    print_prefix();
    printf("%s", val_str);
    if (lchild[idx] >= 0 || rchild[idx] >= 0)
        printf("-|");
    putchar('\n');
    if (lchild[idx] >= 0)
    {
        length_stack[n_stack] = (n_stack > 0) + strlen(val_str) + 1;
        direction_stack[n_stack++] = 0;
        print(lchild[idx]);
        --n_stack;
    }
}

int main()
{
    int val;
    scanf("%d", &val);
    lchild[n] = -1;
    rchild[n] = -1;
    tree[n++] = val;
    while (scanf("%d", &val) != EOF)
        insert(0, val);
    print(0);
    return 0;
}
