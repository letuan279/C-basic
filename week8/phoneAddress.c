#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct phoneaddress_t
{
    char name[20];
    char tel[11];
    char email[25];
} phoneaddress;

int main()
{
    FILE *fp;
    phoneaddress phonearr[MAX];
    int i, n, irc;
    printf("How many contacts do you want to enter (<30)?");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("name:");
        scanf("%s", phonearr[i].name);
        printf("tel:");
        scanf("%s", phonearr[i].tel);
        printf("email:");
        scanf("%s", phonearr[i].email);
    }
    if ((fp = fopen("phonebook.dat", "w+b")) == NULL)
    {
        printf("Can not open %s.\n", "phonebook.dat");
        return 1;
    }

    irc = fwrite(phonearr, sizeof(phoneaddress), n, fp);

    if ((fp = fopen("phonebook.dat", "rb")) == NULL)
    {
        printf("Can not open %s.\n", "phonebook.dat");
        return 1;
    }

    irc = fread(phonearr, sizeof(phoneaddress), n, fp);

    for (int i = 0; i < n; i++)
    {
        printf("%s-", phonearr[i].name);
        printf("%s-", phonearr[i].tel);
        printf("%s\n", phonearr[i].email);
    }
    fclose(fp);
    return 0;
}