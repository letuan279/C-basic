#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 300

int main()
{
    // txt -> dat
    FILE *f, *fdat;
    if ((f = fopen("vnedict.txt", "r")) == NULL)
    {
        printf("\nERROR");
        return 1;
    }
    if ((fdat = fopen("vnedict.dat", "w+b")) == NULL)
    {
        printf("\nERROR");
        return 1;
    }
    char buff[MAX_LEN];
    while ((fgets(buff, MAX_LEN, f)) != NULL)
    {
        buff[strlen(buff)] = '\0';
        fwrite(buff, sizeof(char), MAX_LEN, fdat);
    }
    rewind(fdat);

    // print BD
    int start, end;
    printf("\nStart at: ");
    scanf("%d", &start);
    printf("\nEnd at: ");
    scanf("%d", &end);
    for (int i = 0; i < start - 1; ++i)
    {
        char buff2[MAX_LEN];
        fread(buff2, sizeof(char), MAX_LEN, fdat);
    }
    for (int i = start - 1; i < end; i++)
    {
        char buff3[MAX_LEN];
        fread(buff3, sizeof(char), MAX_LEN, fdat);
        printf("\n%s", buff3);
    }
    fclose(f);
    fclose(fdat);
    return 0;
}