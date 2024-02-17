#include <math.h>
#include <stdio.h>

int main()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    double p = (a + b + c) / 2.0;
    printf("%.2lf\n", sqrt(p * (p - a) * (p - b) * (p - c)));
    return 0;
}