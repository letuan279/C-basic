#include <stdio.h>
#include <math.h>

int main(void)
{
    float A[10];

    printf("\nNhap 10 so:");
    for (int i = 0; i < 10; ++i)
    {
        scanf("%f", &A[i]);
    }

    printf("Hien thi chieu dao nguoc: \n");
    for (int i = 9; i >= 0; --i)
    {
        printf("%.1f ", A[i]);
    }

    float sum = 0, avg = 0, minOfDiff = 10000000;
    int pos;
    for (int i = 0; i < 10; ++i)
    {
        sum += A[i];
    }

    avg = sum / 10;

    for (int i = 0; i < 10; ++i)
    {
        float diff = fabs(A[i] - avg);
        if (diff < minOfDiff)
        {
            minOfDiff = diff;
            pos = i;
        }
    }

    printf("\nPhan tu co gia tri gan trung binh nhat:\nChi muc: %d\nGia trj: %.1f", pos, A[pos]);
}