#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define N_MAX 50

typedef long long ll;

typedef struct
{
    ll distance;
    int previous;
} Node;

typedef struct
{
    int n;
    ll *map;     // n*n
    Node *nodes; // n
} Map;

void Map_init(Map *self, const int n)
{
    self->map = (ll *)calloc(n * n, sizeof(ll));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lld", &self->map[i * n + j]);
    self->nodes = (Node *)calloc(n, sizeof(Node));
    for (int i = 0; i < n; i++)
    {
        self->nodes[i].previous = -1;
        self->nodes[i].distance = -1;
    }
}

bool Map_is_better(Map *self, const int index, const int prev1, const int prev2)
{
    if (prev1 == prev2)
        return false;
    assert(prev1 >= 0);
    if (prev2 == -1)
        return true;
    if (prev2 == -2)
        return false;
    const int n = self->n;
    assert(self->map[prev1 * n + index] >= 0);
    assert(self->nodes[prev1].distance >= 0);
    if (self->map[prev2 * n + index] == -1)
        return true;
    if (self->nodes[prev2].distance == -1)
        assert(false);
    if (self->nodes[prev1].distance + self->map[prev1 * n + index] < self->nodes[prev2].distance + self->map[prev2 * n + index])
        return true;
    if (self->nodes[prev1].distance + self->map[prev1 * n + index] > self->nodes[prev2].distance + self->map[prev2 * n + index])
        return false;

    int stack1[N_MAX], stack2[N_MAX];
    int n_stack1 = 0, n_stack2 = 0;
    for (int curr = prev1; curr >= 0; curr = self->nodes[curr].previous)
    {
        stack1[n_stack1++] = curr;
    }
    for (int curr = prev2; curr >= 0; curr = self->nodes[curr].previous)
    {
        stack2[n_stack1++] = curr;
    }
    int i, j;
    for (i = n_stack1 - 1, j = n_stack2 - 1; i >= 0 && j >= 0; i--, j--)
    {
        if (stack1[i] < stack2[i])
            return true;
        if (stack1[i] > stack2[i])
            return false;
    }
    if (i < 0 && j >= 0)
        return true;
    if (i >= 0 && j < 0)
        return false;
    assert(false);
}

bool Map_calc(Map *self, const int index)
{
    const int n = self->n;
    bool change_flag = false;
    for (int i = 0; i < n; i++)
    {
        if (self->map[i * n + index] != -1 && self->nodes[i].distance >= 0 && Map_is_better(self, index, i, self->nodes[index].previous))
        {
            change_flag = true;
            self->nodes[index].previous = i;
            self->nodes[index].distance = self->nodes[i].distance + self->map[i * n + index];
        }
    }
    return change_flag;
}

void Map_spread(Map *self, const int index)
{
    assert(self->nodes[index].distance >= 0);
    const int n = self->n;
    int change_flags[N_MAX] = {0};
    for (int j = 0; j < n; j++)
    {
        if (self->map[index * n + j] != -1)
            change_flags[j] = Map_calc(self, j);
    }
    for (int j = 0; j < n; j++)
        if (change_flags[j])
            Map_spread(self, j);
}

int main()
{
    Map M;
    scanf("%d", &M.n);
    int start, dest;
    scanf("%d%d", &start, &dest);
    Map_init(&M, M.n);

    M.nodes[start].distance = 0;
    M.nodes[start].previous = -2;
    Map_spread(&M, start);

    if (M.nodes[dest].previous == -1)
    {
        printf("-1");
        return 0;
    }
    int stack[N_MAX];
    int n_stack = 0;
    for (int curr = dest; curr >= 0; curr = M.nodes[curr].previous)
        stack[n_stack++] = curr;
    printf("%d", start);
    for (int i = n_stack - 2; i >= 0; i--)
        printf("->%d", stack[i]);

    return 0;
}
