#include <iostream>
#include <assert.h>

auto add(std::string a, std::string b)
{
    auto c = std::string();
    auto len = std::max(a.length(), b.length()) + 1;
    c.resize(len);
    auto r = 0;
    for (auto i = 0; i < len; i++)
    {
        auto a_i = i < a.length() ? a[a.length() - i - 1] - '0' : 0;
        auto b_i = i < b.length() ? b[b.length() - i - 1] - '0' : 0;
        c[len - i - 1] = (a_i + b_i + r) % 10 + '0';
        r = (a_i + b_i + r) / 10;
    }
    return c;
}

auto sub(std::string a, std::string b)
{
    auto c = std::string();
    auto len = std::max(a.length(), b.length());
    c.resize(len);
    auto r = 0;
    for (auto i = 0; i < len; i++)
    {
        auto a_i = i < a.length() ? a[a.length() - i - 1] - '0' : 0;
        auto b_i = i < b.length() ? b[b.length() - i - 1] - '0' : 0;
        c[len - i - 1] = ((a_i - b_i + r) + 10) % 10 + '0';
        r = ((a_i - b_i + r) + 10) / 10 - 1;
    }
    return c;
}

auto align(std::string a, int n)
{
    assert(a.length() <= n);
    auto b = std::string();
    b.resize(n);
    for (auto i = 0; i < n - a.length(); i++)
        b[i] = '0';
    for (auto i = n - a.length(); i < n; i++)
        b[i] = a[i - (n - a.length())];
    return b;
}

auto trim(std::string a)
{
    auto n_trim = 0;
    for (; n_trim < a.length() && a[n_trim] == '0'; n_trim++)
        ;
    return a.substr(n_trim);
}

auto shift(std::string a, int n)
{
    auto c = std::string();
    c.resize(a.length() + n);
    for (auto i = 0; i < a.length(); i++)
        c[i] = a[i];
    for (auto i = a.length(); i < a.length() + n; i++)
        c[i] = '0';
    return c;
}

std::string mul(std::string a, std::string b);

auto mul_aligned(std::string a, std::string b, int n)
{
    assert(a.length() == n);
    assert(b.length() == n);
    if (n <= 4)
    {
        return std::to_string(std::stoi(a) * std::stoi(b));
    }
    else
    {
        auto a_left = a.substr(0, n / 2);
        auto a_right = a.substr(n / 2);
        auto b_left = b.substr(0, n / 2);
        auto b_right = b.substr(n / 2);
        auto p1 = mul_aligned(a_left, b_left, n / 2);
        auto p2 = mul(add(a_left, a_right), add(b_left, b_right));
        auto p3 = mul_aligned(a_right, b_right, n - n / 2);
        auto p4 = sub(sub(p2, p1), p3);
        return add(shift(p1, (n - n / 2) * 2), add(shift(p4, n - n / 2), p3));
    }
}

std::string mul(std::string a, std::string b)
{
    auto n = std::max(a.length(), b.length());
    a = align(a, n);
    b = align(b, n);
    auto c = mul_aligned(a, b, n);
    return trim(c);
}

int main()
{
    std::string a, b;
    std::cin >> a >> b;
    std::cout << mul(a, b) << std::endl;
    // std::cout << add(a, b) << std::endl;
    return 0;
}
