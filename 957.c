#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>

typedef unsigned uint32;

typedef struct
{
    char *data;
} BitMap;

BitMap *BitMap_Init(uint32 capacity)
{
    BitMap *this = malloc(sizeof(BitMap));
    size_t size = (capacity >> 3) + 1;
    this->data = malloc(size);
    memset(this->data, 0x00, size);
    return this;
}

void BitMap_Destroy(BitMap *this)
{
    free(this->data);
    free(this);
}

void BitMap_Set(BitMap *this, uint32 address, bool value)
{
    uint32 base = address >> 3;
    int offset = address & 0x07;
    this->data[base] &= ~(1 << offset);
    this->data[base] |= !!value << offset;
}

bool BitMap_Read(BitMap *this, uint32 address)
{
    uint32 base = address >> 3;
    int offset = address & 0x07;
    return this->data[base] & (1 << offset);
}

int main()
{
    BitMap *map = BitMap_Init(0x10000000);
    int a, b, p, q;
    scanf("%d%d%d%d", &a, &b, &p, &q);
    BitMap_Set(map, a, true);
    BitMap_Set(map, b, true);
    BitMap_Set(map, p, false);
    bool result = BitMap_Read(map, q);
    printf("%d\n", !!result);
    BitMap_Destroy(map);
}
