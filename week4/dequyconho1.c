#include <stdio.h>
#include <string.h>
#include <time.h>
#define N 100

int m[N];
int fib(int n)
{
    if (n <= 1)
        m[n] = 1;
    else
    {
        if (m[n] == 0)
            m[n] = fib(n - 1) + fib(n - 2);
    }
    return m[n];
}
void init()
{
    memset(m, 0, sizeof(int) * N);
}

int fib2(int n)
{
    if (n <= 1)
        return 1;
    return fib2(n - 1) + fib2(n - 2);
}

int main()
{
    init();
    clock_t start1, start2, end1, end2;
    start1 = clock();
    for (int i = 0; i < 20; i++)
        printf("fib[%d] = %d\n", i, fib(i));
    end1 = clock();
    double time_spent_fib = (double)(end1 - start1) / CLOCKS_PER_SEC;
    printf("\nTime spent fib: %f\n", time_spent_fib);

    start2 = clock();
    for (int i = 0; i < 20; i++)
        printf("fib[%d] = %d\n", i, fib2(i));
    end2 = clock();
    double time_spent_fib2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("\nTime spent fib2: %f", time_spent_fib2);
}