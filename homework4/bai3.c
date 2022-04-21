#include <stdio.h>

int x[6] = {-1, -1, -1, -1, -1, -1};
int n = 6;
int count = 0;

void printSolution()
{
    for (int k = 0; k < n; k++)
        printf("% d", x[k]);
    printf("\n");
    count++;
}

int ucv(int v, int k)
{
    if (k >= 2)
    {
        if (v == 1 && x[k - 1] == 1 && x[k - 2] == 1)
            return 0;
    }
    return 1;
}

int TRY(int k)
{
    for (int v = 0; v <= 1; v++)
    {
        if (ucv(v, k) == 1)
        {
            x[k] = v;
            if (k == n - 1)
                printSolution();
            else
                TRY(k + 1);
        }
    }
}

int S(int n)
{
    if (n == 1)
        return 2;
    if (n == 2)
        return 4;
    if (n == 3)
        return 7;
    return S(n - 1) + S(n - 2) + S(n - 3);
}

int main()
{
    TRY(0);
    printf("\nCount = %d", count);
    printf("\nCount Toan roi rac = %d", S(n));
}