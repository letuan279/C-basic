#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX 100

int n = 5;
int a[MAX];

void printSolution()
{
    for (int i = 1; i <= n; ++i)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int UCV(int i, int k)
{
    for (int j = 1; j < k; ++j)
    {
        if (i == a[j])
            return 0;
        if (abs(i - a[j]) == abs(k - j))
            return 0;
    }
    return 1;
}

void try(int k)
{
    for (int i = 1; i <= n; ++i)
    {
        if (UCV(i, k) == 1)
        {
            a[k] = i;
            if (k == n)
                printSolution();
            else
                try(k + 1);
        }
    }
}

int main()
{
    memset(a, -1, sizeof(int));
    try(1);
}