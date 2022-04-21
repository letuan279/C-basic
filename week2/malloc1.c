#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, *p;
    printf("How many numbers do you want to enter?\n");
    scanf("%d", &n);
    p = (int *)malloc(n * sizeof(int));
    if (p == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }
    /* Nhập các số nguyên */
    for (int i = 0; i < n; ++i)
    {
        printf("\nEnter number %d: ", i + 1);
        scanf("%d", &p[i]);
    }

    /* Hiển thị chúng theo chiều ngược lại */
    printf("\nResult:");
    for (int i = n - 1; i >= 0; --i)
    {
        printf("%d ", p[i]);
    }

    free(p); /* Giải phóng bộ nhớ */
    return 0;
}