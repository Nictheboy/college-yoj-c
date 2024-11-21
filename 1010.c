#include <stdio.h>
#include <stdbool.h>

int n, preorder[1000], inorder[1000];
int preorder_idx[1000]; // satisfy: inorder[preorder_idx[idx]] == preorder[k]
int lchild[1000], rchild[1000];
int n_stack, stack[1000];

void build_preorder_idx()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (preorder[i] == inorder[j])
            {
                preorder_idx[i] = j;
                break;
            }
}

void consider(int idx)
{
    if (idx < stack[n_stack - 1])
        lchild[stack[n_stack - 1]] = idx;
    else
        while (1)
        {
            bool satisfied = true;
            for (int i = 0; i < n_stack - 1; i++)
                if (stack[i] < stack[i + 1] != stack[i] < idx)
                {
                    satisfied = false;
                    break;
                }
            if (satisfied)
            {
                rchild[stack[n_stack - 1]] = idx;
                break;
            }
            else
                --n_stack;
        }
    stack[n_stack++] = idx;
    lchild[idx] = -1;
    rchild[idx] = -1;
}

void postorder(int idx)
{
    if (lchild[idx] >= 0)
        postorder(lchild[idx]);
    if (rchild[idx] >= 0)
        postorder(rchild[idx]);
    printf("%d ", inorder[idx]);
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &preorder[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &inorder[i]);
    build_preorder_idx();
    stack[n_stack++] = preorder_idx[0];
    lchild[preorder_idx[0]] = -1;
    rchild[preorder_idx[0]] = -1;
    for (int i = 1; i < n; i++)
        consider(preorder_idx[i]);
    postorder(stack[0]);
    printf("\n");
    return 0;
}
