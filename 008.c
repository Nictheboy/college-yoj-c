#include <stdio.h>

int main()
{
    int score;
    int gpa10;
    scanf("%d", &score);
    if (score < 60) {
        printf("0");
        return 0;
    } else if (score <= 62)
        gpa10 = 10;
    else if (score <= 65)
        gpa10 = 13;
    else if (score <= 69)
        gpa10 = 17;
    else if (score <= 72)
        gpa10 = 20;
    else if (score <= 75)
        gpa10 = 23;
    else if (score <= 79)
        gpa10 = 27;
    else if (score <= 82)
        gpa10 = 30;
    else if (score <= 85)
        gpa10 = 33;
    else if (score <= 89)
        gpa10 = 37;
    else
        gpa10 = 40;
    printf("%d.%d\n", gpa10 / 10, gpa10 % 10);
}
