#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX(A, B) ((A) > (B) ? (A) : (B))

int R, C;
int *row_data;
int *mapS; // 0001: up
           // 0010: down
           // 0100: left
           // 1000: right
int *mapT;
int *visited;

int main()
{
    scanf("%d %d", &R, &C);
    row_data = (int *)malloc(sizeof(int) * (R + 2) * (C + 2));
    mapS = (int *)malloc(sizeof(int) * R * C);
    mapT = (int *)malloc(sizeof(int) * R * C);
    visited = (int *)malloc(sizeof(int) * (R + 4) * C) + C * 2;
    for (int _c = 0; _c < C + 2; _c++) {
        row_data[_c] = 10001;
    }
    for (int _c = 0; _c < C + 2; _c++) {
        row_data[_c + (R + 1) * (C + 2)] = 10001;
    }
    for (int r = 0; r < R; r++) {
        row_data[C + 2 + r * (C + 2)] = 10001;
    }
    for (int r = 0; r < R; r++) {
        row_data[C + 2 + C + 1 + r * (C + 2)] = 10001;
    }
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            scanf("%d", &row_data[C + 3 + r * (C + 2) + c]);
        }
    }
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            int flag = 0;
            int value = row_data[C + 3 + r * (C + 2) + c];
            int valueU = row_data[C + 3 + (r - 1) * (C + 2) + c];
            int valueD = row_data[C + 3 + (r + 1) * (C + 2) + c];
            int valueL = row_data[C + 3 + r * (C + 2) + c - 1];
            int valueR = row_data[C + 3 + r * (C + 2) + c + 1];
            if (valueU < value)
                flag |= 1;
            if (valueD < value)
                flag |= 2;
            if (valueL < value)
                flag |= 4;
            if (valueR < value)
                flag |= 8;
            mapS[r * C + c] = flag;
            if (flag == 0)
                visited[r * C + c] = -1;
            else
                visited[r * C + c] = C * R + 100;
        }
    }
    for (int _c = 0; _c < C + 2; _c++) {
        row_data[_c] = -1;
    }
    for (int _c = 0; _c < C + 2; _c++) {
        row_data[_c + (R + 1) * (C + 2)] = -1;
    }
    for (int r = 0; r < R; r++) {
        row_data[C + 2 + r * (C + 2)] = -1;
    }
    for (int r = 0; r < R; r++) {
        row_data[C + 2 + C + 1 + r * (C + 2)] = -1;
    }
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            int flag2 = 0;
            int value = row_data[C + 3 + r * (C + 2) + c];
            int valueU = row_data[C + 3 + (r - 1) * (C + 2) + c];
            int valueD = row_data[C + 3 + (r + 1) * (C + 2) + c];
            int valueL = row_data[C + 3 + r * (C + 2) + c - 1];
            int valueR = row_data[C + 3 + r * (C + 2) + c + 1];
            if (valueU > value)
                flag2 |= 1;
            if (valueD > value)
                flag2 |= 2;
            if (valueL > value)
                flag2 |= 4;
            if (valueR > value)
                flag2 |= 8;
            mapT[r * C + c] = flag2;
        }
    }
    int flag = 0;
    int i;
    for (i = 0; !flag; i++) {
        flag = 1;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                int local_flag = -1;
                int s = mapS[r * C + c];
                int up = visited[(r - 1) * C + c];
                int down = visited[(r + 1) * C + c];
                int left = visited[r * C + c - 1];
                int right = visited[r * C + c + 1];
                if ((s & 1) && up < i) {
                    local_flag = MAX(local_flag, up) + 1;
                }
                if ((s & 2) && down < i) {
                    local_flag = MAX(local_flag, down) + 1;
                }
                if ((s & 4) && left < i) {
                    local_flag = MAX(local_flag, left) + 1;
                }
                if ((s & 8) && right < i) {
                    local_flag = MAX(local_flag, right) + 1;
                }
                if (local_flag >= 0 && local_flag != visited[r * C + c]) {
                    visited[r * C + c] = local_flag;
                    flag &= 0;
                }
            }
        }
    }
    int max = visited[0];
    for (int i = 0; i < R * C; i++)
        max = MAX(max, visited[i]);
    printf("%d", max + 2);
    return 0;
}
