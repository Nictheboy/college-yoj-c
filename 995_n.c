#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

int main()
{
    int n;
    scanf("%d", &n);
    int *sigma = malloc(sizeof(int) * (n + 1));

    sigma[0] = 0;
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        sigma[i + 1] = sigma[i] + x;
    }

    int max_delta = 0;
    int current_min = sigma[0];
    for (int i = 1; i <= n; i++)
    {
        int current_sum = sigma[i];
        max_delta = max(max_delta, current_sum - current_min);
        current_min = min(current_min, current_sum);
    }

    printf("%d\n", max_delta);

    free(sigma);
    return 0;
}
