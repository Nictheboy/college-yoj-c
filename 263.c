#include <stdio.h>
#include <stdbool.h>
#include <math.h>
typedef long double ld;

#define TARGET 24

typedef enum
{
    add,
    minus,
    multiply,
    divide,
}
operator;

const int n_op_all = 4;
const operator op_all[4] = {add, minus, multiply, divide};

char op_name(operator op)
{
    switch (op)
    {
    case add:
        return '+';
    case minus:
        return '-';
    case multiply:
        return '*';
    case divide:
        return '/';
    }
}

ld cal(ld a, operator op, ld b)
{
    switch (op)
    {
    case add:
        return a + b;
    case minus:
        return a - b;
    case multiply:
        return a * b;
    case divide:
        return a / b;
    }
}

bool achieve(ld result)
{
    return fabsl(result - TARGET) < 0.00001;
}

// ((num0 op0 num1) op1 (num2 op2 num3))
bool try_1(ld num[4], operator op[3])
{
    ld result = cal(cal(num[0], op[0], num[1]), op[1], cal(num[2], op[2], num[3]));
    if (achieve(result))
    {
        printf("((%.0Lf%c%.0Lf)%c(%.0Lf%c%.0Lf))", num[0], op_name(op[0]), num[1], op_name(op[1]), num[2], op_name(op[2]), num[3]);
        return true;
    }
    return false;
}

// (((num0 op0 num1) op1 num2) op2 num3)
bool try_2(ld num[4], operator op[3])
{
    ld result = cal(cal(cal(num[0], op[0], num[1]), op[1], num[2]), op[2], num[3]);
    if (achieve(result))
    {
        printf("(((%.0Lf%c%.0Lf)%c%.0Lf)%c%.0Lf)", num[0], op_name(op[0]), num[1], op_name(op[1]), num[2], op_name(op[2]), num[3]);
        return true;
    }
    return false;
}

// ((num0 op0 (num1 op1 num2)) op2 num3)
bool try_3(ld num[4], operator op[3])
{
    ld result = cal(cal(num[0], op[0], cal(num[1], op[1], num[2])), op[2], num[3]);
    if (achieve(result))
    {
        printf("((%.0Lf%c(%.0Lf%c%.0Lf))%c%.0Lf)", num[0], op_name(op[0]), num[1], op_name(op[1]), num[2], op_name(op[2]), num[3]);
        return true;
    }
    return false;
}

// (num0 op0 ((num1 op1 num2) op2 num3))
bool try_4(ld num[4], operator op[3])
{
    ld result = cal(num[0], op[0], cal(cal(num[1], op[1], num[2]), op[2], num[3]));
    if (achieve(result))
    {
        printf("(%.0Lf%c((%.0Lf%c%.0Lf)%c%.0Lf))", num[0], op_name(op[0]), num[1], op_name(op[1]), num[2], op_name(op[2]), num[3]);
        return true;
    }
    return false;
}

// (num0 op0 (num1 op1 (num2 op2 num3)))
bool try_5(ld num[4], operator op[3])
{
    ld result = cal(num[0], op[0], cal(num[1], op[1], cal(num[2], op[2], num[3])));
    if (achieve(result))
    {
        printf("(%.0Lf%c(%.0Lf%c(%.0Lf%c%.0Lf)))", num[0], op_name(op[0]), num[1], op_name(op[1]), num[2], op_name(op[2]), num[3]);
        return true;
    }
    return false;
}

bool try_all(ld num[4], operator op[3])
{
    if (try_1(num, op))
        return true;
    if (try_2(num, op))
        return true;
    if (try_3(num, op))
        return true;
    if (try_4(num, op))
        return true;
    if (try_5(num, op))
        return true;
    return false;
}

bool iterate_op(ld num[4])
{
    for (int i = 0; i < n_op_all; i++)
        for (int j = 0; j < n_op_all; j++)
            for (int k = 0; k < n_op_all; k++)
            {
                operator op[3];
                op[0] = op_all[i];
                op[1] = op_all[j];
                op[2] = op_all[k];
                if (try_all(num, op))
                    return true;
            }
    return false;
}

bool iterate(ld num[4])
{
    int i[4];
    for (i[0] = 0; i[0] < 4; i[0]++)
    {
        for (i[1] = 0; i[1] < 4; i[1]++)
        {
            if (i[1] == i[0])
                continue;
            for (i[2] = 0; i[2] < 4; i[2]++)
            {
                if (i[2] == i[0] || i[2] == i[1])
                    continue;
                for (i[3] = 0; i[3] < 4; i[3]++)
                {
                    if (i[3] == i[0] || i[3] == i[1] || i[3] == i[2])
                        continue;
                    ld num_new[4];
                    num_new[0] = num[i[0]];
                    num_new[1] = num[i[1]];
                    num_new[2] = num[i[2]];
                    num_new[3] = num[i[3]];
                    if (iterate_op(num_new))
                        return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    ld num[4];
    scanf("%Lf%Lf%Lf%Lf", &num[0], &num[1], &num[2], &num[3]);
    if (false == iterate(num))
        printf("No Answer");
    return 0;
}
