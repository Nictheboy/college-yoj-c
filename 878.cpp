#include <stdio.h>
#include <assert.h>

#include <algorithm>

#undef assert
#define assert(A)

#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define MIN(A, B) (((A) < (B)) ? (A) : (B))

#define MAX_BLOCK_RANK 15

typedef long long ll;

struct Rect
{
    int xSmall, xLarge, ySmall, yLarge;
};

struct BRect
{
    const int xIndex, yIndex;
    const int rank; // 0 <= rank < 32

    const ll RecSize;
    const int base;
    const int XSmall;
    const int XLarge;
    const int YSmall;
    const int YLarge;

    BRect(int xIndex, int yIndex, int rank)
        : xIndex(xIndex), yIndex(yIndex), rank(rank), RecSize(1 << 2 * rank), base(1 << rank), XSmall(xIndex * base), XLarge((xIndex + 1) * base - 1), YSmall(yIndex * base), YLarge((yIndex + 1) * base - 1) {}

    bool Is(const BRect &node) const
    {
        return rank == node.rank && xIndex == node.xIndex && yIndex == node.yIndex;
    }

    bool WithIn(const BRect &node) const
    {
        return XSmall >= node.XSmall && XLarge <= node.XLarge && YSmall >= node.YSmall && YLarge <= node.YLarge && !Is(node);
    }

    static BRect Wrap(Rect rect)
    {
        for (int i = 0; i < 32; i++)
        {
            if (rect.xSmall >> i == rect.xLarge >> i && rect.ySmall >> i == rect.yLarge >> i)
            {
                return BRect(rect.xSmall >> (i + 1), rect.ySmall >> (i + 1), i + 1);
            }
        }
        assert(false);
    }

    BRect And(const BRect &another) const
    {
        Rect rect;
        rect.xSmall = MIN(XSmall, another.XSmall);
        rect.xLarge = MAX(XLarge, another.XLarge);
        rect.ySmall = MIN(YSmall, another.YSmall);
        rect.yLarge = MAX(YLarge, another.YLarge);
        return Wrap(rect);
    }
};

struct Leaf : public BRect
{
    Leaf(int xIndex, int yIndex, int rank)
        : BRect(xIndex, yIndex, rank) {}
};

class Node : public BRect
{
private:
    ll size;
    bool isLeaf[2][2];
    Node *child[2][2];
    Node *parent;
    int parent_index[2];
    /*
    [0][1] | [1][1]
    ---------------
    [0][0] | [1][0]
    */

    void AddSize(ll delta)
    {
        size += delta;
        if (parent)
            parent->AddSize(delta);
        if (size == RecSize)
        {
            // parent->child[parent_index[0]][parent_index[1]] = nullptr;
            parent->isLeaf[parent_index[0]][parent_index[1]] = true;
        }
    }

    void Link(Node &content)
    {
        assert(content.WithIn(*this));
        if (content.rank == rank - 1)
        {
            int xPos = content.XSmall != XSmall;
            int yPos = content.YSmall != YSmall;
            child[xPos][yPos] = &content;
            content.parent = this;
            content.parent_index[0] = xPos;
            content.parent_index[1] = yPos;
            AddSize(content.Size());
        }
        else
        {
            // node.rank <= rank - 2
            int xPos = content.XSmall >= XSmall + (1 << (rank - 1));
            int yPos = content.YSmall >= YSmall + (1 << (rank - 1));
            child[xPos][yPos] = new Node(xIndex * 2 + xPos, yIndex * 2 + yPos, rank - 1);
            child[xPos][yPos]->parent = this;
            child[xPos][yPos]->parent_index[0] = xPos;
            child[xPos][yPos]->parent_index[1] = yPos;
            child[xPos][yPos]->Link(content);
        }
    }

public:
    Node(int xIndex, int yIndex, int rank, Node *content = nullptr)
        : BRect(xIndex, yIndex, rank)
    {
        size = 0;
        isLeaf[0][0] = false;
        isLeaf[0][1] = false;
        isLeaf[1][0] = false;
        isLeaf[1][1] = false;
        child[0][0] = nullptr;
        child[0][1] = nullptr;
        child[1][0] = nullptr;
        child[1][1] = nullptr;
        if (content)
            Link(*content);
    }

    ll Size() const
    {
        return size;
    }

