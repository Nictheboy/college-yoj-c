#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define PART_MAX 999999999 // 999 999 999 (9 of 9)
#define BASE 1000000000    // 1 000 000 000 (9 of 0)

typedef struct {
    unsigned int blocks; // >= 1
    unsigned int *data;  // each block no bigger than 999 999 999 (9 of 9)
                         // uint_max = 4 294 967 296
    // value = data[0] + data[1]*10^9 + data[2]*10^18 + ... + data[blocks-1]*10^(9*(blocks-1))
} num;

void print(num n)
{
    printf("%d", n.data[n.blocks - 1]);
    for (int i = n.blocks - 2; i >= 0; i--) {
        printf("%09d", n.data[i]);
    }
}

num add(num a, num b)
{
    int max_of_blocks = MAX(a.blocks, b.blocks);
    int min_of_blocks = MIN(a.blocks, b.blocks);
    unsigned int *new_data = (unsigned int *)malloc(sizeof(int) * (max_of_blocks + 1));
    int carry = 0;
    for (int i = 0; i < min_of_blocks; i++) {
        unsigned int part_sum = carry + a.data[i] + b.data[i];
        unsigned int reminder = part_sum % BASE;
        carry = (part_sum - reminder) / BASE;
        new_data[i] = reminder;
    }

    if (a.blocks > b.blocks) {
        for (int i = min_of_blocks; i < max_of_blocks; i++) {
            unsigned int part_sum = carry + a.data[i];
            unsigned int reminder = part_sum % BASE;
            carry = (part_sum - reminder) / BASE;
            new_data[i] = reminder;
        }
    } else if (a.blocks < b.blocks) {
        for (int i = min_of_blocks; i < max_of_blocks; i++) {
            unsigned int part_sum = carry + b.data[i];
            unsigned int reminder = part_sum % BASE;
            carry = (part_sum - reminder) / BASE;
            new_data[i] = reminder;
        }
    }

    if (carry == 0) {
        num result;
        result.blocks = max_of_blocks;
        result.data = new_data;
        return result;
    } else {
        num result;
        result.blocks = max_of_blocks + 1;
        new_data[max_of_blocks] = carry;
        result.data = new_data;
        return result;
    }
}

num from_small_int(int value) // assume value < PART_MAX
{
    num temp;
    temp.blocks = 1;
    temp.data = (unsigned int *)malloc(sizeof(int));
    temp.data[0] = value;
    return temp;
}

/*
// possible memory leak, but no worry since it's for oj
num F(int n)
{
    // f[1] = 1
    num f = from_small_int(1);

    // We define sum[k] = f[1] +...+ f[k]
    // sum[0] = 1
    num sum = from_small_int(1);

    // Notice that:
    // f[k] = k*k + sum[k-1]
    // sum[k] = sum[k-1] + f[k]
    for (int k = 2; k <= n; k++) { // repeat n-1 times
        f = add(from_small_int(k * k), sum);
        sum = add(sum, f);
    }

    return f;
}
*/

// new version, no memory leak :)
// afterall, nobody want to see something like 211532 KiB for a single calculation
num F(int n)
{
    // f[1] = 1
    num f = from_small_int(1);

    // We define sum[k] = f[1] +...+ f[k]
    // sum[0] = 1
    num sum = from_small_int(1);

    // Notice that:
    // f[k] = k*k + sum[k-1]
    // sum[k] = sum[k-1] + f[k]
    for (int k = 2; k <= n; k++) { // repeat n-1 times
        unsigned int *origin_f = f.data;
        unsigned int *origin_sum = sum.data;
        f = add(from_small_int(k * k), sum);
        sum = add(sum, f);
        free(origin_f);
        free(origin_sum);
    }

    return f;
}

int main()
{
    int n;
    scanf("%d", &n);
    print(F(n));
}
