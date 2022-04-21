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
} Node;
Node *root;
int n;

Node *makeNode(char *name, float begin, float end, float hieu)
{
    Node *p = (Node *)malloc(sizeof(Node));
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

Node *insert(Node *r, char *name, float begin, float end, float hieu)
{
    if (r == NULL)
        return makeNode(name, begin, end, hieu);
    int c = strcmp(r->name, name);
    if (c == 0)
    {
        return r;
    }
    else if (c < 0)
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

void load(char *filename)
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
        Node *p = find(root, name);
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

float trungbinh(float *a)
{
    float ans = 0;
    for (int i = 0; i < 10; ++i)
    {
        ans += a[i];
    }
    return ans / 10;
}

void inOrder(Node *r)
{
    if (r == NULL)
        return;
    inOrder(r->leftChild);
    printf("%s %.3f\n", r->name, trungbinh(r->hieu));
    inOrder(r->rightChild);
}

float MAX(float *a)
{
    float max = -100000;
    for (int i = 0; i < 10; ++i)
    {
        max = (max > a[i]) ? max : a[i];
    }
    return max;
}

float MIN(float *a)
{
    float min = 1000000;
    for (int i = 0; i < 10; ++i)
    {
        min = (min < a[i]) ? min : a[i];
    }
    return min;
}

void searchMaChungKhoan()
{
    char name[MAX_L];
    printf("\nNhap ma chung khoan can tim: ");
    fflush(stdin);
    scanf("%s", name);

    Node *p = find(root, name);
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

void SearchXuHuongTang(Node *r)
{
    if (r == NULL)
        return;
    SearchXuHuongTang(r->leftChild);
    if (r->hieu[0] > 0 && r->hieu[1] > 0)
    {
        printf("\n%s", r->name);
    }
    SearchXuHuongTang(r->rightChild);
}

int soNgayTang(Node *r)
{
    int count = 0;

    for (int i = 0; i < 10; ++i)
    {
        if (r->hieu[i] > 0)
            count++;
    }

    return count;
}

int soNgayTangLonNhat(Node *r)
{
    if (r == NULL)
        return 0;
    int ans = 0;
    int left = soNgayTangLonNhat(r->leftChild);
    ans = soNgayTang(r);
    int right = soNgayTangLonNhat(r->rightChild);

    return (ans > right && ans > left) ? ans : ((right > left) ? right : left);
}

void printMaCoSoNgayTangLonNhat(Node *r, int x)
{
    if (r == NULL)
        return;
    printMaCoSoNgayTangLonNhat(r->leftChild, x);
    if (soNgayTang(r) == x)
    {
        printf("\n%s", r->name);
    }
    printMaCoSoNgayTangLonNhat(r->rightChild, x);
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
    while (1)
    {
        system("cls");
        printf("\n1.Doc file\n2.Tim kiem theo ma chung khoan\n3.Tim kiem ma chung khoan co xu huong tang\n4.Tim ma co so ngay lon nhat\n5.Thoat chuong trinh");
        printf("\nNhap lenh: (1~5) ");
        char cmd[MAX_L];
        scanf("%s", cmd);
        if (strcmp(cmd, "5") == 0)
        {
            printf("\nHo va ten: LE ANH TUAN\nMssv: 20205136");
            break;
        }
        else if (strcmp(cmd, "1") == 0)
        {
            load("data.txt");
            inOrder(root);
            printf("\nNhap phim bat ky de tiep tuc ...");
            getch();
        }
        else if (strcmp(cmd, "2") == 0)
        {
            searchMaChungKhoan();
            printf("\nNhap phim bat ky de tiep tuc ...");
            getch();
        }
        else if (strcmp(cmd, "3") == 0)
        {
            printf("\nCac ma dong thoi tang trong 2 ngay 1 va 2 la: ");
            SearchXuHuongTang(root);
            printf("\nNhap phim bat ky de tiep tuc ...");
            getch();
        }
        else if (strcmp(cmd, "4") == 0)
        {
            int max = soNgayTangLonNhat(root);
            printf("\nSo ngay tang lon nhat la: %d", max);
            printf("\nCac ma co so ngay tang lon nhat la: ");
            printMaCoSoNgayTangLonNhat(root, max);
            printf("\nNhap phim bat ky de tiep tuc ...");
            getch();
        }
        else
            printf("\nInvalid");
    }
    freeTree(root);
}