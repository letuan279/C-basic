#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define MAX_L 256

typedef struct Node
{
    char name[10];
    int score;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;
Node *root;
int n = 1;

Node *makeNode(char *name, int score)
{
    Node *p = (Node *)malloc(sizeof(Node));
    printf("\nNut moi thu %d, dia chi: %u", n++, p);
    strcpy(p->name, name);
    p->score = score;
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}

Node *insert(Node *r, char *name, int score)
{
    if (r == NULL)
    {
        return makeNode(name, score);
    }
    int c = strcmp(r->name, name);
    if (c == 0)
    {
        return r;
    }
    else if (c < 0)
    {
        r->rightChild = insert(r->rightChild, name, score);
        return r;
    }
    else
    {
        r->leftChild = insert(r->leftChild, name, score);
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
    while (!feof(f))
    {
        char name1[MAX_L], name2[MAX_L];
        int l, r;
        fscanf(f, "%s\t%s\t%d\t%d\n", name1, name2, &l, &r);
        if (find(root, name1) == NULL && find(root, name2) == NULL)
        {
            int score1 = (l > r) ? 3 : ((l == r) ? 1 : 0);

            root = insert(root, name1, score1);

            int score2 = (l < r) ? 3 : ((l == r) ? 1 : 0);

            root = insert(root, name2, score2);
        }
        else if (find(root, name1) != NULL && find(root, name2) == NULL)
        {
            int score2 = (l < r) ? 3 : ((l == r) ? 1 : 0);

            root = insert(root, name2, score2);

            find(root, name1)->score += (l > r) ? 3 : ((l == r) ? 1 : 0);
        }
        else if (find(root, name2) != NULL && find(root, name1) == NULL)
        {
            int score1 = (l > r) ? 3 : ((l == r) ? 1 : 0);

            root = insert(root, name1, score1);

            find(root, name2)->score += (l < r) ? 3 : ((l == r) ? 1 : 0);
        }
        else
        {
            find(root, name1)->score += (l > r) ? 3 : ((l == r) ? 1 : 0);
            find(root, name2)->score += (l < r) ? 3 : ((l == r) ? 1 : 0);
        }
    }
    fclose(f);
}

void inOrder(Node *r)
{
    if (r == NULL)
        return;
    inOrder(r->leftChild);
    printf("\n%s : %d", r->name, r->score);
    inOrder(r->rightChild);
}

void searchTeam()
{
    char input[10];
    printf("\nNhap ma doi bong muon tim: ");
    fflush(stdin);
    scanf("%s", input);
    Node *p = find(root, input);
    if (p == NULL)
    {
        printf("\nKhong co doi bong nay!");
    }
    else
    {
        printf("\nDiem so cua doi bong nay la: %d", p->score);
    }
}

Node *findMin(Node *r)
{
    if (r == NULL)
        return NULL;
    while (r->leftChild != NULL)
        r = r->leftChild;
    return r;
}

Node *removeTeam(Node *r, char *name)
{
    // X??a 1 h???c sinh
    if (r == NULL)
        return NULL;
    int c = strcmp(r->name, name);
    // T??m h???c sinh c???n x??a
    if (c > 0)
        r->leftChild = removeTeam(r->leftChild, name);
    else if (c < 0)
        r->rightChild = removeTeam(r->rightChild, name);
    else
    {
        // Tr?????ng h???p t??m ???????c h???c sinh c???n x??a trong c??y BST
        if (r->leftChild != NULL && r->rightChild != NULL)
        {
            // N???u l?? node c?? 2 con
            Node *tmp = findMin(r->rightChild); // T??m node tr??i nh???t c???a c??y con b??n ph???i
            // G??n node t??m ???????c cho node c???n x??a
            strcpy(r->name, tmp->name);
            r->score = tmp->score;
            // X??a node tr??i nh???t c???a c??y con b??n ph???i
            r->rightChild = removeTeam(r->rightChild, tmp->name);
        }
        else
        {
            // N???u l?? node c?? 1 con ho???c l?? node l??
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

void searchTeamBayMau(Node *r, int x)
{
    if (r == NULL)
        return;
    searchTeamBayMau(r->leftChild, x);
    if (r->score < x)
    {
        printf("\n%s", r->name);
        root = removeTeam(root, r->name);
    }
    searchTeamBayMau(r->rightChild, x);
}

void teamBayMau()
{
    int x;
    printf("\nNhap X = ");
    scanf("%d", &x);

    printf("\nCac doi bi xuong hang la: ");
    searchTeamBayMau(root, x);

    printf("\nCac doi con lai: ");
    inOrder(root);
}

void writeToResult(FILE *f, Node *r)
{
    if (r == NULL)
        return;
    writeToResult(f, r->leftChild);
    fprintf(f, "%s\t%d\n", r->name, r->score);
    writeToResult(f, r->rightChild);
}

void result(char *filename)
{
    FILE *f = fopen(filename, "w+");
    if (f == NULL)
    {
        printf("Load data -> file not found\n");
        return;
    }

    writeToResult(f, root);

    fclose(f);
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
    // load("BD.txt");
    // inOrder(root);

    // searchTeam();
    // teamBayMau();
    // result("KQ.txt");

    while (1)
    {
        printf("\n1.Tao Cay\n2.Ket qua\n3.Tim kiem\n4.Xuong hang\n5.Xuat file\n6.Quit");
        printf("\nEnter command: (1~6) ");
        char cmd[MAX_L];
        scanf("%s", cmd);
        if (strcmp(cmd, "6") == 0)
            break;
        else if (strcmp(cmd, "1") == 0)
            load("BD.txt");
        else if (strcmp(cmd, "2") == 0)
            inOrder(root);
        else if (strcmp(cmd, "3") == 0)
            searchTeam();
        else if (strcmp(cmd, "4") == 0)
            teamBayMau();
        else if (strcmp(cmd, "5") == 0)
            result("KQ.txt");
        else
            printf("\nInvalid");
    }
    freeTree(root);
}