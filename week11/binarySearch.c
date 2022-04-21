#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// random data
int *createData(int n)
{
    srand(time(NULL));
    int *myData = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
    {
        myData[i] = rand() % 1000 + 1;
    }
    return myData;
}

// bruteForceSolve

void bruteForceSolve(int *arr, int size, int Q)
{
    int count = 0;
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            if (arr[i] + arr[j] == Q)
                count++;
        }
    }
    printf("\nbruteForceSolve's result = %d\n", count);
}

// heap sort

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void adjust(int *arr, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        adjust(arr, n, largest);
    }
}

void heap_sort(int *arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        adjust(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        adjust(arr, i, 0);
    }
}

// binary search

int binarySearch(int *a, int l, int r, int target)
{
    int mid = (l + r) / 2;
    while (l < r)
    {
        if (target == a[mid])
            return 1;
        else if (target > a[mid])
        {
            l = mid + 1;
            mid = (l + r) / 2;
        }
        else
        {
            r = mid;
            mid = (l + r) / 2;
        }
    }

    return (target == a[mid]);
}

// binarySearchSolve

void binarySearchSolve(int *arr, int size, int Q)
{
    // Sort arr
    heap_sort(arr, size);

    // use binary search
    int count = 0;
    for (int i = 0; i < size - 1; ++i)
    {
        int ok = binarySearch(arr, i + 1, size - 1, Q - arr[i]);
        count += ok;
    }

    // print result
    printf("binarySearchSolve's result = %d\n", count);
}

int main()
{
    int n, Q;
    printf("\nEnter n = ");
    scanf("%d", &n);
    printf("\nEnter Q = ");
    scanf("%d", &Q);
    int *myArray = createData(n);
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", myArray[i]);
    }
    bruteForceSolve(myArray, n, Q);
    binarySearchSolve(myArray, n, Q);
    return 0;
}