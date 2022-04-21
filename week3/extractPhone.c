#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct phoneaddress
{
    char name[20];
    char tel[11];
    char email[25];
} phoneaddress;

int main(void)
{
    FILE *fp;
    phoneaddress *phonearr;
    int i, n, irc;
    printf("Read from 2sd data to 3rd data \n");
    if ((fp = fopen("phonebook.dat", "r+b")) == NULL)
    {
        printf("Can not open %s.\n", "phonebook.dat");
        return 1;
    }

    phonearr = (phoneaddress *)malloc(2 * sizeof(phoneaddress));
    if (phonearr == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }
    if (fseek(fp, 1 * sizeof(phoneaddress), SEEK_SET) != 0)
    {
        printf("Fseek failed!\n");
        return 1;
    }
    irc = fread(phonearr, sizeof(phoneaddress), 2, fp);
    for (i = 0; i < 2; i++)
    {
        printf("%s-", phonearr[i].name);
        printf("%s-", phonearr[i].tel);
        printf("%s\n", phonearr[i].email);
    }

    strcpy(phonearr[1].name, "Tuan");
    strcpy(phonearr[1].tel, "0389935193");
    strcpy(phonearr[1].email, "tuanla@hust.edu.vn");
    fseek(fp, 1 * sizeof(phoneaddress), SEEK_SET);
    irc = fwrite(phonearr, sizeof(phoneaddress), 2, fp);
    fclose(fp);
    free(phonearr);
    return 0;
}
