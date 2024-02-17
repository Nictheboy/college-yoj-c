#include <stdio.h>
#include <string.h>

#define BASE 998244353

char str[200005];

// mode = abcdcd

int search1(int len, char b, char c, char d)
{
    int cnt = 0;
    for (int i = 0; i < len; i++)
    {
        const char ch = str[i];
        if (ch != b && ch != c && ch != d)
            cnt++;
    }
    return cnt;
}

int search2(int len, char c, char d)
{
    int cnt = 0;
    for (int i = 0; i < len; i++)
    {
        const char ch = str[i];
        if (ch != c && ch != d)
            cnt = (cnt + search1(i, ch, c, d)) % BASE;
    }
    return cnt;
}

int search3(int len, char c, char d)
{
    int cnt = 0;
    for (int i = 0; i < len; i++)
    {
        const char ch = str[i];
        if (ch == c)
            cnt = (cnt + search2(i, c, d)) % BASE;
    }
    return cnt;
}

int search4(int len, char c, char d)
{
    int cnt = 0;
    for (int i = 0; i < len; i++)
    {
        const char ch = str[i];
        if (ch == d)
            cnt = (cnt + search3(i, c, d)) % BASE;
    }
    return cnt;
}

int search5(int len, char d)
{
    int cnt = 0;
    for (int i = 0; i < len; i++)
    {
        const char ch = str[i];
        if (ch != d)
            cnt = (cnt + search4(i, ch, d)) % BASE;
    }
    return cnt;
}

int search6(int len)
{
    int cnt = 0;
    for (int i = 0; i < len; i++)
    {
        const char ch = str[i];
        cnt = (cnt + search5(i, ch)) % BASE;
    }
    return cnt;
}

int main()
{
    scanf("%s", str);
    const int result = search6(strlen(str));
    printf("%d", result);
    return 0;
}
