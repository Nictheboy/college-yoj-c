#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define MIN(A, B) (((A) > (B)) ? (B) : (A))

int cal_currect_positons(int target, int guess)
{
    int target_numbers[4]; // 计算机生成的数的四位分别是
    int guess_numbers[4];  // 用户猜的数的四位分别是
    for (int i = 0; i < 4; i++) {
        target_numbers[i] = target % 10;
        target /= 10;
    }
    for (int i = 0; i < 4; i++) {
        guess_numbers[i] = guess % 10;
        guess /= 10;
    }
    int counter = 0; // 统计相同的位置数
    for (int i = 0; i < 4; i++) {
        if (target_numbers[i] == guess_numbers[i])
            counter++;
    }
    return counter;
}

int cal_currect_numbers(int target, int guess)
{
    int target_numbers[10] = {0}; // 数字 i 在计算机生成的数中出现几次
    int guess_numbers[10] = {0};  // 数字 i 在用户猜的数中出现几次
    for (int i = 0; i < 4; i++) {
        target_numbers[target % 10]++;
        target /= 10;
    }
    for (int i = 0; i < 4; i++) {
        guess_numbers[guess % 10]++;
        guess /= 10;
    }
    int counter = 0; // 统计重合的数字的总数
    for (int i = 0; i < 10; i++) {
        counter += MIN(target_numbers[i], guess_numbers[i]);
    }
    return counter;
}

bool posible[10000];

void init()
{
    for (int i = 0; i < 10000; i++)
        posible[i] = true; // 没有任何输入时，任何数都有可能
}

void select(int guess, int currect_numbers, int currect_positions)
{
    for (int i = 0; i < 10000; i++) {
        // 如果 i 不满足条件，淘汰 i
        if (cal_currect_numbers(i, guess) != currect_numbers
            || cal_currect_positons(i, guess) != currect_positions)
            posible[i] = false;
    }
}

int main()
{
    init();

    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int guess, currect_numbers, currect_positions;
        scanf("%d%d%d", &guess, &currect_numbers, &currect_positions);
        // 淘汰不满足条件的数
        select(guess, currect_numbers, currect_positions);
    }

    int unique_number;
    int count = 0;
    for (int i = 0; i < 10000; i++) {
        if (posible[i]) {
            unique_number = i;
            count++;
        }
    }
    if (count == 1)
        printf("%d", unique_number);
    else
        printf("Not sure");
    return 0;
}
