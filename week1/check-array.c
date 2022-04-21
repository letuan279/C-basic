#include <stdio.h>
#define SIZE 5

int checkArray(int arr1[], int arr2[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        if (arr1[i] != arr2[i])
            return 0;
    }
    return 1;
}

int main()
{
    int input1[SIZE], input2[SIZE], i;

    printf("Hay nhap mot danh sach co %d so nguyen:\n", SIZE);
    for (i = 0; i < SIZE; ++i)
        scanf("%d", &input1[i]);

    printf("Nhap mot danh sach khac co %d so nguyen:\n", SIZE);
    for (i = 0; i < SIZE; ++i)
        scanf("%d", &input2[i]);

    if (checkArray(input1, input2, SIZE) == 1)
        printf("Hai mang trung nhau\n");
    else
        printf("Hai mang khac nhau\n");

    return 0;
}