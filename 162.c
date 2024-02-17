#include <stdio.h>

int main()
{
    char isbn[10];
    scanf("%c-%c%c%c-%c%c%c%c%c-%c", isbn, isbn + 1, isbn + 2, isbn + 3,
          isbn + 4, isbn + 5, isbn + 6, isbn + 7, isbn + 8, isbn + 9);
    int check_sum = 0;
    char expected_check_char;
    for (int i = 0; i < 9; i++)
        check_sum += (isbn[i] - '0') * (i + 1);
    check_sum %= 11;
    if (check_sum == 10)
        expected_check_char = 'X';
    else
        expected_check_char = '0' + check_sum;
    if (expected_check_char == isbn[9])
        printf("Right");
    else
        printf("%c-%c%c%c-%c%c%c%c%c-%c", isbn[0], isbn[1], isbn[2],
               isbn[3], isbn[4], isbn[5], isbn[6], isbn[7], isbn[8], expected_check_char);
    return 0;
}
