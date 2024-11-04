#include <deque>
#include <cstdio>

template <typename T>
class queap
{
private:
    std::deque<T> P, Q;

public:
    void push(const T &element)
    {
        int cnt = 0;
        for (auto itor = P.rbegin(); itor != P.rend() && *itor < element; itor++)
            cnt++;
        for (int i = 0; i < cnt; i++)
            P.pop_back();
        P.push_back(element);
        Q.push_back(element);
    }

    T pop()
    {
        T element = Q.front();
        if (P.front() == element)
            P.pop_front();
        Q.pop_front();
        return element;
    }

    T max()
    {
        return P.front();
    }
};

int main()
{
    queap<int> instant;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int op, element;
        scanf("%d", &op);
        switch (op)
        {
        case 0:
            instant.pop();
            break;

        case 1:
            scanf("%d", &element);
            instant.push(element);
            break;

        case 2:
            element = instant.max();
            printf("%d\n", element);
            break;
        }
    }
    return 0;
}
