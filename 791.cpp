#include <stdio.h>
#include <assert.h>
#include <limits>
#include <algorithm>

#define unlikely(x) __builtin_expect(x, 0)
typedef long long int int64;
int64 dist(int x0, int y0, int x1, int y1)
{
    int64 dx = x0 - x1;
    int64 dy = y0 - y1;
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

    int x_min() const { return x; }
    int x_max() const { return x + (1 << r) - 1; }
    int y_min() const { return y; }
    int y_max() const { return y + (1 << r) - 1; }

    unsigned int x_pos(int idx) const
    {
        assert(r > 0);
        assert(0 <= idx && idx < 3);
        return (2 * x + idx) << (r - 1);
    }

    unsigned int y_pos(int idx) const
    {
        assert(r > 0);
        assert(0 <= idx && idx < 3);
        return (2 * y + idx) << (r - 1);
    }

    // struct square3x3
    // {
    //     const quad *q[3][3];

    //     square3x3()
    //     {
    //         for (int i = 0; i < 3; i++)
    //             for (int j = 0; j < 3; j++)
    //                 q[i][j] = nullptr;
    //     }

    //     square3x3 narrow(int i, int j)
    //     {
    //         assert(0 <= i && i < 2 && 0 <= j && j < 2);
    //         square3x3 ret;
    //         for (int ii = 0; ii < 3; ii++)
    //             for (int jj = 0; jj < 3; jj++)
    //                 ret.q[ii][jj] = q[(i + ii + 1) / 2][(j + jj + 1) / 2]->child[(i + ii) % 2][(j + jj) % 2];
    //         return ret;
    //     }

    //     int64 mindist(int x0, int y0) const
    //     {
    //         //
    //     }
    // };

    int64 lower_bound(int x0, int y0) const
    {
        if (x_min() <= x0 && x0 <= x_max() && y_min() <= y0 && y0 <= y_max())
            return 0;
        int64 d1 = dist(x_min(), y_min(), x0, y0);
        int64 d2 = dist(x_max(), y_min(), x0, y0);
        int64 d3 = dist(x_min(), y_max(), x0, y0);
        int64 d4 = dist(x_max(), y_max(), x0, y0);
        return std::min({d1, d2, d3, d4});
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
            assert(x0 == x && y0 == y);
        else
        {
            assert(x_pos(0) <= x0 && x0 < x_pos(2) && y_pos(0) <= y0 && y0 < y_pos(2));
            int i = x0 >= x_pos(1), j = y0 >= y_pos(1);
            if (!child[i][j])
            {
                child[i][j] = memory_alloc();
                *child[i][j] = quad(r - 1, 2 * x + i, 2 * y + j);
            }
            child[i][j]->insert(x0, y0);
        }
    }

    // int64 mindist(int x0, int y0) const
    // {
    //     square3x3 s;
    //     s.q[1][1] = this;
    //     return s.mindist(x0, y0);
    // }

    void min_dist(int x0, int y0, int64 &min_dist) const
    {
        if (r == 0)
            min_dist = std::min(min_dist, dist(x, y, x0, y0));
        else if (lower_bound(x0, y0) < min_dist)
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    if (child[i][j])
                        child[i][j]->min_dist(x0, y0, min_dist);
        fprintf(stderr, "[%d, %d][%d, %d]: %lld\n", x_min(), x_max(), y_min(), y_max(), min_dist);
    }
};

quad memory[200 * 1024 * 1024 / sizeof(quad)], *next = memory;
quad *memory_alloc() { return next++; }

int main()
{
    int n;
    quad qtree(31, 0, 0);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        qtree.insert(x, y);
    }
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        int x0, y0;
        scanf("%d%d", &x0, &y0);
        int64 min_dist = std::numeric_limits<int64>::max();
        qtree.min_dist(x0, y0, min_dist);
        printf("%lld\n", min_dist);
    }
    return 0;
}