#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

typedef long long int64;

typedef struct {
    int count_of[6];
    int score;
} Rule;

const Rule rules[12] = {
    {{2, 0, 0, 4, 0, 0}, 2048},
    {{0, 0, 0, 6, 0, 0}, 1024},
    {{6, 0, 0, 0, 0, 0}, 512},
    {{0, 6, 0, 0, 0, 0}, 256},
    {{0, 0, 0, 5, 0, 0}, 128},
    {{0, 5, 0, 0, 0, 0}, 64},
    {{0, 0, 0, 4, 0, 0}, 32},
    {{1, 1, 1, 1, 1, 1}, 16},
    {{0, 0, 0, 3, 0, 0}, 8},
    {{0, 4, 0, 0, 0, 0}, 4},
    {{0, 0, 0, 2, 0, 0}, 2},
    {{0, 0, 0, 1, 0, 0}, 1},
};

// return 0 if failed
int cal_score(int input[])
{
    int count[6] = {0};
    for (int i = 0; i < 6; i++) {
        count[input[i] - 1]++;
    }
    for (int i = 0; i < sizeof(rules) / sizeof(Rule); i++) {
        bool flag = true;
        for (int j = 0; j < 6; j++) {
            if (false == (count[j] >= rules[i].count_of[j])) {
                flag = false;
                break;
            }
        }
        if (flag)
            return rules[i].score;
    }
    return 0;
}

int main()
{
    int n;
    int64 count_score = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int input[6];
        for (int j = 0; j < 6; j++)
            scanf("%d", input + j);
        int score = cal_score(input);
        if (score == 0)
            break;
        else
            count_score += score;
    }
    printf("%llx", count_score);
    return 0;
}
