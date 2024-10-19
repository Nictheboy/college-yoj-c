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

node *of_first(list *l, int data)
{
    for (node *nd = l->next; nd; nd = nd->next)
        if (nd->data == data)
            return nd;
    return NULL;
}

void trim_ordered(list *l)
{
    for (node *nd = l->next; nd; nd = nd->next)
        while (1)
            if (nd->next && nd->next->data == nd->data)
                delete (nd->next);
            else
                break;
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

    trim_ordered(l);
    int m;
    scanf("%d", &m);
    node *to_delete = of_first(l, m);
    delete (to_delete);

    for (node *nd = l->next; nd; nd = nd->next)
        printf("%d ", nd->data);
    printf("\n");

    destroy(l);
    return 0;
}
