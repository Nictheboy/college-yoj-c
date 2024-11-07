#include <stdio.h>
#include <stack>

class steap
{
private:
    std::stack<int> master;
    std::stack<int> maxes;

public:
    void push(int val)
    {
        master.push(val);
        if (maxes.empty() || val >= maxes.top())
            maxes.push(val);
    }

    void pop()
    {
        if (maxes.top() == master.top())
            maxes.pop();
        master.pop();
    }

    int top() const
    {
        return master.top();
    }

    int max() const
    {
        return maxes.top();
    }
};

int main()
{
    steap instance;
    int k, op, x;
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            scanf("%d", &x);
            instance.push(x);
            break;

        case 2:
            instance.pop();
            break;

        case 3:
            x = instance.top();
            printf("%d\n", x);
            break;

        case 4:
            x = instance.max();
            printf("%d\n", x);
            break;
        }
    }
    return 0;
}
