#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

double mysin(double x, double precision)
{
    if (x < 0)
        return mysin(x + 2 * M_PI, precision);
    if (x >= 2 * M_PI)
        return mysin(x - 2 * M_PI, precision);
    if (x >= M_PI)
        return -mysin(x - M_PI, precision);
    if (x >= M_PI_2)
        return mysin(M_PI - x, precision);
    int index;
    int sign;
    double factor1;
    int factor2;
    double current_sum;
    double last_added_part = precision + 1;
    for (index = 0, sign = 1, factor1 = x, factor2 = 1, current_sum = 0;
         fabs(last_added_part) >= precision;
         index++, sign *= -1, factor1 *= x * x, factor2 *= 2 * index * (2 * index + 1)) {
        last_added_part = sign * factor1 / factor2;
        current_sum += last_added_part;
    }
    return current_sum;
}

double mycos(double x, double precision)
{
    return mysin(x + M_PI_2, precision);
}

int main()
{
    double x, precision;
    scanf("%lf%lf", &x, &precision);
    printf("%lf\n%lf", mysin(x, precision), mycos(x, precision));
    return 0;
}
