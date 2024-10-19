#include <stdio.h>

typedef struct
{
    int next;
    int data;
} node;

#define INSERT(DATA, NEXT)            \
    link_array[cursor].data = (DATA); \
    link_array[cursor].next = (NEXT); \
    cursor++;

int main()
{
    node link_array[100];
    int cursor = 0;

    INSERT(0, -1)

    int n;
    scanf("%d", &n);
    int last;
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        link_array[last].next = cursor;
        INSERT(x, -1)
        last = cursor - 1;
    }

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int q, p;
            scanf("%d%d", &q, &p);
            int ptr = 0;
            for (int j = 0; j < p - 1; j++)
                ptr = link_array[ptr].next;
            INSERT(q, link_array[ptr].next)
            link_array[ptr].next = cursor - 1;
        }
        if (op == 0)
        {
            int q;
            scanf("%d", &q);
            for (int ptr = 0; link_array[ptr].next >= 0; ptr = link_array[ptr].next)
                if (link_array[link_array[ptr].next].data == q)
                    link_array[ptr].next = link_array[link_array[ptr].next].next;
        }
    }

    for (int ptr = link_array[0].next; ptr >= 0; ptr = link_array[ptr].next)
        printf("%d ", link_array[ptr].data);
    printf("\n");
    return 0;
}
