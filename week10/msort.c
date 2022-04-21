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

int partition(phoneaddress *arr, int low, int high)
{
    phoneaddress pivot = arr[high]; // pivot
    int i = (low - 1);              // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (strcmp(arr[j].email, pivot.email) < 0)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(phoneaddress *arr, int low, int high)
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

int main()
{
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

    quick_sort(phonearr, 0, n - 1);

    // Output
    printf("\n----------------------------------\n");
    FILE *fout = fopen("outputEx1.dat", "w+b");
    fwrite(phonearr, sizeof(phoneaddress), n, fout);
    for (int i = 0; i < n; i++)
    {
        printf("Name: %-15s Tel: %-20s Email: %-10s\n", phonearr[i].name, phonearr[i].tel, phonearr[i].email);
    }

    fclose(fp);
    fclose(fout);
    return 0;
}