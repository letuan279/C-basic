#include <stdio.h>
#define MAX_LEN 100

void LineReadWrite(FILE *fin, FILE *fout)
{
    char buff[MAX_LEN];
    while (fgets(buff, MAX_LEN, fin) != NULL)
    {
        fputs(buff, fout);
    }
}
int main(void)
{
    FILE *fptr1, *fptr2;
    char filename1[] = "lab1a.txt";
    char filename2[] = "lab1.txt";

    if ((fptr1 = fopen(filename1, "w")) == NULL)
    {
        printf("Cannot open %s.\n", filename1);
        return 1;
    }
    else if ((fptr2 = fopen(filename2, "r")) == NULL)
    {
        printf("Cannot open %s.\n", filename2);
        return 1;
    }
    else
    {
        LineReadWrite(fptr2, fptr1);
        fclose(fptr1);
        fclose(fptr2);
    }
    return 0;
}