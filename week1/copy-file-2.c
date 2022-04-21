#include <stdio.h>

void CharReadWrite(FILE *fin, FILE *fout)
{
    int c;
    while ((c = fgetc(fin)) != EOF)
    {
        if (c >= 'a' && c <= 'z')
        {
            c -= 32;
            fputc(c, fout);
        }
        else if (c >= 'A' && c <= 'Z')
        {
            c += 32;
            fputc(c, fout);
        }
        else
        {
            fputc(c, fout);
        }
    }
}

int main(void)
{
    FILE *fptr1, *fptr2;
    char filename1[] = "lab1w2.txt";
    char filename2[] = "lab1.txt";

    if ((fptr1 = fopen(filename1, "w")) == NULL)
    {
        printf("Cannot open %s.\n", filename1);
    }
    else if ((fptr2 = fopen(filename2, "r")) == NULL)
    {
        printf("Cannot open %s.\n", filename2);
    }
    else
    {
        CharReadWrite(fptr2, fptr1);
        fclose(fptr1);
        fclose(fptr2);
    }
    return 0;
}