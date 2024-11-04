// 设 R 是一个二元关系，R(a, b) 表示 a 可以看到 b，如 R(1, 2) 表示第一头牛可以看到第二头牛
// 则不难验证，R 是一个偏序关系。

// 请读者在脑中想象一张哈塞图。
// 比右边的牛还要矮的牛看不到任何其他的牛，我们把这些牛放在图的最底下。

// 牛 a 上面紧邻的节点 b 是所有这样的节点： a 和 b 之间的所有牛都低于 a 和 b，且 a 高于 b
// 这是因为：假如之间有高于或等于 a 的牛，则 a 看不到 b
// 假如之间有高于 b 但低于 a 的牛 m，则 a 可以看到 m，m 也可以看到 b，ab不紧邻

// 由上面的结论知，这张哈塞图中每个节点至多只有一个高于它的紧邻节点，即图是一颗树或一片森林，
// 每只牛可以看到的牛的个数，就是他的子树的节点数。
// 如果一个节点有 k 个子结点，则它的子树的节点数为这 k 个节点的子树的节点数的和加上 k，
// 也就是每个子结点的子树的节点数加一的和。

// 牛从左到右的顺序实际上是这棵树的一个“先父节点-再子结点”遍历，
// 而且从每个牛往右递减地走（可以跳过一些牛，但要保证跳过的牛比左右都矮）的过程构成的牛的序列既是遍历栈，也是树枝本身。
// 以上便是我们的思路了。

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

int n;
int h[80000];
int parent[80000];
long long c[80000];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &h[i]);

    // fill parent[]
    parent[0] = -1;
    int depth = 0;
    for (int i = 1; i < n; i++)
    {
        if (h[i - 1] > h[i])
        {
            parent[i] = i - 1;
            ++depth;
        }
        else
        {
            bool in_tree = false;
            for (int j = parent[i - 1]; j >= 0; j = parent[j])
            {
                --depth;
                if (h[j] > h[i])
                {
                    parent[i] = j;
                    ++depth;
                    in_tree = true;
                    break;
                }
            }
            if (!in_tree)
            {
                // new root
                parent[i] = -1;
                assert(depth == 0);
            }
        }
    }

    // fill c
    for (int i = 0; i < n; i++)
        for (int j = parent[i]; j >= 0; j = parent[j])
            ++c[j];

    // calculate sum
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += c[i];

    printf("%lld\n", sum);
}
