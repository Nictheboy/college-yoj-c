#include <vector>
#include <assert.h>
#include <algorithm>
#include <stdio.h>

constexpr int lchild(int idx) { return 2 * idx + 1; }
constexpr int rchild(int idx) { return 2 * idx + 2; }
constexpr int parent(int idx) { return (idx - 1) / 2; }

template <typename T>
using min_heap = std::vector<T>;

template <typename T>
void _maintain_up(min_heap<T> &x, int idx)
{
    auto size = x.size();
    assert(0 <= idx && idx < size);
    auto idx_lchild = lchild(idx);
    auto idx_rchild = rchild(idx);
    auto idx_parent = parent(idx);
    bool has_made_change = false;
    if (0 <= idx_lchild && idx_lchild < size && x[idx_lchild] < x[idx])
        std::swap(x[idx_lchild], x[idx]), has_made_change = true;
    if (0 <= idx_rchild && idx_rchild < size && x[idx_rchild] < x[idx])
        std::swap(x[idx_rchild], x[idx]), has_made_change = true;
    if (has_made_change && idx_parent >= 0)
        _maintain_up(x, idx_parent);
}

template <typename T>
void maintain_up(min_heap<T> &x, int idx)
{
    if (idx > 0)
        _maintain_up(x, parent(idx));
}

template <typename T>
void insert(min_heap<T> &x, T val)
{
    x.push_back(val);
    auto size = x.size();
    maintain_up(x, size - 1);
}

template <typename T>
void maintain_down(min_heap<T> &x, int idx)
{
    auto size = x.size();
    assert(0 <= idx && idx < size);
    auto idx_lchild = lchild(idx);
    auto idx_rchild = rchild(idx);
    if (0 <= idx_lchild && idx_lchild < size && x[idx_lchild] < x[idx])
    {
        std::swap(x[idx_lchild], x[idx]);
        maintain_down(x, idx_lchild);
    }
    if (0 <= idx_rchild && idx_rchild < size && x[idx_rchild] < x[idx])
    {
        std::swap(x[idx_rchild], x[idx]);
        maintain_down(x, idx_rchild);
    }
}

template <typename T>
T pop_min(min_heap<T> &x)
{
    auto size = x.size();
    auto val = x[0];
    if (size == 0)
        return -1;
    if (size == 1)
    {
        x.pop_back();
        return val;
    }
    else
    {
        std::swap(x[0], x[size - 1]);
        x.pop_back();
        maintain_down(x, 0);
        return val;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    auto heap = min_heap<int>();
    for (int i = 0; i < n; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 0)
        {
            int val;
            scanf("%d", &val);
            insert(heap, val);
        }
        else if (op == 1)
        {
            int val = pop_min(heap);
            printf("%d\n", val);
        }
        else if (op == 2)
            printf("%ld\n", heap.size());
        else
            assert(false);
    }
    return 0;
}
