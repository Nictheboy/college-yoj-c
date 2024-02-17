#include <stdio.h>

int main()
{
    int m, n, sum = 0;
    scanf("%d,%d", &m, &n);
    for (int i = m + 1; i < n; i++) {
        if (i % 2 == 1)
            sum += i;
    }
    printf("%d", sum);
    return 0;
}
