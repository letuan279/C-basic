#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int *createRandom(int n)
{
    srand(time(NULL));
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i)
    {
        arr[i] = rand() % 1000 + 1;
    }
    return arr;
}

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

int partition(int *arr, int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1);     // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(int *arr, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void insertion_sort(int *arr, int n)
{
    int i, j;
    int next;
    for (i = 1; i < n; i++)
    {
        next = arr[i];
        for (j = i - 1; j >= 0 && next < arr[j]; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = next;
    }
}

int main()
{
    int n = 1;
    while (n)
    {
        printf("\nEnter n(0 to exit): ");
        scanf("%d", &n);
        if (!n)
            return 0;
        int *randArray1 = createRandom(n);
        clock_t start_quick = clock();
        quick_sort(randArray1, 0, n - 1);
        clock_t end_quick = clock();
        float time_quick = (float)(end_quick - start_quick) / CLOCKS_PER_SEC;
        free(randArray1);

        int *randArray2 = createRandom(n);
        clock_t start_insert = clock();
        insertion_sort(randArray2, n);
        clock_t end_insert = clock();
        float time_insert = (float)(end_insert - start_insert) / CLOCKS_PER_SEC;
        free(randArray2);

        printf("\nRuntime Quick sort with n = %d: %.3f (s)", n, time_quick);
        printf("\nRuntime Insertion sort with n = %d: %.3f (s)\n", n, time_insert);
    }
}