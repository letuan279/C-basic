#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <conio.h>
#define MAX_LEN 50

typedef struct student
{
    char name[MAX_LEN];
    char email[MAX_LEN];
    struct student *next;
} student;
student *first;

student *makeNode(char *name, char *email)
{
    student *node = (student *)malloc(sizeof(student));
    strcpy(node->name, name);
    strcpy(node->email, email);
    node->next = NULL;
    return node;
}

void initStack()
{
    first = NULL;
}

int stackEmpty()
{
    return first == NULL;
}

void insertFirst(char *name, char *email)
{
    student *s = makeNode(name, email);
    s->next = first;
    first = s;
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
        insertFirst(name, email);
    }
    fclose(f);
}

void popAStudent()
{
    if (stackEmpty())
        printf("\nList empty!!");
    else
    {
        student *tmp = first;
        first = first->next;
        printf("\nPop student: \nName: %s\nEmail: %s\n", tmp->name, tmp->email);
        free(tmp);
    }
}

void processFind()
{
    if (stackEmpty())
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
    initStack();
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
    insertFirst(name, email);
}

void processRemove()
{
    popAStudent();
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