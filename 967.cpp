#include <iostream>
#include <string>
#include <string.h>
#include <stack>
#include <deque>

struct item
{
    enum op_type
    {
        ADD,
        MUL,
    };
    enum
    {
        VAL,
        OP,
    } type;
    union
    {
        int val;
        op_type op;
    } data;
};

typedef std::deque<item> deque;

const char *match_parenthesis(const char *begin)
{
    if (*begin == '(')
    {
        char cnt = 1;
        while (cnt)
        {
            char c = *++begin;
            if (c == '(')
                cnt++;
            if (c == ')')
                cnt--;
        }
        return begin;
    }
    else
        return begin;
}

bool is_wrapped_by_parentheses(const char *begin, const char *end)
{
    if (*begin != '(' || *(end - 1) != ')')
        return false;
    int cnt = 1;
    for (const char *p = begin + 1; p < end - 1; p++)
    {
        if (*p == '(')
            ++cnt;
        else if (*p == ')')
            --cnt;
        if (cnt == 0)
            return false;
    }
    return cnt == 1;
}

const char *find_first(const char *begin, const char *end, char c)
{
    for (const char *p = begin; p < end; p++)
    {
        if (*p == c)
            return p;
        p = match_parenthesis(p);
    }
    return end;
}

void handle(deque &q, const char *begin, const char *end);

void handle_num(deque &q, const char *begin, const char *end)
{
    int num;
    sscanf(begin, "%d", &num);
    q.push_back({item::VAL, {.val = num}});
}

void handle_mul(deque &q, const char *begin, const char *end)
{
    const char *from = begin, *to = find_first(from, end, '*');
    if (is_wrapped_by_parentheses(from, to))
        handle(q, from + 1, to - 1);
    else
        handle_num(q, from, to);
    while (to != end)
    {
        from = to + 1;
        to = find_first(from, end, '*');
        if (is_wrapped_by_parentheses(from, to))
            handle(q, from + 1, to - 1);
        else
            handle_num(q, from, to);
        q.push_back(item{item::OP, {.op = item::MUL}});
    }
}

void handle_add(deque &q, const char *begin, const char *end)
{
    const char *from = begin, *to = find_first(from, end, '+');
    if (is_wrapped_by_parentheses(from, to))
        handle(q, from + 1, to - 1);
    else
        handle_mul(q, from, to);
    while (to != end)
    {
        from = to + 1;
        to = find_first(from, end, '+');
        if (is_wrapped_by_parentheses(from, to))
            handle(q, from + 1, to - 1);
        else
            handle_mul(q, from, to);
        q.push_back(item{item::OP, {.op = item::ADD}});
    }
}

void handle(deque &q, const char *begin, const char *end)
{
    handle_add(q, begin, end);
}

void print(deque &q)
{
    deque q_copy = q;
    while (!q_copy.empty())
    {
        item itm = q_copy.front();
        q_copy.pop_front();
        if (itm.type == item::VAL)
            printf("%d ", itm.data.val);
        else if (itm.data.op == item::ADD)
            printf("+ ");
        else
            printf("* ");
    }
    printf("\n");
}

int cal(item::op_type op, int a, int b)
{
    if (op == item::ADD)
        return a + b;
    else
        return a * b;
}

int main()
{
    std::string input;
    std::getline(std::cin, input);
    const char *str = input.c_str();
    deque q;
    handle(q, str, str + strlen(str) - 1);
    print(q);

    std::stack<int> stk;
    while (!q.empty())
    {
        item itm = q.front();
        q.pop_front();
        if (itm.type == item::VAL)
            stk.push(itm.data.val);
        else
        {
            int b = stk.top();
            stk.pop();
            int a = stk.top();
            stk.pop();
            int result = cal(itm.data.op, a, b);
            stk.push(result);
        }
    }
    printf("%d\n", stk.top());
    return 0;
}
