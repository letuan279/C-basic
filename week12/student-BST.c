#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_L 256
#define MAX 100000

typedef struct Node
{
    char name[MAX_L];
    char email[MAX_L];
    struct Node *leftChild;
    struct Node *rightChild;
} Node;
Node *root;

Node *makeNode(char *name, char *email)
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->name, name);
    strcpy(p->email, email);
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}

Node *insert(Node *r, char *name, char *email)
{
    if (r == NULL)
        return makeNode(name, email);
    int c = strcmp(r->name, name);
    if (c == 0)
    {
        printf("Student %s exists, do not insert\n", name);
        return r;
    }
    else if (c < 0)
    {
        r->rightChild = insert(r->rightChild, name, email);
        return r;
    }
    else
    {
        r->leftChild = insert(r->leftChild, name, email);
        return r;
    }
}

Node *find(Node *r, char *name)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->name, name);
    if (c == 0)
        return r;
    if (c < 0)
        return find(r->rightChild, name);
    return find(r->leftChild, name);
}

Node *findMin(Node *r)
{
    if (r == NULL)
        return NULL;
    while (r->leftChild != NULL)
        r = r->leftChild;
    return r;
}

Node *removeStudent(Node *r, char *name)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->name, name);
    if (c > 0)
        r->leftChild = removeStudent(r->leftChild, name);
    else if (c < 0)
        r->rightChild = removeStudent(r->rightChild, name);
    else
    {
        if (r->leftChild != NULL && r->rightChild != NULL)
        {
            Node *tmp = findMin(r->rightChild);
            strcpy(r->name, tmp->name);
            strcpy(r->email, tmp->email);
            r->rightChild = removeStudent(r->rightChild, tmp->name);
        }
        else
        {
            Node *tmp = r;
            if (r->leftChild == NULL)
                r = r->rightChild;
            else
                r = r->leftChild;
            free(tmp);
        }
    }
    return r;
}

void freeTree(Node *r)
{
    if (r == NULL)
        return;
    freeTree(r->leftChild);
    freeTree(r->rightChild);
    free(r);
}

void load(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Load data -> file not found\n");
        return;
    }
    root = NULL;
    while (!feof(f))
    {
        char name[MAX_L], email[MAX_L];
        fscanf(f, "%s%s", name, email);
        root = insert(root, name, email);
    }
    fclose(f);
}

void inOrder(Node *r)
{
    if (r == NULL)
        return;
    inOrder(r->leftChild);
    printf("%s, %s\n", r->name, r->email);
    inOrder(r->rightChild);
}

void inOrderF(Node *r, FILE *f)
{
    if (r == NULL)
        return;
    inOrderF(r->leftChild, f);
    fprintf(f, "%s %s\n", r->name, r->email);
    inOrderF(r->rightChild, f);
}

void printList()
{
    inOrder(root);
    printf("\n");
}

void processStore()
{
    char filename[MAX_L];
    printf("\nFilename: ");
    scanf("%s", filename);
    FILE *f = fopen(filename, "w");
    inOrderF(root, f);
    fclose(f);
}

void processInsert()
{
    char name[MAX_L], email[MAX_L];
    printf("\nName: ");
    scanf("%s", name);
    printf("\nEmail: ");
    scanf("%s", email);
    root = insert(root, name, email);
}

void processRemove()
{
    char name[MAX_L];
    printf("\nName: ");
    scanf("%s", name);
    root = removeStudent(root, name);
}

void processLoad()
{
    char filename[MAX_L];
    printf("\nFilename: ");
    scanf("%s", filename);
    load(filename);
}

void processFind()
{
    char name[MAX_L];
    printf("\nName: ");
    scanf("%s", name);
    Node *studentFind = find(root, name);
    if (studentFind == NULL)
    {
        printf("\nNot found!!");
    }
    else
    {
        printf("\n------Found-student-------\n");
        printf("Name: %s\n", studentFind->name);
        printf("Email: %s\n", studentFind->email);
    }
}

void main()
{
    while (1)
    {
        printf("\n1.Load\n2.Print\n3.Find\n4.Insert\n5.Remove\n6.Store\n7.Quit");
        printf("\nEnter command: (1~7) ");
        char cmd[MAX_L];
        scanf("%s", cmd);
        if (strcmp(cmd, "7") == 0)
            break;
        else if (strcmp(cmd, "1") == 0)
            processLoad();
        else if (strcmp(cmd, "2") == 0)
            printList();
        else if (strcmp(cmd, "3") == 0)
            processFind();
        else if (strcmp(cmd, "4") == 0)
            processInsert();
        else if (strcmp(cmd, "5") == 0)
            processRemove();
        else if (strcmp(cmd, "6") == 0)
            processStore();
        else
            printf("\nInvalid");
    }
    freeTree(root);
}