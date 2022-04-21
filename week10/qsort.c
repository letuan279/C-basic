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

void merge(phoneaddress *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    phoneaddress L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (strcmp(L[i].email, R[j].email) <= 0)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(phoneaddress *arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        merge(arr, l, m, r);
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

    merge_sort(phonearr, 0, n - 1);

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