#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct phoneaddress_t
{
    char name[20];
    char tel[11];
    char email[25];
} phoneaddress;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("\nInvalid arguments");
        return 1;
    }
    FILE *fp;
    phoneaddress phonearr[MAX];
    if ((fp = fopen(argv[1], "rb")) == NULL)
    {
        printf("Can not open %s.\n", argv[1]);
        return 1;
    }

    int num = fread(phonearr, sizeof(phoneaddress), MAX, fp);

    for (int i = 0; i < num; i++)
    {
        printf("%-20s-", phonearr[i].name);
        printf("%-11s-", phonearr[i].tel);
        printf("%-15s\n", phonearr[i].email);
    }
    fclose(fp);
    return 0;
}