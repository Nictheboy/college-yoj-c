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

void update_height(node *root) { root->height = max(height_of(root->lchild), height_of(root->rchild)) + 1; }

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

int count(node *nd)
{
    if (nd)
        return 1 + count(nd->lchild) + count(nd->rchild);
    else
        return 0;
}

void rotate_clockwise(node **p_root)
{
    int cnt_checkpoint = count(*p_root);
    node *root = *p_root;
    assert(root->lchild);
    node *nd_1 = root->lchild, *nd_2 = root;
    node *subtree_1 = root->lchild->lchild;
    node *subtree_2 = root->lchild->rchild;
    *p_root = nd_1, nd_1->parent = nd_2->parent;
    nd_1->lchild = subtree_1;
    if (subtree_1)
        subtree_1->parent = nd_1;
    nd_1->rchild = nd_2, nd_2->parent = nd_1;
    nd_2->lchild = subtree_2;
    if (subtree_2)
        subtree_2->parent = nd_2;
    update_height(nd_2);
    update_height(nd_1);
    check(nd_1);
    assert(cnt_checkpoint == count(*p_root));
}

void rotate_counterclockwise(node **p_root)
{
    int cnt_checkpoint = count(*p_root);
    node *root = *p_root;
    assert(root->rchild);
    node *nd_1 = root->rchild, *nd_2 = root;
    node *subtree_1 = root->rchild->rchild;
    node *subtree_2 = root->rchild->lchild;
    *p_root = nd_1, nd_1->parent = nd_2->parent;
    nd_1->rchild = subtree_1;
    if (subtree_1)
        subtree_1->parent = nd_1;
    nd_1->lchild = nd_2, nd_2->parent = nd_1;
    nd_2->rchild = subtree_2;
    if (subtree_2)
        subtree_2->parent = nd_2;
    update_height(nd_2);
    update_height(nd_1);
    check(nd_1);
    assert(cnt_checkpoint == count(*p_root));
}

void maintain(node **p_root)
{
    node *root = *p_root;
    if (height_of(root->lchild) > 1 + height_of(root->rchild))
    {
        if (height_of(root->lchild->lchild) < height_of(root->lchild->rchild))
            rotate_counterclockwise(&root->lchild);
        rotate_clockwise(p_root);
    }
    if (height_of(root->lchild) + 1 < height_of(root->rchild))
    {
        if (height_of(root->rchild->lchild) > height_of(root->rchild->rchild))
            rotate_clockwise(&root->rchild);
        rotate_counterclockwise(p_root);
    }
}

void insert(node **p_root, int val)
{
    int cnt_checkpoint = count(*p_root);
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
    update_height(root);
    maintain(p_root);
    assert(cnt_checkpoint + 1 == count(*p_root));
}

void delete(node **p_root, int val)
{
    int cnt_checkpoint = count(*p_root);
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
    update_height(root);
    if (*p_root)
        maintain(p_root);
    assert(cnt_checkpoint - 1 == count(*p_root));
}

void print(node *nd)
{
    printf("%d ", nd->value);
    if (nd->lchild)
        print(nd->lchild);
    if (nd->rchild)
        print(nd->rchild);
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
        check(root);
        // fprintf(stderr, "cnt = %d\n", count(root));
    }
    print(root);
    printf("\n");
    return 0;
}
