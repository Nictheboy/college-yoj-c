#include <stdio.h>
#include <assert.h>
#include <limits>
#include <algorithm>

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#define int long long
int square(int x) { return x * x; }
int dist(int x0, int y0, int x1, int y1)
{
    int dx = x0 - x1;
    int dy = y0 - y1;
    return dx * dx + dy * dy;
}

class quad;
quad *memory_alloc();

class quad
{
private:
    int r, x, y;       // quad(r, x, y) := [x*2^r, (x+1)*2^r)[y*2^r, (y+1)*2^r)
    quad *child[2][2]; // child[i][j] := quad(r-1, 2x+i, 2y+j)
    int n;

    int x_pos(int idx) const
    {
        // assert(r > 0);
        // assert(0 <= idx && idx < 3);
        return (2 * x + idx) << (r - 1);
    }

    int y_pos(int idx) const
    {
        // assert(r > 0);
        // assert(0 <= idx && idx < 3);
        return (2 * y + idx) << (r - 1);
    }

public:
    quad() {}
    quad(int r, int x, int y) : r(r), x(x), y(y), n(0)
    {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                child[i][j] = nullptr;
    }

    void insert(int x0, int y0)
    {
        n += 1;
        if (unlikely(r == 0))
            // assert(x0 == x && y0 == y);
            ;
        else
        {
            // assert(x_pos(0) <= x0 && x0 < x_pos(2) && y_pos(0) <= y0 && y0 < y_pos(2));
            int i = x0 >= x_pos(1), j = y0 >= y_pos(1);
            if (!child[i][j])
            {
                child[i][j] = memory_alloc();
                *child[i][j] = quad(r - 1, 2 * x + i, 2 * y + j);
            }
            child[i][j]->insert(x0, y0);
        }
    }

    void min_dist(int x0, int y0, int &min_dist) const
    {
        if (likely(r == 0))
            min_dist = std::min(min_dist, dist(x, y, x0, y0));
        else
        {
            int lower_bound[2][2], dx2[2], dy2[2];
            for (int i = 0; i < 2; i++)
                dx2[i] = square(std::max({0ll, x_pos(i) - x0, x0 - (x_pos(i + 1) - 1)}));
            for (int i = 0; i < 2; i++)
                dy2[i] = square(std::max({0ll, y_pos(i) - y0, y0 - (y_pos(i + 1) - 1)}));
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    lower_bound[i][j] = dx2[i] + dy2[j];
            int i0 = x0 >= x_pos(1), j0 = y0 >= y_pos(1);
            if (child[i0][j0])
                if (lower_bound[i0][j0] < min_dist)
                    child[i0][j0]->min_dist(x0, y0, min_dist);
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    if (!(i == i0 && j == j0) && child[i][j])
                        if (lower_bound[i][j] < min_dist)
                            child[i][j]->min_dist(x0, y0, min_dist);
        }
    }
};

quad memory[256 * 1024 * 1024 / sizeof(quad)], *next = memory;
quad *memory_alloc() { return next++; }

signed main()
{
    int n;
    quad qtree(31, 0, 0);
    scanf("%lld", &n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        scanf("%lld%lld", &x, &y);
        qtree.insert(x, y);
    }
    int q;
    scanf("%lld", &q);
    for (int i = 0; i < q; i++)
    {
        int x0, y0;
        scanf("%lld%lld", &x0, &y0);
        int min_dist = std::numeric_limits<int>::max();
        qtree.min_dist(x0, y0, min_dist);
        printf("%lld\n", min_dist);
    }
    return 0;
}
