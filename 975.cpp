#include <stdio.h>
#include <algorithm>

struct node;
typedef node *pnode;
struct node
{
    int frequency;
    pnode left_child;
    pnode right_child;

    long long total_length(int bits_cnt) const
    {
        if (!left_child && !right_child)
            return bits_cnt * frequency;
        long long total = 0;
        if (left_child)
            total += left_child->total_length(bits_cnt + 1);
        if (right_child)
            total += right_child->total_length(bits_cnt + 1);
        return total;
    }
};

int n_leafs, n_internal, n_heap;
node leafs[1000005];
node internals[1000005];

struct heap_element
{
    pnode ptr;
    int frequency;

    heap_element() {}
    heap_element(node *ptr) : ptr(ptr), frequency(ptr->frequency) {}

    inline bool operator<(const heap_element &another)
    {
        return frequency > another.frequency;
    }
};
heap_element heap[1000005];

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int frequency;
        scanf("%d", &frequency);
        if (frequency > 0)
        {
            leafs[n_leafs++].frequency = frequency;
            heap[n_heap++] = &leafs[n_leafs - 1];
        }
    }
    std::make_heap(heap, heap + n_heap);
    while (n_heap > 1)
    {
        // pop
        auto min1 = heap[0].ptr;
        std::swap(heap[0], heap[n_heap - 1]);
        --n_heap;
        std::pop_heap(heap, heap + n_heap);

        // pop
        auto min2 = heap[0].ptr;
        std::swap(heap[0], heap[n_heap - 1]);
        --n_heap;
        std::pop_heap(heap, heap + n_heap);

        // new node
        internals[n_internal].frequency = min1->frequency + min2->frequency;
        internals[n_internal].left_child = min1;
        internals[n_internal].right_child = min2;
        ++n_internal;

        // push
        heap[n_heap++] = &internals[n_internal - 1];
        std::push_heap(heap, heap + n_heap);
    }
    printf("%lld\n", heap[0].ptr->total_length(0));
    return 0;
}
