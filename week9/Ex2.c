#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct phoneaddress_t
{
    char name[20];
    char tel[11];
    char email[25];
} phoneaddress;

void swap(phoneaddress *a, phoneaddress *b)
{
    phoneaddress c = *a;
    *a = *b;
    *b = c;
}

int count_heap = 0;

void adjust(phoneaddress *arr, int n, int i)
{
    count_heap++;
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && strcmp(arr[l].email, arr[largest].email) > 0)
        largest = l;

    if (r < n && strcmp(arr[r].email, arr[largest].email) > 0)
        largest = r;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        adjust(arr, n, largest);
    }
}

void heap_sort(phoneaddress *arr, int n)
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
    // Input data
    FILE *fp;
    phoneaddress phonearr[MAX];
    int i, n;
    n = 10;
    if ((fp = fopen("phonebook.dat", "rb")) == NULL)
    {
        printf("Can not open %s.\n", "phonebook.dat");
        return 1;
    }
    fread(phonearr, sizeof(phoneaddress), n, fp);
    for (int i = 0; i < n; i++)
    {
        printf("Name: %-15s Tel: %-20s Email: %-10s\n", phonearr[i].name, phonearr[i].tel, phonearr[i].email);
    }

    // Heap sort
    heap_sort(phonearr, n);

    // Output
    printf("\n------------------------------------\n");
    FILE *fout = fopen("outputEx2.dat", "w+b");
    for (int i = 0; i < n; i++)
    {
        printf("Name: %-15s Tel: %-20s Email: %-10s\n", phonearr[i].name, phonearr[i].tel, phonearr[i].email);
    }
    fwrite(phonearr, sizeof(phoneaddress), n, fout);

    // Count
    printf("\ncount_heap = %d", count_heap);

    fclose(fp);
    fclose(fout);
}