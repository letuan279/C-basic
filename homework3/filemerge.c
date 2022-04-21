#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100

typedef struct phoneaddress_t
{
    char name[20];
    char tel[11];
    char email[25];
} phoneaddress;

int getLine(FILE *f)
{
    phoneaddress *phone = (phoneaddress *)malloc(MAX_ELEMENT * sizeof(phoneaddress));
    int num = fread(phone, sizeof(phoneaddress), MAX_ELEMENT, f);
    rewind(f);
    free(phone);
    return num;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("\nInvalid arguments");
        return 1;
    }
    FILE *f1, *f2, *f;
    if ((f1 = fopen(argv[1], "rb")) == NULL)
    {
        printf("\nError");
    }
    if ((f2 = fopen(argv[2], "rb")) == NULL)
    {
        printf("\nError");
    }
    if ((f = fopen(argv[3], "w+b")) == NULL)
    {
        printf("\nError");
    }

    int size1 = getLine(f1);
    int size2 = getLine(f2);
    phoneaddress *phone = (phoneaddress *)malloc((size1 + size2) * sizeof(phoneaddress));
    if (phone == NULL)
    {
        printf("\nAllocation failed! Check memory");
        return 1;
    }
    fread(phone, sizeof(phoneaddress), size1, f1);
    fread(&phone[size1], sizeof(phoneaddress), size2, f2);
    fwrite(phone, sizeof(phoneaddress), size1 + size2, f);

    free(phone);
    return 0;
}