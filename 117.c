#include <stdio.h>
#include <malloc.h>

int n;
#define INDEX(ROW, COLUMN) ((ROW) * ((ROW) + 1) / 2 + COLUMN)
#define MAX(A, B) ((A) > (B) ? (A) : (B))
int *weight;
int *max;

int main()
{
    scanf("%d", &n);
    int length = INDEX(n, 0);
    weight = (int *)malloc(sizeof(int) * length);
    max = (int *)malloc(sizeof(int) * length);
    for (int i = 0; i < length; i++)
        scanf("%d", &weight[i]);
    for (int c = 0; c < n; c++) {
        max[INDEX(n - 1, c)] = weight[INDEX(n - 1, c)];
    }
    for (int row = n - 2; row >= 0; row--) {
        for (int c = 0; c <= row; c++) {
            max[INDEX(row, c)] = weight[INDEX(row, c)] + MAX(max[INDEX(row + 1, c)], max[INDEX(row + 1, c + 1)]);
        }
    }
    printf("%d", max[0]);
    return 0;
}
