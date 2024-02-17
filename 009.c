#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d,%d", &a, &b);
    double c, d;
    scanf("%lf %lf", &c, &d);
    char e, f;
    scanf(" %c, %c", &e, &f);
    printf("%d,%d\n", a, b);
    printf("%.1lf %.1lf\n", c, d);
    printf(" %c, %c", e, f);
    return 0;
}
