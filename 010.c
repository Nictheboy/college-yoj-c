#include <stdio.h>

int main()
{
    int F;
    scanf("%d", &F);
    double C = (double)(F - 32) * 5 / 9;
    printf("%.2lf\n", C);
    return 0;
}
