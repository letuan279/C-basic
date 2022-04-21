#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *f;
    int *p;
    int i, n, value, sum;

    printf("Enter a list of numbers with the first is the size of list: \n");
    scanf("%d", &n);
    p = (int *)malloc(n * sizeof(int));
    i = 0;
    sum = 0;
    while (i < n)
    {
        scanf("%d", &value);
        p[i++] = value;
        sum += value;
    }

    if ((f = fopen("out.txt", "w")) == NULL)
    {
        printf("Can not open %s.\n", "out.txt");
        return 1;
    }
    for (i = n - 1; i >= 0; i--)
    {
        fprintf(f, "%d ", p[i]);
    }
    fprintf(f, "%d ", sum);
    fclose(f);
    free(p);
}