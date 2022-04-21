#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 80

void Copy_2(FILE *fin, FILE *fout)
{
    int num;
    char buff[MAX_LEN + 1];
    while (!feof(fin))
    {
        num = fread(buff, sizeof(char), MAX_LEN, fin);
        buff[num * sizeof(char)] = '\0';
        printf("%s", buff);
        fwrite(buff, sizeof(char), num, fout);
    }
}

int main(int argc, char *argv[])
{
    FILE *fptr1, *fptr2;
    if (argc != 3)
    {
        printf("The correct syntax should be: filecpy <file 1> <file 2> \n");
        return 1;
    }
    if ((fptr1 = fopen(argv[1], "r")) == NULL)
    {
        printf("Cannot open %s.\n", argv[1]);
        return 1;
    }
    else
    {
        fptr2 = fopen(argv[2], "w");
        Copy_2(fptr1, fptr2);
        fclose(fptr1);
        fclose(fptr2);
    }
    return 0;
}