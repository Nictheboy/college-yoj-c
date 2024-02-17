#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int id;
    int score;
} info_t;

int cmp(const void *info1, const void *info2)
{
    int delta = ((info_t *)info2)->score - ((info_t *)info1)->score; // des
    if (delta != 0)
        return delta;
    else
        return ((info_t *)info1)->id - ((info_t *)info2)->id; // asc
}

int main()
{
    int n, m, wanted;
    info_t *info; // [n]

    scanf("%d %d", &n, &m);
    wanted = floor(1.5 * m);
    info = (info_t *)malloc(sizeof(info_t) * n);
    for (int i = 0; i < n; i++) {
        int id, score;
        scanf("%d %d", &id, &score);
        info[i].id = id;
        info[i].score = score;
    }

    qsort(info, n, sizeof(info_t), cmp);
    int score_line = info[wanted - 1].score;
    int actual = wanted;
    for (; info[actual + 1 - 1].score == score_line; actual++)
        ;
    printf("%d %d\n", score_line, actual);
    for (int i = 0; i < actual; i++)
        printf("%d %d\n", info[i].id, info[i].score);

    free(info);
}
