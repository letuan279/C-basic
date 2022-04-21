#include <stdio.h>
#define MAX_LEN 100

int LineReadWrite(FILE *fin)
{
    int count = 0;
    char buff[MAX_LEN];
    while (fgets(buff, MAX_LEN, fin) != NULL)
    {
        printf("%s", buff);
        count++;
    }
    return count;
}
int main(void)
{
    FILE *fptr1;
    char filename[] = "haiku.txt";

    if ((fptr1 = fopen(filename, "r")) == NULL)
    {
        printf("Cannot open %s.\n", filename);
        return 1;
    }
    else
    {
        printf("Reading file % s... done !\n", filename);
        printf("\nThe file has % d lines.", LineReadWrite(fptr1));
        fclose(fptr1);
    }
    return 0;
}