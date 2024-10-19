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

node *next(list *l, int data)
{
    for (node *curr = l->next; curr; curr = curr->next)
    {
        if (curr->data == data)
            return curr;
    }
    return NULL;
}

void trim(list *l)
{
    for (node *curr = l->next; curr;)
    {
        node *next_node = curr->next;
        int data = curr->data;
        node *curr_same_data = curr;
        while (1)
        {
            node *next_same_data = next(curr_same_data, data);
            if (next_same_data)
            {
                if (curr_same_data == next_node)
                    next_node = next_node ? next_node->next : NULL;
                delete (curr_same_data);
                curr_same_data = next_same_data;
            }
            else
            {
                break;
            }
        }
        curr = next_node;
    }
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

    trim(l);

    for (node *nd = l->next; nd; nd = nd->next)
        printf("%d ", nd->data);
    printf("\n");

    destroy(l);
    return 0;
}
