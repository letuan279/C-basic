#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_L 256
#define MAX 1000
typedef struct Profile
{
    char name[MAX_L];
    char email[MAX_L];
} Profile;
Profile students[MAX];
int n = 0;

void insert(char *name, char *email)
{
    // maintain increasing order of name
    int i = n - 1;
    while (i >= 0)
    {
        int c = strcmp(students[i].name, name);
        if (c == 0)
        {
            printf("Name %s exists, do not insert\n", name);
            return;
        }
        else if (c > 0)
        {
            students[i + 1] = students[i];
            i--;
        }
        else
            break;
    }
    i++;
    strcpy(students[i].name, name);
    strcpy(students[i].email, email);
    n++;
}

void removeStudent(int idx)
{
    for (int i = idx; i < n - 1; i++)
        students[i] = students[i + 1];
    n--;
}

void load(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Load data -> file not found\n");
        return;
    }
    n = 0;
    while (!feof(f))
    {
        char name[MAX_L], email[MAX_L];
        fscanf(f, "%s%s", name, email);
        insert(name, email);
    }
    fclose(f);
}

void printList()
{
    for (int i = 0; i < n; i++)
        printf("student[%d]: %s, %s\n", i, students[i].name, students[i].email);
}

int binarySearch(int L, int R, char *name)
{
    if (L > R)
        return -1;
    if (L == R)
    {
        if (strcmp(students[L].name, name) == 0)
            return L;
        else
            return -1;
    }
    int m = (L + R) / 2;
    int c = strcmp(students[m].name, name);
    if (c == 0)
        return m;
    if (c < 0)
        return binarySearch(m + 1, R, name);
    return binarySearch(L, m - 1, name);
}

void processFind()
{
    char name[MAX_L];
    scanf("%s", name);
    int idx = binarySearch(0, n - 1, name);
    if (idx == -1)
    {
        printf("Not found student %s\n", name);
    }
    else
    {
        printf("Found student %s, at position %d, email %s\n", students[idx].name, idx, students[idx].email);
    }
}

void processLoad()
{
    char filename[MAX_L];
    printf("\nInput file's name: ");
    scanf("%s", filename);
    load(filename);
}

void processStore()
{
    char filename[MAX_L];
    scanf("%s", filename);
    FILE *f = fopen(filename, "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%s %s", students[i].name, students[i].email);
        if (i < n - 1)
            fprintf(f, "\n");
    }
    fclose(f);
}

void processInsert()
{
    char name[MAX_L], email[MAX_L];
    scanf("%s%s", name, email);
    insert(name, email);
}

void processRemove()
{
    char name[256];
    scanf("%s", name);
    int idx = binarySearch(0, n - 1, name);
    if (idx == -1)
        printf("Not found %s\n", name);
    else
    {
        removeStudent(idx);
    }
}

int main()
{
    while (1)
    {
        printf("\n1.Load\n2.Print\n3.Find\n4.Insert\n5.Remove\n6.Store\n7.Exit\nEnter choice: ");
        int choice;
        scanf("%d", &choice);
        if (choice == 7)
            break;
        else if (choice == 1)
            processLoad();
        else if (choice == 2)
            printList();
        else if (choice == 3)
            processFind();
        else if (choice == 4)
            processInsert();
        else if (choice == 5)
            processRemove();
        else if (choice == 6)
            processStore();
        else
            break;
    }
}
