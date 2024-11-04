#include <stack>
#include <cstdio>

int input()
{
    int x;
    scanf("%d", &x);
    return x;
}

int max(int a, int b) { return a > b ? a : b; }

struct stick
{
    int x, h;
};

class solver
{
private:
    std::stack<stick> instance;
    int i = 0, max_area = 0;

public:
    void consider(int h)
    {
        int x = i;
        while (!instance.empty() && instance.top().h > h)
        {
            max_area = max(max_area, instance.top().h * (i - instance.top().x));
            x = instance.top().x;
            instance.pop();
        }
        instance.push(stick{x, h});
        ++i;
    }

    int result() { return max_area; }
};

int main()
{
    auto n = input();
    auto instance = solver();
    instance.consider(0);
    for (int i = 0; i < n; i++)
        instance.consider(input());
    instance.consider(0);
    printf("%d\n", instance.result());
    return 0;
}
