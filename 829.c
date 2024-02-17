#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX(A, B) (((A) > (B)) ? (A) : (B))

typedef struct
{
    int cnt;
    int size;
    const char *type;
} info;

int main()
{
    info infos[18] = {
        {0, 16, "long double"},
        {0, 8, "long double *"},
        {0, 8, "long long *"},
        {0, 8, "double *"},
        {0, 8, "long *"},
        {0, 8, "float *"},
        {0, 8, "int *"},
        {0, 8, "short *"},
        {0, 8, "bool *"},
        {0, 8, "char *"},
        {0, 8, "long long"},
        {0, 8, "double"},
        {0, 4, "long"},
        {0, 4, "float"},
        {0, 4, "int"},
        {0, 2, "short"},
        {0, 1, "bool"},
        {0, 1, "char"},
    };

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        char input[25];
        int cnt;
        getchar();
        scanf("%[^\n]", input);
        int len = strlen(input);
        while (!isblank(input[len - 1]))
            ungetc(input[--len], stdin);
        input[--len] = '\0';
        scanf("%d", &cnt);
        for (int j = 0; j < 18; j++)
            if (strcmp(infos[j].type, input) == 0)
            {
                infos[j].cnt += cnt;
                break;
            }
    }

    int size_max = 1;
    for (int i = 0; i < 18; i++)
        if (infos[i].cnt > 0)
            size_max = MAX(size_max, infos[i].size);

    int size_cnt = 0;
    for (int i = 0; i < 18; i++)
        size_cnt += infos[i].cnt * infos[i].size;

    printf("%d\n", (size_cnt % size_max == 0) ? size_cnt : size_max * (size_cnt / size_max + 1));
    for (int i = 0; i < 18; i++)
        if (infos[i].cnt > 0)
            printf("%s %d\n", infos[i].type, infos[i].cnt);

    return 0;
}
