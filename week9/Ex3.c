// Sorting Algorithms Comparison

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define LEN 1000000

int *oneMillionElement = NULL;

int *createDataset()
{
    srand(time(NULL));
    int *myArray = (int *)malloc(sizeof(int) * LEN);
    if (myArray == NULL)
    {
        printf("\nCannot allocate memory");
        exit(0);
    }
    for (int i = 0; i < LEN; ++i)
    {
        myArray[i] = (rand() % LEN) + 1;
    }
    return myArray;
}

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void insertion_sort(int *list, int n)
{
    int i, j;
    int next;
    for (i = 1; i < n; i++)
    {
        next = list[i];
        for (j = i - 1; j >= 0 && next < list[j]; j--)
            list[j + 1] = list[j];
        list[j + 1] = next;
    }
}

void selection_sort(int *list, int n)
{
    int i, j, min, tmp;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j <= n - 1; j++)
            if (list[j] < list[min])
                min = j;
        swap(&list[i], &list[min]);
    }
}

void bubble_sort(int *list, int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (list[i] > list[j])
            {
                swap(&list[i], &list[j]);
            }
        }
    }
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

int main()
{
    int choice;
    while (1)
    {
        printf("\n1.Create Dataset\n2.Insertion sort\n3.Selection sort\n4.Bubble Sort\n5.Heap sort\n6.Exit");
        printf("\nChoose (1~6): ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:;
            oneMillionElement = createDataset();
            printf("\nCreated 1,000,000 integer values!!!");
            break;
        case 2:;
            clock_t start1, finish1;
            start1 = clock();
            insertion_sort(oneMillionElement, LEN);
            finish1 = clock();
            float timeRun1 = (float)(finish1 - start1) / CLOCKS_PER_SEC;
            printf("-->Running time: %.3f (s)\n", timeRun1);
            oneMillionElement = createDataset();
            break;
        case 3:;
            clock_t start2, finish2;
            start2 = clock();
            selection_sort(oneMillionElement, LEN);
            finish2 = clock();
            float timeRun2 = (float)(finish2 - start2) / CLOCKS_PER_SEC;
            printf("\n-->Running time: %.3f (s)\n", timeRun2);
            oneMillionElement = createDataset();
            break;
        case 4:;
            clock_t start3, finish3;
            start3 = clock();
            bubble_sort(oneMillionElement, LEN);
            finish3 = clock();
            float timeRun3 = (float)(finish3 - start3) / CLOCKS_PER_SEC;
            printf("\n-->Running time: %.3f (s)\n", timeRun3);
            oneMillionElement = createDataset();
            break;
        case 5:;
            clock_t start4, finish4;
            start4 = clock();
            heap_sort(oneMillionElement, LEN);
            finish4 = clock();
            float timeRun4 = (float)(finish4 - start4) / CLOCKS_PER_SEC;
            printf("\n-->Running time: %.3f (s)\n", timeRun4);
            oneMillionElement = createDataset();
            break;
        default:
            exit(0);
            break;
        }
    }
}