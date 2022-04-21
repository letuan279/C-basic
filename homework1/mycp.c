#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Wrong input!!\nSYNTAX: ./apd.exe <file name 1> <file name 2>");
    }
    FILE *f1, *f2;
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "w");
    char c = '\0';
    while (c != EOF)
    {
        c = fgetc(f1);
        if (c != EOF)
            fputc(c, f2);
    }
    fclose(f1);
    fclose(f2);
    return 0;
}