#include <stdio.h>
#include <list>
#include <assert.h>
#include <memory>
#include <limits.h>

std::unique_ptr<std::list<int>> radix_sort(std::unique_ptr<std::list<int>> x)
{
    for (int r = 0; r < 32 - 1; r++)
    {
        auto l = std::make_unique<std::list<int>>();
        auto g = std::make_unique<std::list<int>>();
        bool is_ok = true;
        int last = INT_MIN;
        for (auto x_i : *x)
        {
            (((x_i >> r) & 1) ? g : l)->push_back(x_i);
            is_ok = is_ok && x_i > last;
            last = x_i;
        }
        if (is_ok)
            break;
        l->splice(l->end(), *g);
        x = std::move(l);
    }
    return x;
}

int main()
{
    int n;
    scanf("%d", &n);
    auto x = std::make_unique<std::list<int>>();
    for (int i = 0; i < n; i++)
    {
        int x_i;
        scanf("%d", &x_i);
        x->push_back(x_i);
    }
    x = radix_sort(std::move(x));
    for (auto x_i : *x)
        printf("%d\n", x_i);
    return 0;
}
