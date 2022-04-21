#include <stdio.h>
#include <string.h>
#define MAX 100

int x[MAX];
int n = 5;
int count = 0;

void printSolution()
{
    for (int k = 0; k < n; k++)
        printf("% d", x[k]);
    printf("\n");
    count++;
}

int UCV(int v, int i)
{
    for (int j = 0; j < i; j++)
    {
        if (v == x[j])
            return 0;
    }
    return 1;
}

void TRY(int i)
{
    for (int v = 1; v <= n; v++)
    {
        if (UCV(v, i) == 1)
        {
            x[i] = v;
            if (i == n - 1)
                printSolution();
            else
                TRY(i + 1);
        }
    }
}

void main()
{
    memset(x, -1, MAX * sizeof(int));
    TRY(0);
    printf("So ket qua: %d", count);
}