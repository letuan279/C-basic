#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_L 256

typedef struct Node
{
    int maso;
    char dochoi[30];
    struct Node *leftChild;
    struct Node *rightChild;
} Node;
Node *root;

typedef struct Array
{
    int maso;
    char dochoi[30];
} Array;
Array B[MAX_L];
Array A[MAX_L];
int B_sl;
int A_sl = 0;

Node *makeNode(int maso, char *dochoi)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->maso = maso;
    strcpy(p->dochoi, dochoi);
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}

Node *insert(Node *r, int maso, char *dochoi)
{
    if (r == NULL)
        return makeNode(maso, dochoi);
    int c = r->maso - maso;
    if (c == 0)
    {
        printf("Ma so %d exists, do not insert\n", maso);
        return r;
    }
    else if (c < 0)
    {
        r->rightChild = insert(r->rightChild, maso, dochoi);
        return r;
    }
    else
    {
        r->leftChild = insert(r->leftChild, maso, dochoi);
        return r;
    }
}

void loadFileA(char *filename)
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
        int maso;
        char dochoi[30];
        fscanf(f, "%d\t%s", &maso, dochoi);
        root = insert(root, maso, dochoi);
    }
    fclose(f);
}

void inOrder(Node *r)
{
    if (r == NULL)
        return;
    inOrder(r->leftChild);
    printf("%d\t%s\n", r->maso, r->dochoi);
    inOrder(r->rightChild);
}

void loadFileB(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Load data -> file not found\n");
        return;
    }
    B_sl = 0;
    while (!feof(f))
    {
        int maso;
        char dochoi[30];
        fscanf(f, "%d\t%s", &maso, dochoi);
        B[B_sl].maso = maso;
        strcpy(B[B_sl].dochoi, dochoi);
        B_sl++;
    }
    fclose(f);
}

void printB()
{
    for (int i = 0; i < B_sl; ++i)
    {
        printf("%d\t%s\n", B[i].maso, B[i].dochoi);
    }
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

Node *removeStudent(Node *r, int maso)
{
    // Xóa 1 học sinh
    if (r == NULL)
        return NULL;
    int c = r->maso - maso;
    // Tìm học sinh cần xóa
    if (c > 0)
        r->leftChild = removeStudent(r->leftChild, maso);
    else if (c < 0)
        r->rightChild = removeStudent(r->rightChild, maso);
    else
    {
        // Trường hợp tìm được học sinh cần xóa trong cây BST
        if (r->leftChild != NULL && r->rightChild != NULL)
        {
            // Nếu là node có 2 con
            Node *tmp = findMin(r->rightChild); // Tìm node trái nhất của cây con bên phải
            // Gán node tìm được cho node cần xóa
            r->maso = tmp->maso;
            strcpy(r->dochoi, tmp->dochoi);
            // Xóa node trái nhất của cây con bên phải
            r->rightChild = removeStudent(r->rightChild, tmp->maso);
        }
        else
        {
            // Nếu là node có 1 con hoặc là node lá
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

void xoatrunglap()
{
    printf("\nCac ma so bi trung: \n");
    for (int i = 0; i < B_sl; ++i)
    {
        if (find(root, B[i].maso) != NULL)
        {
            printf("%d\t%s\n", B[i].maso, B[i].dochoi);
        }
        removeStudent(root, B[i].maso);
    }

    printf("\nA: \n");
    inOrder(root);
}

void printAdec(Node *r)
{
    if (r == NULL)
        return;
    printAdec(r->rightChild);
    printf("%d\t%s\n", r->maso, r->dochoi);

    A[A_sl].maso = r->maso;
    strcpy(A[A_sl].dochoi, r->dochoi);
    A_sl++;

    printAdec(r->leftChild);
}

void chenAll()
{
    for (int i = 0; i < B_sl; ++i)
    {
        root = insert(root, B[i].maso, B[i].dochoi);
    }

    printAdec(root);
}

Array C[MAX_L];
int C_sl = 0;

void thongke()
{
    for (int i = 0; i < A_sl; ++i)
    {
        int check = 0;
        for (int j = 0; j < C_sl; ++j)
        {
            if (strcmp(A[i].dochoi, C[j].dochoi) == 0)
            {
                check = 1;
                break;
            }
        }
        if (check == 0)
        {
            strcpy(C[C_sl].dochoi, A[i].dochoi);
            C_sl++;
        }
    }

    for (int i = 0; i < C_sl; ++i)
    {
        int sl = 0;
        for (int j = 0; j < A_sl; ++j)
        {
            if (strcmp(C[i].dochoi, A[j].dochoi) == 0)
                sl++;
        }
        printf("\n%s: %d", C[i].dochoi, sl);
    }
}

void freeTree(Node *r)
{
    if (r == NULL)
        return;
    freeTree(r->leftChild);
    freeTree(r->rightChild);
    free(r);
}

int main()
{
    // loadFileA("A.txt");
    // inOrder(root);
    // printf("\n---------------\n");
    // loadFileB("B.txt");
    // printB();
    // printf("\n---------------\n");
    // xoatrunglap();
    // printf("\n---------------\n");
    // chenAll();
    // printf("\n---------------\n");
    // thongke();
    while (1)
    {
        printf("\n1.Load file A and print\n2.Load file B and print\n3.Search\n4.Merge\n5.Statistic\n6.Quit");
        printf("\nEnter command: (1~7) ");
        char cmd[MAX_L];
        scanf("%s", cmd);
        if (strcmp(cmd, "6") == 0)
            break;
        else if (strcmp(cmd, "1") == 0)
        {
            loadFileA("A.txt");
            inOrder(root);
        }
        else if (strcmp(cmd, "2") == 0)
        {
            loadFileB("B.txt");
            printB();
        }
        else if (strcmp(cmd, "3") == 0)
            xoatrunglap();
        else if (strcmp(cmd, "4") == 0)
            chenAll();
        else if (strcmp(cmd, "5") == 0)
            thongke();
        else
            printf("\nInvalid");
    }
    freeTree(root);
}