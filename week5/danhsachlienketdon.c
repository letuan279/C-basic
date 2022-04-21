#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_LEN 50

typedef struct student
{
    char name[MAX_LEN];
    char email[MAX_LEN];
    struct student *next;
} student;
student *first, *last;

student *makeNode(char *name, char *email)
{
    student *node = (student *)malloc(sizeof(student));
    strcpy(node->name, name);
    strcpy(node->email, email);
    node->next = NULL;
    return node;
}

void initList()
{
    first = NULL;
    last = NULL;
}

int listEmpty()
{
    return first == NULL && last == NULL;
}

void insertLast(char *name, char *email)
{
    student *s = makeNode(name, email);
    if (listEmpty())
    {
        first = s;
        last = s;
    }
    else
    {
        last->next = s;
        last = s;
    }
}

void processPrint()
{
    for (student *p = first; p != NULL; p = p->next)
        printf("Name: %s, Email: %s\n", p->name, p->email);
}

void loadFileText(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Load data -> file not found\n");
        exit(0);
    }
    while (!feof(f))
    {
        char name[MAX_LEN], email[MAX_LEN];
        fscanf(f, "%s %s", name, email);
        insertLast(name, email);
    }
    fclose(f);
}

void removeStudentByName(char *name)
{
    if (listEmpty())
        printf("\nList empty!!");
    else
    {
        student *p = first;
        student *prev = NULL;
        while (p != NULL && strcmp(p->name, name) != 0)
        {
            prev = p;
            p = p->next;
        }
        if (p == NULL)
        {
            printf("NOT FOUND student %s\n", name);
        }
        else if (p == first)
        {
            first = first->next;
            free(p);
        }
        else
        {
            prev->next = p->next;
            free(p);
        }
    }
}

void processFind()
{
    if (listEmpty())
        printf("\nList empty!!");
    else
    {
        char name[MAX_LEN];
        printf("\nName: ");
        scanf("%s", name);
        student *p = first;
        for (; p != NULL; p = p->next)
        {
            if (strcmp(p->name, name) == 0)
                break;
        }
        if (p == NULL)
        {
            printf("NOT FOUND student %s\n", name);
        }
        else
        {
            printf("FOUND student! \nName: %s, Email: %s\n", p->name, p->email);
        }
    }
}

void processLoad()
{
    initList();
    char filename[MAX_LEN];
    scanf("%s", filename);
    loadFileText(filename);
}

void processStore()
{
    char filename[256];
    printf("\nFile Name: ");
    scanf("%s", filename);
    FILE *f = fopen(filename, "w");
    for (student *p = first; p != NULL; p = p->next)
    {
        fprintf(f, "%s %s", p->name, p->email);
        if (p->next != NULL)
            fprintf(f, "\n");
    }
    fclose(f);
}

void processInsert()
{
    char name[MAX_LEN], email[MAX_LEN];
    printf("\nName: ");
    scanf("%s", name);
    printf("\nEmail: ");
    scanf("%s", email);
    insertLast(name, email);
}

void processRemove()
{
    char name[MAX_LEN];
    printf("\nName: ");
    scanf("%s", name);
    removeStudentByName(name);
}

int main(void)
{
    int choice;
    for (;;)
    {
        system("cls");
        printf("1.Doc du lieu tu file txt\n2.In danh sach\n3.Them 1 ho so\n4.Xoa 1 ho so\n5.Tim kiem ho so\n6.Luu ho so vao file txt\n7.Exit\n8.Lua chon: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nNhap ten file txt: ");
            processLoad();
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
            break;
        case 2:
            processPrint();
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
            break;
        case 3:
            printf("\nNhap ten va email");
            processInsert();
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
            break;
        case 4:
            printf("\nNhap ten can xoa: ");
            processRemove();
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
            break;
        case 5:
            printf("\nNhap ten can tim: ");
            processFind();
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
            break;
        case 6:
            printf("\nNhap file txt muon luu tru");
            processStore();
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
            break;
        default:
            exit(0);
        }
    }
    return 0;
}