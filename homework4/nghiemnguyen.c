#include <stdio.h>

int minOfArray(int A[], int size)
{
    int min = 1000000;
    for (int i = 1; i < size + 1; ++i)
    {
        min = (A[i] < min) ? A[i] : min;
    }
    return min;
}
int n = 2;
int A[3] = {-1, 1, 2};
int X[3] = {-1, -1, -1};
int VP = 5;
int count = 0;

void inketqua()
{
    for (int i = 1; i <= n; ++i)
    {
        printf("%d ", X[i]);
    }
    printf("\n");
    count++;
}

int ucv(int v, int k)
{
    int sum = 0;
    for (int i = 1; i < k; ++i)
    {
        sum += X[i];
    }
    if (sum + v * A[k] > VP)
        return 0;
    return 1;
}

int check()
{
    int VT = 0;
    for (int i = 1; i <= n; ++i)
    {
        VT += A[i] * X[i];
    }
    if (VP == VT)
        return 1;
    return 0;
}

void giaipt(int k)
{
    int max = VP / minOfArray(A, n) + 1;
    for (int v = 1; v < max; ++v)
    {
        if (ucv(v, k) == 1)
        {
            X[k] = v;
            if (k == n)
            {
                if (check() == 1)
                    inketqua();
            }
            else
                giaipt(k + 1);
        }
    }
}

int main()
{
    giaipt(1);
    printf("Count: %d", count);
}