#include <stdio.h>
#include <stdlib.h>

typedef long long int64;

int cmp(const void *pa, const void *pb)
{
    return *((int64 *)pa) - *((int64 *)pb);
}

int main()
{
    int64 input[3];
    scanf("%lld,%lld,%lld", input, input + 1, input + 2);
    qsort(input, 3, sizeof(int64), cmp);
    printf("%lld,%lld,%lld", input[0], input[1], input[2]);
    return 0;
}
