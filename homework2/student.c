#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    char mssv[20];
    char name[20];
    char sdt[20];
    int diem;
} student;

int getNumOfLine(FILE *f)
{
    int count = 0;
    char buff[100];
    while (fgets(buff, 100, f) != NULL)
    {
        count++;
    }
    return count;
}

int main(void)
{
    FILE *f1, *f2;
    if ((f1 = fopen("student.txt", "r")) == NULL)
    {
        printf("Can not open %s.\n",
               "product.txt");
        return 1;
    }
    else
    {
        //tao mang dong
        int sl = getNumOfLine(f1);
        student *st = (student *)malloc(sl * sizeof(student));
        rewind(f1);
        //doc file student.txt
        int i = 0;
        while (fscanf(f1, "%d%s%s%s", &st[i].id, st[i].mssv, st[i].name, &st[i].sdt) != EOF)
        {
            printf("%-6d%-24s%-24s%-24s\n", st[i].id, st[i].mssv, st[i].name, &st[i].sdt);
            ++i;
        }

        //option them so luong sinh vien
        char option;
        printf("\nBan co muon them so luong sinh vien? (y/n)");
        scanf("%c", &option);
        if (option == 'y')
        {
            int more;
            printf("\nNhap so luong sinh vien can them:");
            scanf("%d", &more);
            st = (student *)realloc(st, (sl + more) * sizeof(student));
            for (int i = sl; i < sl + more; ++i)
            {
                printf("\nSV %d: ", i + 1);
                printf("\nNhap mssv :");
                fflush(stdin);
                gets(st[i].mssv);
                printf("\nNhap ten :");
                fflush(stdin);
                gets(st[i].name);
                printf("\nNhap sdt :");
                fflush(stdin);
                gets(st[i].sdt);
                st[i].id = i + 1;
            }
            sl += more;
        }
        else
            printf("\nBan da khong chon them sv!");

        //in ra banhdiem.txt
        printf("\n----------Nhap diem------------");
        f2 = fopen("bangdiem.txt", "w");
        fprintf(f2, "%-6s%-24s%-24s%-24s%-12s\n", "ID", "MSSV", "NAME", "SDT", "Diem");
        for (int i = 0; i < sl; ++i)
        {
            printf("\nNhap diem cho hoc sinh %d: ", st[i].id);
            scanf("%d", &st[i].diem);
            fprintf(f2, "%-6d%-24s%-24s%-24s%-12d\n", st[i].id, st[i].mssv, st[i].name, st[i].sdt, st[i].diem);
        }
    }
    fclose(f1);
    fclose(f2);
    return 0;
}