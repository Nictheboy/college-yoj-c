#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int n, m;
long long *mat;
long long *sub;
long long *buf_1;
long long *buf_2;
long long *buf_3;
long long *buf_4;
long long *buf_5; // buf_5[i*n+j] == buf_1[i] + ... + buf_1[i+j]
long long *buf_6; // buf_6[i*n+j] == buf_2[i] + ... + buf_2[i+j]

int cal_start_1(int r0, int c0)
{
    if (r0 >= c0) {
        return r0;
    } else {
        return c0;
    }
}

int cal_end_1(int r0, int c0)
{
    if (r0 >= c0) {
        return c0 + m - 1;
    } else {
        return r0 + m - 1;
    }
}

int cal_start_2(int r0, int c0)
{
    return cal_start_1(r0, n - 1 - c0 - (m - 1));
}

int cal_end_2(int r0, int c0)
{
    return cal_end_1(r0, n - 1 - c0 - (m - 1));
}

long long cal(int r0, int c0)
{
    long long sum1 = 0;
    const int start_1 = cal_start_1(r0, c0);
    const int end_1 = cal_end_1(r0, c0);
    const bool flag_1 = start_1 <= end_1;
    long long sum2 = 0;
    const int start_2 = cal_start_2(r0, c0);
    const int end_2 = cal_end_2(r0, c0);
    const bool flag_2 = start_2 <= end_2;

    if (flag_1) {
        sum1 += start_1 > 0 ? buf_5[0 * n + start_1 - 1] : 0;
        sum1 += end_1 < n - 1 ? buf_5[(end_1 + 1) * n + (n - end_1 - 1) - 1] : 0;
        sum1 += buf_3[m - 1 - (r0 - c0)];
    } else {
        sum1 += buf_5[0 * n + n - 1];
    }

    if (flag_2) {
        sum2 += start_2 > 0 ? buf_6[0 * n + start_2 - 1] : 0;
        sum2 += end_2 < n - 1 ? buf_6[(end_2 + 1) * n + (n - end_2 - 1) - 1] : 0;
        sum2 += buf_4[m - 1 + (n - 1 - (r0 + c0 + m - 1))];
    } else {
        sum2 += buf_6[0 * n + n - 1];
    }

    return sum1 - sum2;
}

void init_buffer_5()
{
    // for length == 1
    for (int i = 0; i < n; i++) {
        buf_5[i * n + 0] = buf_1[i];
    }

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            buf_5[i * n + length - 1] = buf_5[i * n + length - 2] + buf_1[i + length - 1];
        }
    }
}

void init_buffer_6()
{
    // for length == 1
    for (int i = 0; i < n; i++) {
        buf_6[i * n + 0] = buf_2[i];
    }

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            buf_6[i * n + length - 1] = buf_6[i * n + length - 2] + buf_2[i + length - 1];
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    long long Mat[n][n];
    mat = (long long *)Mat;
    long long Sub[m][m];
    sub = (long long *)Sub;

    long long Buf_1[n];
    buf_1 = Buf_1;
    long long Buf_2[n];
    buf_2 = Buf_2;

    buf_3 = (long long *)malloc(sizeof(long long) * (2 * m - 1));
    buf_4 = (long long *)malloc(sizeof(long long) * (2 * m - 1));

    buf_5 = (long long *)malloc(sizeof(long long) * (n * n));
    buf_6 = (long long *)malloc(sizeof(long long) * (n * n));

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            scanf("%lld", &Mat[r][c]);
        }
    }
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < m; c++) {
            scanf("%lld", &Sub[r][c]);
        }
    }

    for (int i = 0; i < n; i++) {
        Buf_1[i] = Mat[i][i] * Mat[i][i];
    }
    for (int i = 0; i < n; i++) {
        Buf_2[i] = Mat[i][n - i - 1] * Mat[i][n - i - 1];
    }

    for (int f = 0; f < 2 * m - 1; f++) {
        buf_3[f] = 0;
        for (int r = 0; r < m; r++) {
            int c = m - 1 - f + r;
            if (c >= 0 && c < m) {
                buf_3[f] += Sub[r][c] * Sub[r][c];
            }
        }
    }
    for (int f = 0; f < 2 * m - 1; f++) {
        buf_4[f] = 0;
        for (int r = 0; r < m; r++) {
            int c = f - r;
            if (c >= 0 && c < m) {
                buf_4[f] += Sub[r][c] * Sub[r][c];
            }
        }
    }

    init_buffer_5();
    init_buffer_6();

    long long best = cal(0, 0);

    for (int r0 = 0; r0 <= n - m; r0++) {
        for (int c0 = 0; c0 <= n - m; c0++) {
            long long value = cal(r0, c0);
            if (value > best) {
                best = value;
            }
        }
    }

    printf("%lld", best);
    return 0;
}
