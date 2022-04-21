#include <stdio.h>
#include <string.h>
#define MAX 100

int x[MAX];
int n = 6;
int count = 0;
void printSolution()
{
    for (int k = 0; k < n; k++)
        printf("% d", x[k]);
    printf("\n");
    count++;
}
int TRY(int k)
{
    for (int v = 0; v <= 1; v++)
    {
        x[k] = v;
        if (k == n - 1)
            printSolution();
        else
            TRY(k + 1);
    }
}
int main()
{
    memset(x, -1, sizeof(int));
    TRY(0);
    printf("\nKet qua: %d", count);
}