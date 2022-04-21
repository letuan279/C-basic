#include <stdio.h>
#include <stdio.h>
#include <string.h>
#define MAX 20

typedef struct phoneaddress_t
{
    char name[20];
    char tel[11];
    char email[25];
} phoneaddress;

typedef struct Node
{
    phoneaddress data;
    struct Node *left, *right;
} TreeType;

TreeType *Search(char *email, TreeType *Root)
{
    if (Root == NULL)
        return NULL;
    else if (strcmp(Root->data.email, email) == 0)
        return Root;
    else if (strcmp(Root->data.email, email) < 0)
        return Search(email, Root->right);
    else
        return Search(email, Root->left);
}

void InsertNode(phoneaddress data, TreeType **Root)
{
    if (*Root == NULL)
    {
        *Root = (TreeType *)malloc(sizeof(TreeType));
        strcmp((*Root)->data.email, data.email);
        strcmp((*Root)->data.tel, data.tel);
        strcmp((*Root)->data.name, data.name);
        (*Root)->left = NULL;
        (*Root)->right = NULL;
    }
    else if (strcmp((*Root)->data.email, data.email) > 0)
        InsertNode(data, (*Root)->left);
    else if (strcmp((*Root)->data.email, data.email) < 0)
        InsertNode(data, (*Root)->right);
}

void printData(phoneaddress data)
{
    printf("\n--------------------------");
    printf("\nName: ", data.name);
    printf("\nTel: ", data.tel);
    printf("\nEmail: ", data.email);
}

void pre_order_display(TreeType *r)
{
    if (r == NULL)
        return;
    printData(r->data);
    pre_order_display(r->left);
    pre_order_display(r->right);
}

void in_order_display(TreeType *r)
{
    if (r == NULL)
        return;
    in_order_display(r->left);
    printData(r->data);
    in_order_display(r->right);
}

void post_order_display(TreeType *r)
{
    if (r == NULL)
        return;
    post_order_display(r->left);
    post_order_display(r->right);
    printData(r->data);
}

int main(void)
{
    FILE *fp;
    phoneaddress phonearr[MAX];
    TreeType *root = NULL;
    int n = 10;

    if ((fp = fopen("phonebook.dat", "rb")) == NULL)
    {
        printf("Can not open %s.\n", "phonebook.dat");
        return 1;
    }
    fread(phonearr, sizeof(phoneaddress), n, fp);

    fclose(fp);

    for (int i = 0; i < n; i++)
        InsertNode(phonearr[i], &root);

    pre_order_display(root);

    // Search for an email

    FILE *f = fopen("phonebook.dat", "w+b");
    char *email;
    printf("\nEnter email: ");
    scanf("%s", email);
    TreeType *result = Search(email, root);
    if (result)
    {
        printf("\nFound email: %s", email);
        fwrite(result, sizeof(phoneaddress), n, fp);
    }
    else
    {
        printf("\nNot found %s", email);
    }

    // Output all the data stored in the binary tree in ascending order for the e-mail address
    in_order_display(root);
    return 0;
}
