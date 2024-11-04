#include <cstdio>
#include <cctype>

int main()
{
    int stack_height = 0;
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        switch (c)
        {
        case '(':
            ++stack_height;
            break;

        case ')':
            if (stack_height > 0)
                --stack_height;
            else
            {
                printf("NO\n");
                return 0;
            }
            break;

        default:
            break;
        }
    }
    if (stack_height > 0)
        printf("NO\n");
    else
        printf("YES\n");
    return 0;
}
