#include <stdio.h>

int sum(int n)
{
    if (n <= 1)
        return 1;
    int s = sum(n - 1);
    return n + s;
}

int C(int k, int n)
{
    if (k == 0 || k == n)
        return 1;
    int C1 = C(k - 1, n - 1);
    int C2 = C(k, n - 1);
    return C1 + C2;
}

int main()
{
    printf("\nsum(5) = %d", sum(5));
    printf("\nC(2,7) = %d", C(2, 7));
}