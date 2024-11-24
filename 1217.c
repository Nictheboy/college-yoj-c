#include <stdio.h>

int last[300], current[300], cursor, merged;

int main()
{
    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int status;
            scanf("%d", &status);
            if (status)
            {
                if (j - 1 >= 0 && current[j - 1] && last[j])
                {
                    if (current[j - 1] == last[j])
                        current[j] = current[j - 1];
                    else
                    {
                        ++merged;
                        int to_merge = last[j];
                        for (int k = 0; k < n; k++)
                            if (last[k] == to_merge)
                                last[k] = current[j - 1];
                        for (int k = 0; k < n; k++)
                            if (current[k] == to_merge)
                                current[k] = current[j - 1];
                        current[j] = current[j - 1];
                    }
                }
                else if (j - 1 >= 0 && current[j - 1])
                    current[j] = current[j - 1];
                else if (last[j])
                    current[j] = last[j];
                else
                    current[j] = ++cursor;
            }
            else
                current[j] = 0;
        }
        for (int j = 0; j < n; j++)
            last[j] = current[j];
    }
    printf("%d\n", cursor - merged);
    return 0;
}
