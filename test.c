#include <stdio.h>
int main()
{
    int a, b, c, d;
    int i, i2, i3, i4;
    int f[8] = {120, 40, 85, 50, 100, 140, 70, 100};
    scanf("%d %d %d %d", &a, &b, &c, &d);
    for (i = 0; i < 8; i++) {
        int f1[4] = {0, 0, 0, 0};
        int f2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        if (f[i] >= a) {
            f1[0] = i + 1;
            // continue;
        } else {
            continue;
        }
        for (i2 = 0; i2 < 8; i2++) {
            if (f[i2] >= b && i != i2) {
                f1[1] = i2 + 1;
                // continue;
            } else {
                continue;
            }
            for (i3 = 0; i3 < 8; i3++) {
                if (f[i3] >= c && i2 != i3 && i2 != i) {
                    f1[2] = i3 + 1;
                    // continue;
                } else {
                    continue;
                }
                for (i4 = 0; i4 < 8; i4++) {
                    if (f[i4] >= d && i4 != i && i4 != i2 && i4 != i3) {
                        f1[3] = i4 + 1;
                        // continue;
                        printf("%d %d %d %d\n", f1[0], f1[1], f1[2], f1[3]);
                    } else {
                        continue;
                    }
                }
            }
        }
    }
    return 0;
}