#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>

#define VERY_BIG_NUMBER (INT_MAX / 2)

int n;
bool *map; // n*n
int X[3], Y[3];
bool *calculating; // n*n

bool out_of_range(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= n;
}

int min(int d1, int d2, int d3, int d4)
{
    if (d1 <= d2 && d1 <= d3 && d1 <= d4)
        return d1;
    if (d2 <= d3 && d2 <= d4)
        return d2;
    if (d3 <= d4)
        return d3;
    return d4;
}

int *_dist1_cache_value = NULL;
bool *_dist1_cached = NULL;
int *_dist2_cache_value = NULL;
bool *_dist2_cached = NULL;
void _ensure_caches_inited()
{
    if (!_dist1_cache_value)
    {
        _dist1_cache_value = (int *)calloc(n * n, sizeof(int));
        _dist1_cached = (bool *)calloc(n * n, sizeof(bool));
        for (int i = 0; i < n * n; i++)
            _dist1_cached[i] = false;
    }
    if (!_dist2_cache_value)
    {
        _dist2_cache_value = (int *)calloc(n * n, sizeof(int));
        _dist2_cached = (bool *)calloc(n * n, sizeof(bool));
        for (int i = 0; i < n * n; i++)
            _dist2_cached[i] = false;
    }
}

// Returns: dist((x, y), (X[1], Y[1]))
// @Cacheable
int dist1(int x, int y)
{
    if (out_of_range(x, y) || !map[x * n + y] || calculating[x * n + y])
        return VERY_BIG_NUMBER;
    if (x == X[1] && y == Y[1])
        return 0;

    _ensure_caches_inited();
    if (!_dist1_cached[x * n + y])
    {
        //printf("dist1(%d, %d)\n", x, y);
        calculating[x * n + y] = true;
        int d1 = dist1(x - 1, y);
        int d2 = dist1(x + 1, y);
        int d3 = dist1(x, y - 1);
        int d4 = dist1(x, y + 1);
        _dist1_cache_value[x * n + y] = 1 + min(d1, d2, d3, d4);
        calculating[x * n + y] = false;
        //_dist1_cached[x * n + y] = true;
        //printf("dist1(%d, %d) = %d\n", x, y, _dist1_cache_value[x * n + y]);
    }
    return _dist1_cache_value[x * n + y];
}
// Returns: dist((x, y), (X[2], Y[2]))
// @Cacheable
int dist2(int x, int y)
{
    if (out_of_range(x, y) || !map[x * n + y] || calculating[x * n + y])
        return VERY_BIG_NUMBER;
    if (x == X[2] && y == Y[2])
        return 0;

    _ensure_caches_inited();
    if (!_dist2_cached[x * n + y])
    {
        calculating[x * n + y] = true;
        int d1 = dist2(x - 1, y);
        int d2 = dist2(x + 1, y);
        int d3 = dist2(x, y - 1);
        int d4 = dist2(x, y + 1);
        _dist2_cache_value[x * n + y] = 1 + min(d1, d2, d3, d4);
        calculating[x * n + y] = false;
        //_dist2_cached[x * n + y] = true;
    }
    return _dist2_cache_value[x * n + y];
}

int main()
{
    scanf("%d", &n);
    map = (bool *)calloc(n * n, sizeof(bool));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int temp;
            scanf("%d", &temp);
            switch (temp)
            {
            case 0:
                map[i * n + j] = true;
                break;
            case 1:
                map[i * n + j] = false;
                break;
            case 2:
                map[i * n + j] = true;
                X[0] = i;
                Y[0] = j;
                break;
            case 3:
                map[i * n + j] = true;
                X[1] = i;
                Y[1] = j;
                break;
            case 4:
                map[i * n + j] = true;
                X[2] = i;
                Y[2] = j;
                break;
            }
        }
    }
    calculating = (bool *)calloc(n * n, sizeof(bool));
    for (int i = 0; i < n * n; i++)
        calculating[i] = false;
    //printf("dist1(X[0], Y[0]) = %d\n", dist1(X[0], Y[0]));
    //printf("dist2(X[1], Y[1]) = %d\n", dist2(X[1], Y[1]));
    printf("%d", dist1(X[0], Y[0]) + dist2(X[1], Y[1]));
    return 0;
}
