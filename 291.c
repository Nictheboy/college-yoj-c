#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 128
#define BASE 10000000000000000 // mod 10^16
#define BASE_TEN 16

#define _MACRO_STR(A) #A
#define MACRO_STR(A) _MACRO_STR(A)

typedef long long ll;

typedef struct {
    ll part[SIZE]; // mod 10^16
} number;

number add(const number *pnum1, const number *pnum2)
{
    number num;
    int carry = 0;
    for (int i = 0; i < SIZE; i++) {
        const ll result_raw = carry + pnum1->part[i] + pnum2->part[i];
        num.part[i] = result_raw % BASE;
        carry = result_raw / BASE;
    }
    return num;
}

number one()
{
    number num;
    num.part[0] = 1;
    for (int i = 1; i < SIZE; i++) {
        num.part[i] = 0;
    }
    return num;
}

number neg(const number *pnum)
{
    number num;
    for (int i = 0; i < SIZE; i++) {
        num.part[i] = BASE - pnum->part[i] - 1;
    }
    number num_one = one();
    return add(&num, &num_one);
}

void print(const number *pnum)
{
    if (pnum->part[SIZE - 1] < BASE / 2) {
        // possitive
        bool number_begun = false;
        for (int i = SIZE - 1; i >= 0; i--) {
            const ll part = pnum->part[i];
            if (false == number_begun) {
                if (part == 0)
                    continue;
                else {
                    number_begun = true;
                    printf("%lld", part);
                }
            } else {
                printf("%0" MACRO_STR(BASE_TEN) "lld", part);
            }
        }
    } else {
        // negative
        printf("-");
        number neg_num = neg(pnum);
        print(&neg_num);
    }
}

number convert(const char str_raw[])
{
    number num;
    const int sgn = (str_raw[0] == '+' || str_raw[0] == '-') ?
                        (str_raw[0] == '+' ? 1 : -1) :
                        1;
    const char *str = (str_raw[0] == '+' || str_raw[0] == '-') ? str_raw + 1 : str_raw;
    const int length = strlen(str);
    for (int i = 0; i < SIZE; i++) {
        num.part[i] = 0;
        // for (int j = length - i * BASE_TEN - 1; j >= length - (i + 1) * BASE_TEN && j >= 0; j--) {
        for (int j = length - (i + 1) * BASE_TEN; j < length - i * BASE_TEN; j++) {
            if (j >= 0)
                num.part[i] = num.part[i] * 10 + (str[j] - '0');
        }
        assert(num.part[i] < BASE);
    }
    if (sgn == 1)
        return num;
    else
        return neg(&num);
}

int main()
{
    char op[2], number1[2001], number2[2001];
    scanf("%s%s%s", op, number1, number2);
    const number num1 = convert(number1);
    const number num2 = convert(number2);
    if (op[0] == '+') {
        const number result = add(&num1, &num2);
        print(&result);
    } else {
        const number neg_num2 = neg(&num2);
        const number result = add(&num1, &neg_num2);
        print(&result);
    }
    return 0;
}
