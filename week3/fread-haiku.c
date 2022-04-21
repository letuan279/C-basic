#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 80
int main()
{
    int num;
    FILE *fptr2;
    char filename2[] = "haiku.txt";
    char buff[MAX_LEN + 1];
    if ((fptr2 = fopen(filename2, "r")) == NULL)
    {
        printf("Cannot open %s.\n", filename2);
        return 1;
    }
    num = fread(buff, sizeof(char), MAX_LEN, fptr2);
    buff[num * sizeof(char)] = '\0';
    printf("%s", buff);
}