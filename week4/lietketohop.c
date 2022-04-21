#include <stdio.h>
#include <string.h>
#define MAX 100

int x[MAX];
int k = 3;
int n = 6;
int count = 0;

void printSolution()
{
    for (int i = 0; i < k; i++)
        printf("% d", x[i]);
    printf("\n");
    count++;
}

int UCV(int v, int i)
{
    if (v > x[i - 1])
        return 1;
    return 0;
}

int TRY(int i)
{
    for (int v = 1; v <= n; v++)
    {
        if (UCV(v, i) == 1)
        {
            x[i] = v;
            if (i == k - 1)
                printSolution();
            else
                TRY(i + 1);
        }
    }
}

int main()
{
    memset(x, -1, MAX * sizeof(int));
    TRY(0);
    printf("\nKet qua: %d", count);
}