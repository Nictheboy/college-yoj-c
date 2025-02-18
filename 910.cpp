#include <stdio.h>
#include <assert.h>
#include <numeric>
#include <algorithm>

#define int long long

int n, a[100000], tree[262144]; // 262144 == 2 ** 18

int tree_layer_end(int layer) { return (1 << layer) - 1; }
int tree_layer_begin(int layer) { return tree_layer_end(layer) / 2; }
int lchild(int idx) { return 2 * idx + 1; }
int rchild(int idx) { return 2 * idx + 2; }

void build_tree()
{
    int layer = 18, layer_begin = tree_layer_begin(layer), layer_end = tree_layer_end(layer);
    int i;
    for (i = 0; i < n; i++)
        tree[layer_begin + i] = a[i];
    for (; layer_begin + i < layer_end; i++)
        tree[layer_begin + i] = 0;
    for (layer--; layer > 0; layer--)
    {
        layer_begin = tree_layer_begin(layer), layer_end = tree_layer_end(layer);
        for (int idx = layer_begin; idx < layer_end; idx++)
            tree[idx] = std::gcd(tree[lchild(idx)], tree[rchild(idx)]);
    }
}

int fast_gcd(int begin, int end)
{
    assert(begin <= end);
    if (begin == end)
        return 0;
    for (int layer = 1; layer <= 18; layer++)
    {
        int left = (begin - 1) >> (18 - layer), right = end >> (18 - layer);
        if (right - left >= 2)
        {
            int first = left + 1;
            int pivot_left = first << (18 - layer), pivot_right = right << (18 - layer);
            int gcd_1 = fast_gcd(begin, pivot_left);
            int gcd_2 = 0;
            int layer_begin = tree_layer_begin(layer);
            for (int blk = first; blk < right; blk++)
                gcd_2 = std::gcd(gcd_2, tree[layer_begin + blk]);
            int gcd_3 = fast_gcd(pivot_right, end);
            int gcd = std::gcd(gcd_1, std::gcd(gcd_2, gcd_3));
            return gcd;
        }
    }
    assert(0);
}

int update_y_max_from_begin(int y_max, int begin)
{
    int end = begin + 1;
    int gcd = a[begin];
    int y = (end - begin) * gcd;
    y_max = std::max(y_max, y);
    while (end < n)
    {
        if (gcd == 1)
        {
            int y = n - begin;
            y_max = std::max(y_max, y);
            break;
        }
        int new_gcd = std::gcd(gcd, a[end]);
        int new_end = std::max(end + 1, begin + y_max / new_gcd);
        if (new_end > n)
            break;
        gcd = std::gcd(gcd, fast_gcd(end, new_end));
        end = new_end;
        y = (end - begin) * gcd;
        y_max = std::max(y_max, y);
    }
    return y_max;
}

signed main()
{
    scanf("%lld", &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    build_tree();
    int y_max = 0;
    for (int i = 0; i < n; i++)
        y_max = update_y_max_from_begin(y_max, i);
    printf("%lld\n", y_max);
}
