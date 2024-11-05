#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <memory.h>

typedef struct
{
    int group;  // 0 if not in any group
    int prev;   // previous element in this group, -1 if is first element, meaningless if group == 0
    int offset; // 0, 1 or 2. 0 eats 1, 1 eats 2, 2 eats 0
} knowledge;

int n;
knowledge species[50000];
int n_groups = 1;
int tails[50000]; // last element of each group

// x, y in {0, 1, ..., n - 1}
// true if "offset[y] - offset[x] = delta (mod 3)" is consistant with current knowledge
bool judge_and_learn(int x, int y, int delta)
{
    assert(x >= 0 && x < n);
    assert(y >= 0 && y < n);
    assert(delta >= 0 && delta < 3);
    if (x == y)
        return delta == 0;
    if (species[x].group == 0 && species[y].group == 0) // no knowledge about both x and y
    {
        species[x].group = n_groups;
        species[y].group = n_groups;
        species[x].prev = -1;
        species[y].prev = x;
        tails[n_groups++] = y;
        species[y].offset = (species[x].offset + delta) % 3;
        return true;
    }
    if (species[x].group == 0) // no knowledge about x, but have knowledge about y
    {
        int group = species[y].group;
        species[x].group = group;
        species[x].prev = tails[group];
        tails[group] = x;
        species[x].offset = (species[y].offset + 3 - delta) % 3;
        return true;
    }
    if (species[y].group == 0) // no knowledge about y, but have knowledge about x
    {
        int group = species[x].group;
        species[y].group = group;
        species[y].prev = tails[group];
        tails[group] = y;
        species[y].offset = (species[x].offset + delta) % 3;
        return true;
    }
    if (species[x].group == species[y].group) // have knowledge about x and y's relationship
    {
        int real_delta = species[y].offset - species[x].offset;
        return (real_delta - delta + 6) % 3 == 0;
    }
    // have knowledge about x and y, but do not know their relationship.
    int x_group = species[x].group;
    int y_group = species[y].group;
    int group_delta = (3 - species[y].offset + species[x].offset + delta) % 3;
    int current;
    for (current = tails[y_group]; species[current].prev != -1; current = species[current].prev)
    {
        species[current].group = x_group;
        species[current].offset = (species[current].offset + group_delta) % 3;
    }
    species[current].group = x_group;
    species[current].offset = (species[current].offset + group_delta) % 3;
    species[current].prev = tails[x_group];
    tails[x_group] = tails[y_group];
    return true;
}

int main()
{
    int k, cnt = 0;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; i++)
    {
        int d;
        long long x, y;
        scanf("%d%lld%lld", &d, &x, &y);
        if (x > n || y > n || (d == 2 && x == y))
            continue;
        bool ret = judge_and_learn((int)x - 1, (int)y - 1, d == 1 ? 0 : 1);
        assert(ret == 0 || ret == 1);
        cnt += ret;
    }
    printf("%d\n", k - cnt);
    return 0;
}
