#include <cstdio>
#include <stack>

#define int long long
#define MAX_LENGTH 100000

int P[MAX_LENGTH], Q[MAX_LENGTH], n;
std::stack<int> stack;

int input()
{
    int x;
    scanf("%lld", &x);
    return x;
}

signed main()
{
    n = input();
    for (int i = 0; i < n; i++)
        P[i] = input();
    for (int i = 0; i < n; i++)
        Q[i] = input();
    for (int i = 0, j = 0; i < n; i++)
    {
        if (!stack.empty() && stack.top() == Q[i])
            stack.pop();
        else
        {
            while (j < n && P[j] != Q[i])
                stack.push(P[j++]);
            if (j == n)
            {
                printf("No\n");
                return 0;
            }
            j++;
        }
    }
    printf("Yes\n");
    return 0;
}
