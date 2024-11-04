#include <stack>
#include <cctype>
#include <stdio.h>
#include <cstring>
#include <cstdlib>

enum op
{
    ADD,
    MUL
};

bool input_success;
bool input_is_op;
op input_op;
int input_value;

void input()
{
    char input[20];
    int ret = scanf("%[0-9]", input);
    if (ret == -1)
        input_success = false;
    else if (ret != 0)
    {
        input_is_op = false;
        sscanf(input, "%d", &input_value);
        input_value %= 10000;
        input_success = true;
    }
    else
    {
        input_is_op = true;
        char c = getchar();
        input_success = true;
        if (c == '+')
            input_op = ADD;
        else if (c == '*')
            input_op = MUL;
        else
            input_success = false;
    }
}

int cal(op o, int x, int y)
{
    if (o == ADD)
        return (x + y) % 10000;
    else if (o == MUL)
        return (x * y) % 10000;
    else
        exit(-1);
}

signed main()
{
    std::stack<int> values;
    std::stack<op> ops;
    input();
    while (input_success)
    {
        if (input_is_op)
            ops.push(input_op);
        else
        {
            values.push(input_value);
            char c;
            if ((c = getchar()) != '*')
                while (!ops.empty())
                {
                    int x = values.top();
                    values.pop();
                    int y = values.top();
                    values.pop();
                    int result = cal(ops.top(), x, y);
                    ops.pop();
                    values.push(result);
                }
            ungetc(c, stdin);
        }
        input();
    }
    printf("%d\n", values.top());
    return 0;
}
