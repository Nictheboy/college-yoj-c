#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    struct _node *prev, *next;
    int data;
} node, list;

list *init()
{
    list *l = malloc(sizeof(list));
    l->prev = NULL;
    l->next = NULL;
    return l;
}

node *of_index(list *l, int idx)
{
    node *curr = l;
    for (int i = 0; curr && i < idx; i++)
    {
        curr = curr->next;
    }
    return curr;
}

void append(node *n, int data)
{
    node *new = malloc(sizeof(node));
    new->data = data;
    if (n->next)
    {
        node *next = n->next;
        n->next = new;
        next->prev = new;
        new->prev = next;
        new->next = next;
    }
    else
    {
        n->next = new;
        new->prev = n;
        new->next = NULL;
    }
}

void delete(node *n)
{
    node *prev = n->prev;
    node *next = n->next;
    if (prev)
        prev->next = next;
    if (next)
        next->prev = prev;
    free(n);
}

void destroy(list *l)
{
    for (node *nd = l->next; nd;)
    {
        node *next = nd->next;
        free(nd);
        nd = next;
    }
    free(l);
}

node *of_max(list *l)
{
    int max = 0x80000000;
    node *ret = NULL;
    for (node *nd = l->next; nd; nd = nd->next)
    {
        if (nd->data > max)
        {
            max = nd->data;
            ret = nd;
        }
    }
    return ret;
}

list *select_sort(list *l)
{
    list *sorted = init();
    while (l->next)
    {
        node *max_node = of_max(l);
        append(sorted, max_node->data); // push_front
        delete (max_node);
    }
    return sorted;
}

int length(list *l)
{
    int count = 0;
    for (node *nd = l->next; nd; nd = nd->next)
        count++;
    return count;
}

int count_reverse_pair(list *begin, int length)
{
    // if (length <= 1)
    //     return 0;
    // int front_cnt = length / 2;
    // int back_cnt = length - front_cnt;
    // node *
    int count = 0;
    for (int i = 0; i < length - 1; i++)
    {
        node *next = begin->next;
        for (int j = i + 1; j < length; j++)
        {
            if (begin->data > next->data)
                count++;
            next = next->next;
        }
        begin = begin->next;
    }
    return count;
}

int main()
{
    int n;
    scanf("%d", &n);
    list *l = init();

    node *curr = l;
    for (int i = 0; i < n; i++)
    {
        int data;
        scanf("%d", &data);
        append(curr, data);
        curr = curr->next;
    }

    int result = count_reverse_pair(l->next, n);
    printf("%d", result);

    destroy(l);
    return 0;
}
