#include <stdio.h>
#include <assert.h>

#define unlikely(x) __builtin_expect(x, 0)

// int perf_counter;

class quad;
quad *memory_alloc();

class quad
{
private:
    int r, x, y;       // quad(r, x, y) := [x*2^r, (x+1)*2^r)[y*2^r, (y+1)*2^r)
    quad *child[2][2]; // child[i][j] := quad(r-1, 2x+i, 2y+j)
    int n;

    unsigned int x_pos(int idx) const
    {
        // assert(r > 0);
        // assert(0 <= idx && idx < 3);
        return (2 * x + idx) << (r - 1);
    }

    unsigned int y_pos(int idx) const
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

    int count(int x0, int x1, int y0, int y1) const
    {
        // ++perf_counter;
        if (r == 0)
            return (x0 <= x && x <= x1 && y0 <= y && y <= y1) ? n : 0;
        if (x0 <= x_pos(0) && x1 >= x_pos(2) - 1 && y0 <= y_pos(0) && y1 >= y_pos(2) - 1)
            return n;
        int total = 0;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                if (child[i][j])
                    if (x0 < x_pos(i + 1) && x1 >= x_pos(i) && y0 < y_pos(j + 1) && y1 >= y_pos(j))
                        total += child[i][j]->count(x0, x1, y0, y1);
        // fprintf(stderr, "quad(%d, %d, %d): %d\n", r, x, y, total);
        return total;
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
        int x0, x1, y0, y1;
        scanf("%d%d%d%d", &x0, &x1, &y0, &y1);
        // perf_counter = 0;
        printf("%d\n", qtree.count(x0, x1, y0, y1));
        // fprintf(stderr, "perf counter: %d\n", perf_counter);
    }
    return 0;
}