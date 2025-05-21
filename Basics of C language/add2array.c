#include <stdio.h>

int main()
{
    int arr[10] = {5, 2, 52, 23, 34, 67, 23, 78, 23, 65};
    int arr1[10] = {23, 34, 6, 34, 56, 34, 5, 7, 7, 34};
    for (int i = 0; i < 10 - 1; i++)
    {
        arr[i] = arr[i] + arr1[i];
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}