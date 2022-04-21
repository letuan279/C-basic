#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_L 256
#define MAX 100

typedef struct Node
{
    int maso;
    char dochoi[30];
    struct Node *leftChild;
    struct Node *rightChild;
} Node;
Node *root = NULL;

typedef struct Array
{
    int maso;
    char dochoi[30];
} Array;

Array B[MAX];
int B_sl = 0;
int A_sl = 0;
int H_sl = 0;
int H[MAX];
Array C[MAX];
int C_sl = 0;
int check = 0;

Node *makeNode(int maso, char *dochoi)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->maso = maso;
    strcpy(p->dochoi, dochoi);
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}

Node *find(Node *r, int maso)
{
    if (r == NULL)
        return NULL;
    int c = r->maso - maso;
    if (c == 0)
        return r;
    if (c < 0)
        return find(r->rightChild, maso);
    return find(r->leftChild, maso);
}

Node *findMin(Node *r)
{
    if (r == NULL)
        return NULL;
    while (r->leftChild != NULL)
        r = r->leftChild;
    return r;
}

Node *removeNode(Node *r, int maso)
{
    if (r == NULL)
        return NULL;
    int c = r->maso - maso;
    if (c > 0)
        r->leftChild = removeNode(r->leftChild, maso);
    else if (c < 0)
        r->rightChild = removeNode(r->rightChild, maso);
    else
    {
        if (r->leftChild != NULL && r->rightChild != NULL)
        {
            Node *tmp = findMin(r->rightChild);
            r->maso = tmp->maso;
            strcpy(r->dochoi, tmp->dochoi);
            r->rightChild = removeNode(r->rightChild, tmp->maso);
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

Node *insert_A(Node *r, int maso, char *dochoi)
{
    if (r == NULL)
        return makeNode(maso, dochoi);
    int c = r->maso - maso;
    if (c == 0)
    {
        printf("\nMaso %d da ton tai, khong them vao", maso);
        return r;
    }
    else if (c < 0)
    {
        r->rightChild = insert_A(r->rightChild, maso, dochoi);
        return r;
    }
    else
    {
        r->leftChild = insert_A(r->leftChild, maso, dochoi);
        return r;
    }
}

void load_A(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("\n khong tim thay file");
        return;
    }
    while (!feof(f))
    {
        int maso;
        char dochoi[30];
        fscanf(f, "%d\t%s", &maso, dochoi);
        root = insert_A(root, maso, dochoi);
    }
    fclose(f);
}

void load_B(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("\n khong tim thay file");
        return;
    }
    int index = 0;
    while (!feof(f))
    {
        int maso;
        char dochoi[30];
        fscanf(f, "%d\t%s", &maso, dochoi);
        B[index].maso = maso;
        strcpy(B[index].dochoi, dochoi);
        index++;
    }
    B_sl = index;
    fclose(f);
}

void print_A_inOrder(Node *r)
{
    if (r == NULL)
        return;
    print_A_inOrder(r->leftChild);
    printf("%d   %s\n", r->maso, r->dochoi);
    print_A_inOrder(r->rightChild);
}

void print_A_postOrder(Node *r)
{
    if (r == NULL)
        return;
    print_A_postOrder(r->rightChild);
    printf("%d   %s\n", r->maso, r->dochoi);
    A_sl++;
    print_A_postOrder(r->leftChild);
}

void print_B()
{
    printf("\nfile B:\n");
    for (int i = 0; i < B_sl; ++i)
    {
        printf("%d   %s\n", B[i].maso, B[i].dochoi);
    }
}

void search()
{
    for (int i = 0; i < B_sl; ++i)
    {
        Node *a = find(root, B[i].maso);
        if (a != NULL)
        {
            printf("%d   %s\n", a->maso, a->dochoi);
            root = removeNode(root, a->maso);
        }
    }
}

void merge()
{
    for (int i = 0; i < B_sl; ++i)
    {
        root = insert_A(root, B[i].maso, B[i].dochoi);
    }
}

void setup()
{
    for (int i = 0; i < MAX; ++i)
    {
        H[i] = 0;
    }
}

int hash(char *s)
{ // hash function
    int rs = 0;
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        rs = (rs * 255 + s[i]) % MAX;
    return rs;
}

void duyetCayA(Node *r)
{
    if (r == NULL)
        return;
    for (int i = 0; i < C_sl; ++i)
    {
        if (strcmp(r->dochoi, C[i].dochoi) == 0)
        {
            check = 1;
            break; // khong them vao C[]
        }
    }
    if (check == 0)
    {
        strcpy(C[C_sl].dochoi, r->dochoi);
        C_sl++;
    }
    H[hash(r->dochoi)]++;
    check = 0;
    duyetCayA(r->leftChild);
    duyetCayA(r->rightChild);
}

void thongke()
{
    setup();
    duyetCayA(root);
    for (int i = 0; i < C_sl; ++i)
    {
        printf("\n%s\t%d", C[i].dochoi, H[hash(C[i].dochoi)]);
    }
    printf("\n");
}

int main()
{
    while (1)
    {
        printf("\n1.Doc file A\n2.Doc file B\n3.Tim kiem\n4.Tong hop\n5.Thong ke\n6.Quit");
        printf("\nEnter command: (1~6) ");
        char cmd[MAX_L];
        scanf("%s", cmd);
        if (strcmp(cmd, "6") == 0)
            break;
        else if (strcmp(cmd, "1") == 0)
        {
            load_A("A.txt");
            print_A_inOrder(root);
        }
        else if (strcmp(cmd, "2") == 0)
        {
            load_B("B.txt");
            print_B();
        }
        else if (strcmp(cmd, "3") == 0)
        {
            printf("\nCac ma so bi trung: \n");
            search();
            printf("\nA:\n");
            print_A_inOrder(root);
        }
        else if (strcmp(cmd, "4") == 0)
        {
            merge();
            printf("\nA:\n");
            print_A_postOrder(root);
        }
        else if (strcmp(cmd, "5") == 0)
        {
            thongke();
        }
        else
            printf("\nInvalid");
    }
    return 0;
}
