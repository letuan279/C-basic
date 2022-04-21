#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_LEN 50

typedef struct Profile
{
    char name[MAX_LEN];
    char email[MAX_LEN];
    struct Profile *next; // pointer to the next element
    struct Profile *prev; // pointer to the predecessor
} Profile;

Profile *first, *last;

Profile *makeProfile(char *name, char *email)
{
    Profile *node = (Profile *)malloc(sizeof(Profile));
    strcpy(node->name, name);
    strcpy(node->email, email);
    node->next = NULL;
    node->prev = NULL;
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

void printListLeft2Right()
{
    for (Profile *p = first; p != NULL; p = p->next)
        printf("Name: %s, Email: %s\n", p->name, p->email);
}

void printListRight2Left()
{
    for (Profile *p = last; p != NULL; p = p->prev)
        printf("Name: %s, Email: %s\n", p->name, p->email);
}

void insertLast(char *name, char *email)
{
    Profile *profile = makeProfile(name, email);
    if (listEmpty())
    {
        first = profile;
        last = profile;
    }
    else
    {
        last->next = profile;
        profile->prev = last;
        last = profile;
    }
}

Profile *find(char *name)
{
    for (Profile *p = first; p != NULL; p = p->next)
    {
        if (strcmp(p->name, name) == 0)
        {
            return p;
        }
    }
    return NULL;
}

void removeProfile(char *name)
{
    if (listEmpty())
    {
        printf("\nList empty!");
        exit(0);
    }
    else
    {
        Profile *profile = find(name);
        if (profile == NULL)
        {
            printf("NOT FOUND %s\n", name);
        }
        else
        {
            Profile *left = profile->prev;
            Profile *right = profile->next;
            if (left != NULL)
                left->next = right;
            if (right != NULL)
                right->prev = left;
            if (left == NULL)
                first = right;
            if (right == NULL)
                last = left;
            free(profile);
        }
    }
}

void load(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Load data -> file not found\n");
        exit(0);
    }
    initList();
    while (!feof(f))
    {
        char name[MAX_LEN], email[MAX_LEN];
        fscanf(f, "%s %s", name, email);
        insertLast(name, email);
    }
    fclose(f);
}

void processFind()
{
    char name[MAX_LEN];
    scanf("%s", name);
    Profile *profile = find(name);
    if (profile == NULL)
    {
        printf("NOT FOUND profile %s\n", name);
    }
    else
    {
        printf("FOUND profile: \nName: %s, Email: %s\n", profile->name, profile->email);
    }
}

void processLoad()
{
    char filename[MAX_LEN];
    scanf("%s", filename);
    load(filename);
}

void processStore()
{
    char filename[MAX_LEN];
    scanf("%s", filename);
    FILE *f = fopen(filename, "w");
    for (Profile *p = first; p != NULL; p = p->next)
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
    removeProfile(name);
}

void processPrintList()
{
    printf("Danh sach tu trai qua phai\n");
    printListLeft2Right();
    printf("\n-------------------------\n");
    printf("Danh sach tu phai qua trai\n");
    printListRight2Left();
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
            processPrintList();
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
            printf("\nNhap file txt muon luu tru: ");
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