#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CAPACITY 1024 * 1024 * 1024
typedef unsigned char uint8;
typedef unsigned uint32;
uint32 bitmap[CAPACITY / 8];

void set(uint32 address)
{
    uint32 high = address / 8;
    uint32 low = address & 7;
    uint8 mask = 1 << low;
    bitmap[high] |= mask;
}

bool get(uint32 address)
{
    uint32 high = address / 8;
    uint32 low = address & 7;
    uint8 mask = 1 << low;
    return bitmap[high] & mask;
}

int main()
{
    int n;
    scanf("%d", &n);
    uint32 *processed = malloc(sizeof(int) * n);
    int n_processed = 0;

    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        if (!get(x))
        {
            set(x);
            processed[n_processed++] = x;
        }
    }

    for (int i = 0; i < n_processed; i++)
        printf("%d ", processed[i]);
    printf("\n");

    free(processed);
    return 0;
}
