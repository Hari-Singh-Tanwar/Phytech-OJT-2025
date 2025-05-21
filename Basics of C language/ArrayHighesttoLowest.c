#include <stdio.h>

int main()
{
    int arr[10] = {5, 2, 52, 23, 34, 67, 23, 78, 23, 65};
    int swap;
    for (int i = 0; i < 10 -1; i++)
    {
        for (int j = 0; j < (10 - i-1); j++)
        {
            if (arr[j] < arr[j + 1])
            {
                swap = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = swap;
            }
        }
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}