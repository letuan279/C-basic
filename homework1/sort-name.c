#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct sinhvien
{
    char fullName[100];
    char lastName[100];
} SV;
SV sv[100];

int pos(char *fullname)
{
    int i = strlen(fullname) - 1;
    while (fullname[i] != ' ')
    {
        i--;
    }
    return i + 1;
}

int main()
{
    int sl;
    char name[100][100];
    printf("Nhap so luong sinh vien trong lop hoc: ");
    scanf("%d", &sl);
    for (int i = 0; i < sl; ++i)
    {
        printf("\nNhap ten sinh vien thu %d: ", i + 1);
        fflush(stdin);
        gets(name[i]);
    }

    for (int i = 0; i < sl; ++i)
    {
        strcpy(sv[i].fullName, name[i]);
        strcpy(sv[i].lastName, &name[i][pos(name[i])]);
    }

    for (int i = 0; i < sl - 1; ++i)
    {
        for (int j = i + 1; j < sl; ++j)
        {
            if (strcmp(sv[i].lastName, sv[j].lastName) > 0)
            {
                SV tmp = sv[i];
                sv[i] = sv[j];
                sv[j] = tmp;
            }
        }
    }
    for (int i = 0; i < sl; ++i)
    {
        printf("\n%s", sv[i].fullName);
    }

    int max = 0;
    char tensvmax[100];
    for (int i = 0; i < sl - 1; ++i)
    {
        int count = 1;
        for (int j = i + 1; j < sl; ++j)
        {
            if (strcmp(sv[i].lastName, sv[j].lastName) == 0)
            {
                count++;
            }
        }
        if (count > max)
        {
            max = count;
            strcpy(tensvmax, sv[i].lastName);
        }
    }

    printf("\nSo luong lon nhat cac sinh vien cung ten: %s %d", tensvmax, max);

    return 0;
}
