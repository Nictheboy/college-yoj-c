#include <stdio.h>
#include <string.h>

int to_int(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else
        return c - 'A' + 10;
}

char to_char(int x)
{
    if (x >= 0 && x <= 9)
        return x + '0';
    else
        return x + 'A' - 10;
}

int main()
{
    char input[33], output[33], reversed_output[33];
    int n, m, n_output = 0;
    scanf("%d\n%s\n%d", &n, input, &m);
    int value = 0;
    for (int i = 0; i < strlen(input); i++)
        value = value * n + to_int(input[i]);
    while (value)
    {
        output[n_output++] = to_char(value % m);
        value /= m;
    }
    for (int i = 0; i < n_output; i++)
        reversed_output[i] = output[n_output - 1 - i];
    reversed_output[n_output] = '\0';
    printf("%s\n", reversed_output);
    return 0;
}
