#include <stdio.h>

int main()
{
    int arr[10] = {5, 2, 52, 23, 34, 67, 23, 78, 23, 65};
    int arr1[10] = {23, 34, 6, 34, 56, 34, 5, 7, 7, 34};
    int arr2[20];
    for (int i = 0; i < 20; i++)
    {
        if(i<10){
            arr2[i] = arr[i];
        }
        else{
            arr2[i] = arr1[i - 10];
        }
    }
    for (int i = 0; i < 20; i++)
    {
        printf("%d ", arr2[i]);
    }
    printf("\n");
    return 0;
}