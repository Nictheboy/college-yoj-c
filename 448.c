#include <stdio.h>

int main()
{
    for (int c = getchar(); c != EOF; c = getchar())
        putchar(c);
    return 0;
}
