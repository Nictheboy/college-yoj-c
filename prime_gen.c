#include <stdio.h>
#include <stdbool.h>

const int N = 45721;

bool is_prime(const int n)
{
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main()
{
    printf("{2");
    for (int i = 3; i <= N; i++)
    {
        if (is_prime(i))
            printf(", %d", i);
    }
    printf("};");
    return 0;
}
