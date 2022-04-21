#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_L 256
#define MAX 1000

typedef struct Node
{
    char vng[25];
    char eng[25];
    struct Node *leftChild;
    struct Node *rightChild;
} Node;
Node *root;

typedef struct string
{
    char text[MAX_L];
    int thieu;
} string;

Node *makeNode(char *eng, char *vng)
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->vng, vng);
    strcpy(p->eng, eng);
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}

Node *insert(Node *r, char *eng, char *vng)
{
    if (r == NULL)
        return makeNode(eng, vng);
    int c = strcmp(r->eng, eng);
    if (c == 0)
    {
        printf("Word %s exists, do not insert\n", eng);
        return r;
    }
    else if (c < 0)
    {
        r->rightChild = insert(r->rightChild, eng, vng);
        return r;
    }
    else
    {
        r->leftChild = insert(r->leftChild, eng, vng);
        return r;
    }
}

void load(char *filename)
{
    FILE *f = fopen(filename, "r");
    // if (f == NULL)
    // {
    //     printf("Load data -> file not found\n");
    //     return;
    // }
    root = NULL;
    while (!feof(f))
    {
        char eng[25], vng[25];
        fscanf(f, "%s %s", eng, vng);
        printf("%s %s\n", eng, vng);
        root = insert(root, eng, vng);
    }
    fclose(f);
}

void inOrder(Node *r)
{
    if (r == NULL)
        return;
    inOrder(r->leftChild);
    printf("%s %s\n", r->eng, r->vng);
    inOrder(r->rightChild);
}

Node *find(Node *r, char *eng)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->eng, eng);
    if (c == 0)
        return r;
    if (c < 0)
        return find(r->rightChild, eng);
    return find(r->leftChild, eng);
}

void themVaSua()
{
    char input[25];
    printf("\nENG: ");
    scanf("%s", input);
    Node *s = find(root, input);
    if (s)
    {
        printf("\nTim thay trong tu dien: %s %s\nCo muon doi k? (y/n): ", s->eng, s->vng);
        char c;
        fflush(stdin);
        scanf("%c", &c);
        if (c == 'y')
        {
            char tmp[25];
            printf("\nVNG: ");
            scanf("%s", tmp);
            strcpy(s->vng, tmp);
        }
    }
    else
    {
        char tmp[25];
        printf("\nVNG: ");
        scanf("%s", tmp);
        insert(root, input, tmp);
        printf("\nDa them!!");
    }
}

void dich()
{
    // xu ly input
    fflush(stdin);

    char c = '\0';
    string str[MAX];
    int idx_str = 0;
    int idx = 0;
    int check = 0;
    while (c != '\n')
    {
        scanf("%c", &c);
        if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
        {
            str[idx_str].text[idx++] = tolower(c);
            check = 1;
        }
        else if (check)
        {
            str[idx_str].thieu = 0;
            idx_str++;
            idx = 0;
            check = 0;
        }
    }

    for (int i = 0; i < idx_str; ++i)
    {
        printf("\n%s", str[i].text);
    }
    printf("\n---------------------\n");

    // dich
    for (int i = 0; i < idx_str; ++i)
    {
        Node *f = find(root, str[i].text);
        if (f)
        {
            printf("%s ", f->vng);
        }
        else
        {
            printf("<thieu tu> ");
            str[i].thieu = 1;
        }
    }

    int choice;
    printf("\n\nCo muon nhap nhung tu con thieu de dich lai:\n1.muon\n2.k muon\nEnter(1~2): ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        for (int i = 0; i < idx_str; ++i)
        {
            if (str[i].thieu)
            {
                printf("\nVNG for %s: ", str[i].text);
                char vng[25];
                scanf("%s", vng);
                insert(root, str[i].text, vng);
            }
        }

        printf("\nDich lai: \n");
        for (int i = 0; i < idx_str; ++i)
        {
            Node *f = find(root, str[i].text);
            printf("%s ", f->vng);
        }
    }
}

void main()
{
    while (1)
    {
        printf("\n1.Load\n2.Print\n3.Them va Sua\n4.Dich\n5.Quit");
        printf("\nEnter command: (1~5) ");
        char cmd[MAX_L];
        scanf("%s", cmd);
        if (strcmp(cmd, "5") == 0)
            break;
        else if (strcmp(cmd, "1") == 0)
            load("dict.txt");
        else if (strcmp(cmd, "2") == 0)
            inOrder(root);
        else if (strcmp(cmd, "3") == 0)
            themVaSua();
        else if (strcmp(cmd, "4") == 0)
            dich();
        else
            printf("\nInvalid");
    }
    // freeTree(root);
}