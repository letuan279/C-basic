#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct phone_struct
{
    char model[30];
    int memory;
    float screenSize;
    long price;
} phone;

int getNumOfPhone(FILE *f);
void importDBFromText(FILE *fin, FILE *fout, int size);
void importAllFromDB(FILE *f, phone *p, int size);
void importPartFromDB(FILE *f, phone *p, int begin, int end);
void showBD(phone *p, int size);
void searchPhone(phone *p, int size);

int main()
{
    int choice;
    FILE *ftxt, *fdat;
    if ((ftxt = fopen("PhoneBD.txt", "r")) == NULL)
    {
        printf("cannot open PhoneBD.txt");
    }
    if ((fdat = fopen("PhoneBD.dat", "w+b")) == NULL)
    {
        printf("cannot open PhoneBD.dat");
    }
    int sl = getNumOfPhone(ftxt);
    phone *p = (phone *)malloc(sl * sizeof(phone));
    if (p == NULL)
    {
        printf("\nAllocation failed! Check memory");
        return 1;
    }
    for (;;)
    {
        printf("\n1. Import DB from text\n2. Import from DB\n3.Print All Database\n4.Search by phone by Phone Model\n5. Exit\nEnter(1~5):  ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            importDBFromText(ftxt, fdat, sl);
            break;
        case 2:
            printf("\n1. Import all\n2. Import a part\nEnter(1~2):  ");
            int import_choice;
            scanf("%d", &import_choice);
            if (import_choice == 1)
                importAllFromDB(fdat, p, sl);
            else
            {
                int begin, end;
                printf("\nStart at: ");
                scanf("%d", &begin);
                printf("\nEnd at: ");
                scanf("%d", &end);
                importPartFromDB(fdat, p, begin, end);
                sl = end - begin + 1;
            }
            break;
        case 3:
            showBD(p, sl);
            break;
        case 4:
            searchPhone(p, sl);
            break;

        default:
            free(p);
            return 1;
            break;
        }
    }
    free(p);
    return 0;
}

int getNumOfPhone(FILE *f)
{
    char buff[200];
    int count = 0;
    while ((fgets(buff, 200, f)) != NULL)
    {
        count++;
    }
    rewind(f);
    return count;
}

void importDBFromText(FILE *fin, FILE *fout, int size)
{
    rewind(fin);
    phone *p2 = (phone *)malloc(size * sizeof(phone));
    if (p2 == NULL)
    {
        printf("\nAllocation failed! Check memory");
    }
    for (int i = 0; i < size; ++i)
    {
        fscanf(fin, "%s %d %f %ld", p2[i].model, &p2[i].memory, &p2[i].screenSize, &p2[i].price);
        if (fwrite(&p2[i], sizeof(phone), 1, fout) != 1)
        {
            printf("\nError");
            exit(0);
        }
    }
    free(p2);
}

void importAllFromDB(FILE *f, phone *p, int size)
{
    rewind(f);
    for (int i = 0; i < size; ++i)
    {
        if (fread(&p[i], sizeof(phone), 1, f) != 1)
        {
            printf("\nError");
            exit(0);
        }
    }
}

void importPartFromDB(FILE *f, phone *p, int begin, int end)
{
    rewind(f);
    free(p);
    p = (phone *)malloc((end - begin + 1) * sizeof(phone));
    if (p == NULL)
    {
        printf("\nAllocation failed! Check memory");
    }
    fseek(f, (begin - 1) * sizeof(phone), SEEK_SET);
    for (int i = 0; i < end - begin + 1; ++i)
    {
        if (fread(&p[i], sizeof(phone), 1, f) != 1)
        {
            printf("\nError");
            exit(0);
        }
    }
}

void showBD(phone *p, int size)
{
    printf("\n%-30s%10s%15s%15s\n", "Model", "Memory", "Screen size", "Price");
    for (int i = 0; i < size; ++i)
    {
        printf("\n%-30s%10d%15.2f%15ld", p[i].model, p[i].memory, p[i].screenSize, p[i].price);
    }
}

void searchPhone(phone *p, int size)
{
    char phone_search[30];
    printf("\nEnter phone:");
    scanf("%s", phone_search);
    printf("\n%-30s%10s%15s%15s\n", "Model", "Memory", "Screen size", "Price");
    for (int i = 0; i < size; ++i)
    {
        if (strstr(p[i].model, phone_search) != NULL)
        {
            printf("\n%-30s%10d%15.2f%15ld", p[i].model, p[i].memory, p[i].screenSize, p[i].price);
        }
    }
}
