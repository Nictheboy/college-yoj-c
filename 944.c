#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int size;
    int *data;
} vector;

#define FOR(VEC, IDX) for (int IDX = 0; IDX < VEC.size; IDX++)

void delete(vector *this, int start, int n)
{
    int *data = this->data;
    int end = (this->size -= n);
    for (int i = start; i < end; i++)
    {
        data[i] = data[i + n];
    }
}

int main()
{
    vector vec;
    int k;
    scanf("%d %d", &vec.size, &k);
    vec.data = malloc(sizeof(int) * vec.size);
    FOR(vec, i)
    {
        scanf("%d", &vec.data[i]);
    }
    for (int i = 0; i < k; i++)
    {
        int lo, hi;
        scanf("%d %d", &lo, &hi);
        delete (&vec, lo, hi - lo);
    }
    FOR(vec, i)
    {
        printf("%d ", vec.data[i]);
    }
    return 0;
}
