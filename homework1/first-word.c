#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Wrong!!\nSYNTAX: .\\first-word.exe <link file>");
        return 1;
    }
    FILE *f;
    f = fopen(argv[1], "a+");

    char firstWord[100];
    char buff[100];
    int index = -1;
    while ((fgets(buff, 100, f)) != NULL)
    {
        index++;
        firstWord[index] = buff[0];
    }
    fputc('\n', f);
    for (int i = 0; i <= index; ++i)
    {
        fputc(firstWord[i], f);
        fputc(' ', f);
    }
    return 0;
}