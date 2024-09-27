#include <stdio.h>

#define ITOR(BEGIN, END, REF) for ((REF) = (BEGIN); (REF) < (END); (REF)++)

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int vec[n], *x;

    ITOR(vec, vec + n, x)
    scanf("%d", x);

    int sum = 0;
    switch (m)
    {
    case 1:
        ITOR(vec, vec + n, x)
        *x -= 1;
        ITOR(vec, vec + n, x)
        printf("%d ", *x);
        break;

    case 2:
        ITOR(vec, vec + n, x)
        *x *= 2;
        ITOR(vec, vec + n, x)
        printf("%d ", *x);
        break;

    case 3:
        ITOR(vec, vec + n, x)
        sum += *x;
        printf("%d", sum);
        break;
    }
    return 0;
}
