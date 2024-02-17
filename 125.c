#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef long long int64;

typedef struct {
    int n;
    int64 *data; // n*n
    int sign;    // if sign = 1, targetValue = Det(Current)
                 // if sign = -1, targetValue = -Det(Current)
} Det, *pDet;

void DetInit(pDet pd)
{
    scanf("%d", &pd->n);
    int n = pd->n;
    pd->data = (int64 *)malloc(sizeof(int64) * n * n);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            scanf("%lld", &pd->data[r * n + c]);
        }
    }
    pd->sign = 1;
}

void DetSwapColumn(pDet pd, int c1, int c2)
{
    if (c1 == c2)
        return;
    int n = pd->n;
    for (int r = 0; r < n; r++) {
        int64 temp = pd->data[r * n + c1];
        pd->data[r * n + c1] = pd->data[r * n + c2];
        pd->data[r * n + c2] = temp;
    }
    pd->sign *= -1;
}

// return true if success
// return false if no zero at Row[r] or Col[c],
// which means TargetValue = sign * Det(Current) = 0
bool DetEnsureNoneZeroAt(pDet pd, int r, int c)
{
    int n = pd->n;
    if (pd->data[r * n + c] != 0)
        return true;
    for (int c2 = 0; c2 < n; c2++) {
        if (pd->data[r * n + c2] != 0) {
            DetSwapColumn(pd, c, c2);
            return true;
        }
    }
    return false;
}

void DetPrint(pDet pd)
{
    int n = pd->n;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            printf("%lld ", pd->data[r * n + c]);
        }
        printf("\n");
    }
}

// The data in Det is damaged in this procudure, but the return value equals TargetValue
// I could not understand the algorithm, but for more info
// see https://cs.stackexchange.com/questions/124759/determinant-calculation-bareiss-vs-gauss-algorithm
int DetSolveWithBareissAlg(pDet pd)
{
    int n = pd->n;
    int64 *data = pd->data;
    for (int k = 0; k < n - 1; k++) {
        if (!DetEnsureNoneZeroAt(pd, k, k))
            return 0;
        // Apply formula
        for (int r = k + 1; r < n; r++) {
            for (int c = k + 1; c < n; c++) {
                data[r * n + c] = data[k * n + k] * data[r * n + c] - data[r * n + k] * data[k * n + c];
                if (k != 0) {
                    data[r * n + c] /= data[(k - 1) * n + k - 1];
                }
            }
        }
    }
    // DetPrint(pd);
    return pd->sign * data[n * n - 1];
}

int main()
{
    Det d;
    DetInit(&d);
    printf("%d", DetSolveWithBareissAlg(&d));
    return 0;
}
