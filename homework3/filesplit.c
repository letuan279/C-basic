#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 100

typedef struct phoneaddress_t
{
    char name[20];
    char tel[11];
    char email[25];
} phoneaddress;

int getLine(FILE *f)
{
    phoneaddress *phone = (phoneaddress *)malloc(MAX_LEN * sizeof(phoneaddress));
    int num = fread(phone, sizeof(phoneaddress), MAX_LEN, f);
    rewind(f);
    free(phone);
    return num;
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("\nInvalid arguments");
        return 1;
    }
    FILE *f, *f1, *f2;
    if ((f = fopen(argv[1], "rb")) == NULL)
    {
        printf("\nError");
    }
    if ((f1 = fopen(argv[3], "w+b")) == NULL)
    {
        printf("\nError");
    }
    if ((f2 = fopen(argv[4], "w+b")) == NULL)
    {
        printf("\nError");
    }

    int pos = atoi(argv[2]);
    int size = getLine(f);
    phoneaddress *phone = (phoneaddress *)malloc(size * sizeof(phoneaddress));
    if (phone == NULL)
    {
        printf("\nAllocation failed! Check memory");
        return 1;
    }
    if (pos >= size)
    {
        int num = fread(phone, sizeof(phoneaddress), MAX_LEN, f);
        fwrite(phone, sizeof(phoneaddress), num, f1);
    }
    else if (pos <= 0)
    {
        int num = fread(phone, sizeof(phoneaddress), MAX_LEN, f);
        fwrite(phone, sizeof(phoneaddress), num, f2);
    }
    else
    {
        int num = fread(phone, sizeof(phoneaddress), pos, f);
        fwrite(phone, sizeof(phoneaddress), num, f1);
        int num2 = fread(&phone[pos], sizeof(phoneaddress), MAX_LEN, f);
        fwrite(&phone[pos], sizeof(phoneaddress), num2, f2);
    }
    free(phone);
    return 0;
}