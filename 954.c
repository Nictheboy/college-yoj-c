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

list *select_sort(list *l)
{
    list *sorted = init();
    for (node *nd = l->next; nd; nd = nd->next)
    {
        int data = nd->data;
        if (!sorted->next)
            append(sorted, data);
        else
        {
            int is_first = 1;
            for (node *nd2 = sorted; nd2; nd2 = nd2->next)
            {
                int gte = is_first || nd2->data <= data;
                int lte = !nd2->next || data <= nd2->next->data;
                if (gte && lte)
                {
                    append(nd2, data);
                    break;
                }
                is_first = 0;
            }
        }
    }
    return sorted;
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

    list *sorted = select_sort(l);

    for (node *nd = sorted->next; nd; nd = nd->next)
        printf("%d ", nd->data);
    printf("\n");

    destroy(sorted);
    destroy(l);
    return 0;
}
