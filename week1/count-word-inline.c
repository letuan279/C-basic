#include <stdio.h>
#include <string.h>
#define MAX_LEN 100

void LineReadWrite(FILE *fin, FILE *fout)
{
    char buff[MAX_LEN];
    int count;
    while (fgets(buff, MAX_LEN, fin) != NULL)
    {
        count = strlen(buff) - 1;
        fprintf(fout, "%d %s", count, buff);
    }
}

int main()
{
    FILE *f1, *f2;
    f1 = fopen("count-word-inline1.txt", "r");
    f2 = fopen("count-word-inline2.txt", "w");
    LineReadWrite(f1, f2);
    fclose(f1);
    fclose(f2);
}
