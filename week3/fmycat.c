#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 80

void BlockCat(FILE *fin)
{
    int num;
    char buff[MAX_LEN + 1];
    while (!feof(fin))
    {
        num = fread(buff, sizeof(char), MAX_LEN, fin);
        buff[num * sizeof(char)] = '\0';
        printf("%s", buff);
    }
}

int main(int argc, char *argv[])
{
    FILE *fptr1;
    if (argc != 2)
    {
        printf("The correct syntax should be: cat1 filename \n");
        return 1;
    }
    if ((fptr1 = fopen(argv[1], "r")) == NULL)
    {
        printf("Cannot open %s.\n", argv[1]);
        return 1;
    }
    else
    {
        BlockCat(fptr1);
        fclose(fptr1);
    }
    return 0;
}