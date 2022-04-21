#include <stdio.h>

void thaphanoi(int n, char A, char B, char C)
{
    if (n == 1)
    {
        printf("\nDi chuyen %c sang %c", A, B);
    }
    else
    {
        thaphanoi(n - 1, A, C, B);
        thaphanoi(1, A, B, C);
        thaphanoi(n - 1, C, B, A);
    }
}

int main()
{
    int n;
    printf("\nNhap n: ");
    scanf("%d", &n);
    thaphanoi(n, 'A', 'B', 'C');
}