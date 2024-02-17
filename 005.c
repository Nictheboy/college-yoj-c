#include <stdio.h>

int main()
{
    char c = getchar();
    if (c >= 'a' && c <= 'z')
        putchar(c - 'a' + 'A');
    else
        putchar(c-'A'+'a');
}