    void Insert(Leaf &leaf)
    {
        assert(leaf.WithIn(*this));
        if (leaf.rank == rank - 1)
        {
            int xPos = leaf.XSmall != XSmall;
            int yPos = leaf.YSmall != YSmall;
            if (isLeaf[xPos][yPos])
                return;
            else
            {
                isLeaf[xPos][yPos] = true;
                if (child[xPos][yPos])
                {
                    AddSize(-child[xPos][yPos]->size);
                }
                AddSize(leaf.RecSize);
            }
        }
        else
        {
            // node.rank <= rank - 2
            int xPos = leaf.XSmall >= XSmall + (1 << (rank - 1));
            int yPos = leaf.YSmall >= YSmall + (1 << (rank - 1));
            if (isLeaf[xPos][yPos])
                return;
            else if (child[xPos][yPos])
                child[xPos][yPos]->Insert(leaf);
            else
            {
                child[xPos][yPos] = new Node(xIndex * 2 + xPos, yIndex * 2 + yPos, rank - 1);
                child[xPos][yPos]->parent = this;
                child[xPos][yPos]->parent_index[0] = xPos;
                child[xPos][yPos]->parent_index[1] = yPos;
                child[xPos][yPos]->Insert(leaf);
            }
        }
    }
};

void Insert(Node **root, Leaf &leaf)
{
    if (!leaf.WithIn(**root))
    {
        BRect wrap = (*root)->And(leaf);
        auto newRoot = new Node(wrap.xIndex, wrap.yIndex, wrap.rank, *root);
        *root = newRoot;
    }
    (*root)->Insert(leaf);
    return;
}

void Insert(Node **root, int x1, int y1, int x2, int y2)
{
    assert(x2 >= x1 && y1 >= y2);
    if (x2 == x1 || y1 == y2)
        return;
    if (x2 - x1 == y1 - y2)
    {
        for (int i = 0; i < MAX_BLOCK_RANK; i++)
        {
            const int base = 1 << i;
            if (x2 - x1 == base)
            {
                if (x2 / base == x1 / base)
                {
                    Leaf leaf(x1 >> i, y2 >> i, i);
                    Insert(root, leaf);
                }
                else
                    break;
            }
        }
    }
    for (int i = MAX_BLOCK_RANK; i >= 0; i--)
    {
        const int base = (1 << i);
        if (x2 / base > (x1 - 1) / base + 1 && y1 / base > (y2 - 1) / base + 1)
        {
            for (int x = (x1 - 1) / base + 1; x < x2 / base; x++)
            {
                for (int y = (y2 - 1) / base + 1; y < y1 / base; y++)
                {
                    Leaf leaf(x, y, i);
                    Insert(root, leaf);
                }
            }
            const int x1_2 = ((x1 - 1) / base + 1) * base;
            const int x2_2 = x2 / base * base;
            const int y1_2 = y1 / base * base;
            const int y2_2 = ((y2 - 1) / base + 1) * base;
            /*
            (x1, y1  )  (x1_2, y1  )    (x2_2, y1  )    (x2, y1  )

            (x1, y1_2)  (x1_2, y1_2)    (x2_2, y1_2)    (x2, y1_2)

            (x1, y2_2)  (x1_2, y2_2)    (x2_2, y2_2)    (x2, y2_2)

            (x1, y2  )  (x1_2, y2  )    (x2_2, y2  )    (x2, y2  )
            */
            Insert(root, x1, y1, x2_2, y1_2);
            Insert(root, x2_2, y1, x2, y2_2);
            Insert(root, x1_2, y2_2, x2, y2);
            Insert(root, x1, y1_2, x1_2, y2);
            return;
        }
    }
    assert(false);
}

int main()
{
    int n;
    scanf("%d", &n);
    Node *root = nullptr;
    for (int i = 0; i < n; i++)
    {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (!root)
        {
            Rect rect;
            rect.xSmall = x1;
            rect.xLarge = x2;
            rect.ySmall = y2;
            rect.yLarge = y1;
            BRect bRect = BRect::Wrap(rect);
            root = new Node(bRect.xIndex, bRect.yIndex, bRect.rank);
        }
        Insert(&root, x1, y1, x2, y2);
    }
    printf("%lld\n", root->Size());
    return 0;
}
