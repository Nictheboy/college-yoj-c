#include <stdio.h>
#include <assert.h>

typedef struct _node
{
    struct _node *lchild, *rchild, *parent;
    int value, height;
} node;

node tree[1000000];
int cursor;

int max(int a, int b) { return a > b ? a : b; }

int height_of(node *nd) { return nd ? nd->height : -1; }

void insert(node **p_root, int val)
{
    node *root = *p_root, **insert_to;
    if (val < root->value)
        insert_to = &root->lchild;
    else
        insert_to = &root->rchild;
    if (*insert_to)
        insert(insert_to, val);
    else
    {
        node *new_node = &tree[cursor++];
        new_node->height = 0;
        new_node->parent = root;
        new_node->value = val;
        *insert_to = new_node;
    }
    root->height = max(height_of(root->lchild), height_of(root->rchild)) + 1;
}

void delete(node **p_root, int val)
{
    node *root = *p_root;
    if (root->value == val)
    {
        if (!root->lchild && !root->rchild)
            *p_root = NULL;
        else if (!root->lchild && root->rchild)
            *p_root = root->rchild, root->rchild->parent = root->parent;
        else if (root->lchild && !root->rchild)
            *p_root = root->lchild, root->lchild->parent = root->parent;
        else
        {
            node *r_left = root->rchild;
            while (r_left->lchild)
                r_left = r_left->lchild;
            root->value = r_left->value;
            delete (&root->rchild, root->value);
        }
    }
    else
    {
        if (val < root->value)
            delete (&root->lchild, val);
        else
            delete (&root->rchild, val);
    }
    root->height = max(height_of(root->lchild), height_of(root->rchild)) + 1;
}

void print(node *nd)
{
    printf("%d ", nd->value);
    if (nd->lchild)
        print(nd->lchild);
    if (nd->rchild)
        print(nd->rchild);
}

void check(node *nd)
{
    if (nd->lchild)
    {
        assert(nd->lchild->value < nd->value);
        assert(nd->lchild->parent == nd);
        check(nd->lchild);
    }
    if (nd->rchild)
    {
        assert(nd->rchild->value > nd->value);
        assert(nd->rchild->parent == nd);
        check(nd->rchild);
    }
    assert(nd->height == max(height_of(nd->lchild), height_of(nd->rchild)) + 1);
}

int main()
{
    int n;
    scanf("%d", &n);
    int a, b;
    scanf("%d%d", &a, &b);
    node *root = &tree[cursor++];
    root->value = b;
    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d%d", &a, &b);
        if (a)
            insert(&root, b);
        else
            delete (&root, b);
        check(tree);
    }
    print(tree);
    printf("\n");
    return 0;
}
