#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

const int capacity[8] = {120, 40, 85, 50, 100, 140, 70, 100};
bool able_to_use[4][8];

void init_able_to_use()
{
    for (int i = 0; i < 4; i++) {
        int N;
        scanf("%d", &N);
        for (int j = 0; j < 8; j++) {
            if (N <= capacity[j])
                able_to_use[i][j] = true;
            else
                able_to_use[i][j] = false;
        }
    }
}

void search(int array[], bool used[], const int index, bool *flag)
{
    if (index == 4) {
        printf("%d %d %d %d\n", array[0] + 1, array[1] + 1, array[2] + 1, array[3] + 1);
        *flag = true;
    } else {
        for (int i = 0; i < 8; i++) {
            if (false == used[i]) {
                if (able_to_use[index][i]) {
                    used[i] = true;
                    array[index] = i;
                    search(array, used, index + 1, flag);
                    used[i] = false;
                }
            }
        }
    }
}

int main()
{
    init_able_to_use();
    int array[4];
    bool used[8] = {0};
    bool flag = false;
    search(array, used, 0, &flag);
    if (false == flag)
        printf("-1");
    return 0;
}
