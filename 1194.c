#include <stdio.h>
#include <stdbool.h>

int n, buffer[1001], begin, end;

int inc(int idx) { return ++idx < n ? idx : 0; }
int dec(int idx) { return --idx >= 0 ? idx : n - 1; }
bool empty() { return begin == end; }
bool full() { return begin == inc(end); }

int main()
{
    int k;
    scanf("%d%d", &n, &k);
    ++n;
    for (int i = 0; i < k; i++)
    {
        int op, x;
        scanf("%d", &op);
        switch (op)
        {
        case 0:
            if (empty())
                printf("-1\n");
            else
                printf("%d\n", buffer[begin]);
            break;

        case 1:
            if (empty())
                printf("-1\n");
            else
                printf("%d\n", buffer[dec(end)]);
            break;

        case 2:
            scanf("%d", &x);
            if (full())
                printf("0\n");
            else
            {
                buffer[end] = x;
                end = inc(end);
                printf("1\n");
            }
            break;

        case 3:
            if (empty())
                printf("0\n");
            else
            {
                begin = inc(begin);
                printf("1\n");
            }
            break;

        case 4:
            if (empty())
                printf("1\n");
            else
                printf("0\n");
            break;

        case 5:
            if (full())
                printf("1\n");
            else
                printf("0\n");
            break;
        }
    }
    return 0;
}
