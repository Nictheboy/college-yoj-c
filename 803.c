#include <stdio.h>
#include <assert.h>
#include <string.h>

int max(int a, int b, int c)
{
    return (a > b && a > c) ? a
           : (b > c)        ? b
                            : c;
}

char str1[1001], str2[1001];
int cache[1000][1000];
void init_cache()
{
    int n1 = strlen(str1), n2 = strlen(str2);
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < n2; j++)
            cache[i][j] = -1;
}

int solve(int n1, int n2);
int solve_impl(int n1, int n2)
{
    assert(n1 >= 0 && n2 >= 0);
    return max(solve(n1 - 1, n2), solve(n1, n2 - 1), solve(n1 - 1, n2 - 1) + (str1[n1] == str2[n2]));
}
int solve(int n1, int n2)
{
    if (n1 < 0 || n2 < 0)
        return 0;
    if (cache[n1][n2] >= 0)
        return cache[n1][n2];
    int result = solve_impl(n1, n2);
    cache[n1][n2] = result;
    // fprintf(stderr, "solve(%d, %d) = %d\n", n1, n2, result);
    return result;
}

int main()
{
    scanf("%s%s", str1, str2);
    init_cache();
    printf("%d\n", solve(strlen(str1) - 1, strlen(str2) - 1));
    return 0;
}
