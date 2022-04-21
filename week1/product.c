#include <stdio.h>
#define MAX_ELEMENT 10

typedef struct
{
    int no;
    char name[20];
    double price;
} product;

int main(void)
{
    FILE *f;
    product arr[MAX_ELEMENT];
    int i = 0;
    if ((f = fopen("product.txt", "r")) == NULL)
    {
        printf("Can not open %s.\n", "product.txt");
        return 1;
    }
    else
    {
        printf("%-6s%-24s%-6s\n", "NO", "NAME", "PRICE");
        while (fscanf(f, "%d%s%lf", &arr[i].no, arr[i].name, &arr[i].price) != EOF)
        {
            printf("%-6d%-24s%-6.2f\n", arr[i].no, arr[i].name, arr[i].price);
            i++;
        }
    }
    fclose(f);
    return 0;
}