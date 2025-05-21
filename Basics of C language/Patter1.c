#include <stdio.h>

int main()
{
    int num = 5;
    num = num * 2;
    for (int i = 0; i < num; i++)
    {
        if (i % 2 != 0)
        {
            for (int j = 0; j < num - i; j++)
            {
                printf(" ");
            }
            for (int j = 0; j < i; j++)
            {
                printf("%d ", j + 1);
            }
            printf("\n");
        }
    }
    for (int i = num - 2; i > 0; i--)
    {
        if (i % 2 != 0)
        {
            for (int j = 0; j < num - i; j++)
            {
                printf(" ");
            }
            for (int j = 0; j < i; j++)
            {
                printf("%d ", j + 1);
            }
            printf("\n");
        }
    }
    return 0;
}