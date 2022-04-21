#include <stdio.h>
#define MAX_LEN 100

void LineReadWrite(FILE *fin)
{
    char buff[MAX_LEN];
    int index = 1;
    while (fgets(buff, MAX_LEN, fin) != NULL)
    {
        printf("%d ", index);
        index++;
        printf("%s", buff);
    }
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
        LineReadWrite(fptr1);
    }
    return 0;
}