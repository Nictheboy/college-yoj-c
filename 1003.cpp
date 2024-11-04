#include <iostream>

enum op
{
    I,
    O,
};

struct status
{
    const char *a, *b;
    int n, i_a, i_b, n_stack, n_ops;
    char *stack;
    op *ops;

    void solve()
    {
        if (n_ops < n * 2)
        {
            if (i_a < n)
            {
                ops[n_ops++] = I;
                stack[n_stack++] = a[i_a++];
                solve();
                --n_ops;
                --n_stack;
                --i_a;
            }
            if (n_stack > 0 && stack[n_stack - 1] == b[i_b])
            {
                ops[n_ops++] = O;
                int backup = stack[--n_stack];
                ++i_b;
                solve();
                --n_ops;
                stack[n_stack++] = backup;
                --i_b;
            }
        }
        else
        {
            for (int i = 0; i < n * 2; i++)
                printf("%c ", ops[i] == I ? 'i' : 'o');
            printf("\n");
        }
    }
};

int main()
{
    while (!std::cin.eof())
    {
        std::string a, b;
        std::cin >> a >> b;
        if (a.empty() || b.empty())
            break;
        status s;
        s.a = a.c_str();
        s.b = b.c_str();
        s.n = a.length();
        s.i_a = 0;
        s.i_b = 0;
        s.n_stack = 0;
        s.n_ops = 0;
        s.stack = new char[s.n];
        s.ops = new op[s.n * 2];
        printf("[\n");
        s.solve();
        printf("]\n");
        delete[] s.stack;
        delete[] s.ops;
    }
    return 0;
}
