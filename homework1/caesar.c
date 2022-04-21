#include <stdio.h>
#include <stdlib.h>

char change(char input, int offset)
{
    char result;
    if (input >= 'a' && input <= 'z')
    {
        result = (input + offset - 'a') % 26 + 'a';
    }
    else if (input >= 'A' && input <= 'Z')
    {
        result = (input + offset - 'A') % 26 + 'A';
    }
    return result;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Wrong!!\nSYNTAX: ./caesar <file 1> <offset> <file 2>");
        return 1;
    }
    FILE *f1, *f2;
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[3], "w");
    char c = '\0';
    c = fgetc(f1);
    while (c != EOF)
    {
        fputc(change(c, atoi(argv[2])), f2);
        c = fgetc(f1);
    }
    return 0;
}