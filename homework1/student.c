#include <stdio.h>
#define MAX_ELEMENT 10

typedef struct
{
    int id;
    char mssv[20];
    char name[20];
    char sdt[20];
    int diem;
} student;

int main(void)
{
    FILE *f1, *f2;
    student st[MAX_ELEMENT];
    int i = 0;
    if ((f1 = fopen("student.txt", "r")) == NULL)
    {
        printf("Can not open %s.\n",
               "product.txt");
        return 1;
    }
    else
    {
        //doc file student.txt
        int i = 0;
        while (fscanf(f1, "%d%s%s%s", &st[i].id, st[i].mssv, st[i].name, &st[i].sdt) != EOF)
        {
            printf("%-6d%-24s%-24s%-24s\n", st[i].id, st[i].mssv, st[i].name, &st[i].sdt);
            i++;
        }

        //in ra banhdiem.txt
        f2 = fopen("bangdiem.txt", "w");
        fprintf(f2, "%-6s%-24s%-24s%-24s%-12s\n", "ID", "MSSV", "NAME", "SDT", "Diem");
        int sl = i;
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