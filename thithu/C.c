#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_L 256

typedef struct Node
{
    char name[40];
    int hour;
    int minute;
    struct Node *next;
} Node;
Node *first;

Node *makeNode(char *name, int hour, int minute)
{
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node->name, name);
    node->hour = hour;
    node->minute = minute;
    node->next = NULL;
    return node;
}

void initList()
{
    first = NULL;
}

int listEmpty()
{
    return first == NULL;
}

void insertLast(char *name, int hour, int minute)
{
    Node *s = makeNode(name, hour, minute);
    if (listEmpty())
    {
        first = s;
    }
    else
    {
        Node *p = first;
        while (p->next != NULL)
            p = p->next;
        p->next = s;
    }
}

void readLog(char *fileName)
{
    FILE *f = fopen(fileName, "r");
    if (f == NULL)
    {
        printf("Load data -> file not found\n");
        exit(0);
    }

    initList();

    while (!feof(f))
    {
        char name[40];
        int hour, minute;
        fscanf(f, "%s %d %d", name, &hour, &minute);
        insertLast(name, hour, minute);
    }
    fclose(f);
}

void printNode()
{
    for (Node *p = first; p != NULL; p = p->next)
        printf("\n%-50s%-10d%-10d", p->name, p->hour, p->minute);
}

void findNode(char *name)
{
    Node *p = first;
    int check = 0;
    while (p != NULL)
    {
        if (strcmp(p->name, name) == 0)
        {
            if (check)
                printf(", ");
            printf("%d:%d", p->hour, p->minute);
            check = 1;
        }
        p = p->next;
    }

    if (!check)
        printf("\nBan chua toi dia diem do");
    check = 0;
}

void findByTime()
{
    int hour, minute;
    do
    {
        printf("\nNhap gio: ");
        scanf("%d", &hour);
        printf("\nNhap phut: ");
        scanf("%d", &minute);
        if (hour < 0 || hour > 24 || minute < 0 || minute > 60)
        {
            printf("\nKhong hop le! Vui long nhap lai\n");
        }
    } while (hour < 0 || hour > 24 || minute < 0 || minute > 60);

    Node *p = first;
    int check = 0;
    while (p != NULL)
    {
        if (p->hour == hour && p->minute == minute)
        {
            printf("\n%s", p->name);
            check = 1;
            break;
        }
        p = p->next;
    }

    if (!check)
    {
        printf("\nKHONG tim thay lich su di chuyen!");
    }
}

void checkCovid()
{
    printf("\nNhap ten dia diem: ");
    char name[40];
    scanf("%s", name);

    int hour, minute;
    do
    {
        printf("\nNhap gio: ");
        scanf("%d", &hour);
        printf("\nNhap phut: ");
        scanf("%d", &minute);
        if (hour < 0 || hour > 24 || minute < 0 || minute > 60)
        {
            printf("\nKhong hop le! Vui long nhap lai\n");
        }
    } while (hour < 0 || hour > 24 || minute < 0 || minute > 60);

    Node *p = first;
    int check = 0;
    while (p != NULL)
    {
        if (strcmp(p->name, name) == 0)
        {
            if (p->hour * 60 + p->minute >= hour * 60 + minute)
            {
                printf("\nBan co kha nang bi lay Covid, can phai khai bao y te ngay lap tuc!");
                check = 1;
                break;
            }
        }
        p = p->next;
    }

    if (!check)
    {
        printf("\nLich su di chuyen cua ban OK");
    }
}

void freeNode()
{
    while (first != NULL)
    {
        Node *remove = first;
        first = first->next;
        free(remove);
    }
}

int main()
{
    while (1)
    {
        system("cls");
        printf("===================");
        printf("\n1. Nap file log lich su di chuyen\n2. In ra lich su di chuyen\n3. Tim kiem lich su theo dia diem\n4. Tim kiem lich su theo thoi gian\n5. Kiem tra truy vet moi nhat\n6. Thoat");
        printf("\n===================");
        printf("\nNhap lenh(1~6): ");
        char cmd[MAX_L];
        scanf("%s", cmd);
        if (strcmp(cmd, "6") == 0)
        {
            freeNode();
            break;
        }
        else if (strcmp(cmd, "1") == 0)
        {
            readLog("log.txt");
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
        }
        else if (strcmp(cmd, "2") == 0)
        {
            printNode();
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
        }
        else if (strcmp(cmd, "3") == 0)
        {
            printf("\nNhap ten dia diem: ");
            char name[40];
            scanf("%s", name);
            findNode(name);
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
        }
        else if (strcmp(cmd, "4") == 0)
        {
            findByTime();
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
        }
        else if (strcmp(cmd, "5") == 0)
        {
            checkCovid();
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
        }
        else
            printf("\nInvalid");
    }
    return 0;
}