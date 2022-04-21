#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Wrong!!\nSYNTAX: ./unconvert.exe <file name>");
        return 1;
    }
    FILE *f1, *f2;
    f1 = fopen(argv[1], "r");
    f2 = fopen("tmp.txt", "w");

    char c = '\0';
    while (c != EOF)
    {
        c = fgetc(f1);
        if (c != EOF)
        {
            if (c >= 'a' && c <= 'z')
            {
                c -= 32;
                fputc(c, f2);
            }
            else
                fputc(c, f2);
        }
    }

    fclose(f1);
    fclose(f2);

    FILE *ptr1, *ptr2;
    ptr1 = fopen(argv[1], "w");
    ptr2 = fopen("tmp.txt", "r");

    char h = '\0';
    while (h != EOF)
    {
        h = fgetc(ptr2);
        if (h != EOF)
            fputc(h, ptr1);
    }
    fclose(ptr1);
    fclose(ptr2);
}