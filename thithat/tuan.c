#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_L 256

typedef struct Node
{
    char name[MAX_L];
    float begin[10];
    float end[10];
    float hieu[10];
    int index;
    struct Node *leftChild;
    struct Node *rightChild;
} Stock;
Stock *root;
int n;

Stock *createStock(char *name, float begin, float end, float hieu)
{
    Stock *p = (Stock *)malloc(sizeof(Stock));
    strcpy(p->name, name);
    p->index = 0;
    p->begin[0] = begin;
    p->end[0] = end;
    p->hieu[0] = end - begin;
    p->index++;
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}

Stock *insert(Stock *r, char *name, float begin, float end, float hieu)
{
    if (r == NULL)
        return createStock(name, begin, end, hieu);
    if (strcmp(r->name, name) == 0)
    {
        return r;
    }
    else if (strcmp(r->name, name) < 0)
    {
        r->rightChild = insert(r->rightChild, name, begin, end, hieu);
        return r;
    }
    else
    {
        r->leftChild = insert(r->leftChild, name, begin, end, hieu);
        return r;
    }
}

Stock *find(Stock *r, char *name)
{
    if (r == NULL)
        return NULL;
    if (strcmp(r->name, name) == 0)
        return r;
    if (strcmp(r->name, name) < 0)
        return find(r->rightChild, name);
    return find(r->leftChild, name);
}

void f_load(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Load data -> file not found\n");
        return;
    }
    root = NULL;
    fscanf(f, "%d", &n);

    while (!feof(f))
    {
        char name[MAX_L];
        float begin, end;
        fscanf(f, "%s\t%f\t%f\n", name, &begin, &end);
        Stock *p = find(root, name);
        if (p == NULL)
        {
            root = insert(root, name, begin, end, end - begin);
        }
        else
        {
            p->begin[p->index] = begin;
            p->end[p->index] = end;
            p->hieu[p->index] = end - begin;
            p->index++;
        }
    }
    fclose(f);
}

float average(float *a)
{
    float ans = 0;
    int i;
    for (i = 0; i < 10; ++i)
    {
        ans += a[i];
    }
    return ans / 10;
}

void inOrder(Stock *r)
{
    if (r == NULL)
        return;
    inOrder(r->leftChild);
    printf("%s %.3f\n", r->name, average(r->hieu));
    inOrder(r->rightChild);
}

float MAX(float *a)
{
    float max = -100000;
    int i;
    for (i = 0; i < 10; ++i)
    {
        max = (max > a[i]) ? max : a[i];
    }
    return max;
}

float MIN(float *a)
{
    float min = 1000000;
    int i;
    for (i = 0; i < 10; ++i)
    {
        min = (min < a[i]) ? min : a[i];
    }
    return min;
}

void searchStock()
{
    char name[MAX_L];
    printf("\nNhap ma chung khoan can tim: ");
    fflush(stdin);
    scanf("%s", name);

    Stock *p = find(root, name);
    if (p == NULL)
    {
        printf("\nKhong tim thay ...");
        return;
    }
    else
    {
        printf("\nMa co phieu: %s", p->name);
        printf("\nGia dong cua cao nhat: %.3f", MAX(p->end));
        printf("\nGia dong cua thap nhat: %.3f", MIN(p->end));
    }
}

void SearchUpTrend(Stock *r)
{
    if (r == NULL)
        return;
    SearchUpTrend(r->leftChild);
    if (r->hieu[0] > 0 && r->hieu[1] > 0)
    {
        printf("\n%s", r->name);
    }
    SearchUpTrend(r->rightChild);
}

int soNgayTang(Stock *r)
{
    int count = 0;
    int i;
    for (i = 0; i < 10; ++i)
    {
        if (r->hieu[i] > 0)
            count++;
    }

    return count;
}

int soNgayTangMax(Stock *r)
{
    if (r == NULL)
        return 0;
    int ans = 0;
    int left = soNgayTangMax(r->leftChild);
    ans = soNgayTang(r);
    int right = soNgayTangMax(r->rightChild);

    return (ans > right && ans > left) ? ans : ((right > left) ? right : left);
}

void printMaCoSoNgayTangMax(Stock *r, int x)
{
    if (r == NULL)
        return;
    printMaCoSoNgayTangMax(r->leftChild, x);
    if (soNgayTang(r) == x)
    {
        printf("\n%s", r->name);
    }
    printMaCoSoNgayTangMax(r->rightChild, x);
}

void freeTree(Stock *r)
{
    if (r == NULL)
        return;
    freeTree(r->leftChild);
    freeTree(r->rightChild);
    free(r);
}

int main()
{

    while (1)
    {
        printf("\n1.Doc file\n2.Tim kiem theo ma chung khoan\n3.Tim kiem ma chung khoan co xu huong tang\n4.Tim ma co so ngay lon nhat\n5.Thoat chuong trinh");
        printf("\nNhap lenh: (1~5) ");
        char cmd[MAX_L];
        scanf("%s", cmd);
        if (strcmp(cmd, "5") == 0)
        {
            printf("\nHo va ten: TRAN MINH TUAN\nMssv: 20205137");
            break;
        }
        else if (strcmp(cmd, "1") == 0)
        {
            f_load("data.txt");
            inOrder(root);
        }
        else if (strcmp(cmd, "2") == 0)
        {
            searchStock();
        }
        else if (strcmp(cmd, "3") == 0)
        {
            printf("\nCac ma dong thoi tang trong 2 ngay la: ");
            SearchUpTrend(root);
        }
        else if (strcmp(cmd, "4") == 0)
        {
            printf("\nSo ngay tang lon nhat la: %d", soNgayTangMax(root));
            printf("\nCac ma co so ngay tang lon nhat la: ");
            printMaCoSoNgayTangMax(root, soNgayTangMax(root));
        }
        else
            printf("\nInvalid");
    }
    freeTree(root);
}