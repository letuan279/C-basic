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

int count_insertion = 0;
int count_selection = 0;

void insertion_sort(phoneaddress list[], int n)
{
    int i, j;
    phoneaddress next;
    for (i = 1; i < n; i++)
    {
        next = list[i];
        for (j = i - 1; j >= 0 && strcmp(next.email, list[j].email) < 0; j--)
        {
            list[j + 1] = list[j];
            count_insertion++;
        }
        list[j + 1] = next;
    }
}

void selection_sort(phoneaddress a[], int n)
{
    int i, j, min;
    phoneaddress tmp;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j <= n - 1; j++)
        {
            count_selection++;
            if (strcmp(a[j].email, a[min].email) < 0)
                min = j;
        }
        tmp = a[i];
        a[i] = a[min];
        a[min] = tmp;
    }
}

int main()
{
    // insertion sort
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
    insertion_sort(phonearr, n);

    // selection sort
    FILE *fp2;
    phoneaddress phonearr2[MAX];
    if ((fp2 = fopen("phonebook.dat", "rb")) == NULL)
    {
        printf("Can not open %s.\n", "phonebook.dat");
        return 1;
    }

    fread(phonearr2, sizeof(phoneaddress), n, fp2);
    selection_sort(phonearr2, n);

    printf("\n------------------------------------\n");

    // Output
    FILE *fout = fopen("outputEx1.dat", "w+b");
    fwrite(phonearr2, sizeof(phoneaddress), n, fout);
    for (int i = 0; i < n; i++)
    {
        printf("Name: %-15s Tel: %-20s Email: %-10s\n", phonearr2[i].name, phonearr2[i].tel, phonearr2[i].email);
    }

    // Count
    printf("\ncount_insertion = %d", count_insertion);
    printf("\ncount_selection = %d", count_selection);

    fclose(fp);
    fclose(fp2);
    fclose(fout);
    return 0;
}