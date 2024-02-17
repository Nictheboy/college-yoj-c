#include <stdio.h>

typedef unsigned int uint32;

// uint32_max = 4,294,967,296
typedef struct {
    uint32 a11;
    uint32 a12;
    uint32 a21;
    uint32 a22;
} matrix;

matrix multicate(matrix A, matrix B)
{
    matrix ret;
    ret.a11 = (A.a11 * B.a11 + A.a12 * B.a21) % 10000;
    ret.a12 = (A.a11 * B.a12 + A.a12 * B.a22) % 10000;
    ret.a21 = (A.a21 * B.a11 + A.a22 * B.a21) % 10000;
    ret.a22 = (A.a21 * B.a12 + A.a22 * B.a22) % 10000;
    return ret;
}

int main()
{
    matrix powers[32];
    powers[0].a11 = 1;
    powers[0].a12 = 1;
    powers[0].a21 = 1;
    powers[0].a22 = 0;
    // show(powers[0]);
    for (int i = 1; i < 32; i++) {
        powers[i] = multicate(powers[i - 1], powers[i - 1]);
        // show(powers[i]);
    }

    uint32 n;
    matrix result;
    result.a11 = 1;
    result.a12 = 0;
    result.a21 = 0;
    result.a22 = 1;
    scanf("%d", &n);
    for (uint32 i = 0, mask = 1; i < 32; i++, mask = mask << 1) {
        if (mask & n) {
            result = multicate(result, powers[i]);
        }
    }
    printf("%d", result.a21);

    return 0;
}
