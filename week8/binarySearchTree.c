#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Cài đặt Binary Search Tree
typedef int KeyType; // Loại dữ liệu của Key
typedef struct Node
{
    KeyType key;
    struct Node *left, *right;
} TreeType;

// Tìm kiếm trên BST
TreeType *Search(KeyType x, TreeType *r)
{
    if (r == NULL)
        return NULL;
    else if (r->key == x)
        return r;
    else if (r->key < x)
    {
        return Search(x, r->right);
    }
    else
        return Search(x, r->left);
}

// Chèn một nút vào BST
void InsertNode(KeyType x, TreeType **Root)
{
    TreeType *temp = NULL;
    if (!(*Root))
    {
        temp = (TreeType *)malloc(sizeof(TreeType));
        temp->left = temp->right = NULL;
        temp->key = x;
        *Root = temp;
        return;
    }

    if (x < (*Root)->key)
    {
        InsertNode(x, &(*Root)->left);
    }
    else if (x > (*Root)->key)
    {
        InsertNode(x, &(*Root)->right);
    }
}

// Xóa một nút khỏi BST

KeyType DeleteMin(TreeType **Root)
{
    KeyType k;
    if ((*Root)->left == NULL)
    {
        k = (*Root)->key;
        (*Root) = (*Root)->right;
        return k;
    }
    else
        return DeleteMin(&(*Root)->left);
}

void DeleteNode(KeyType X, TreeType **Root)
{
    if (*Root != NULL)
    {
        if (X < (*Root)->key)
        {
            DeleteNode(X, &(*Root)->left);
        }
        else if (X > (*Root)->key)
            DeleteNode(X, &(*Root)->right);
        else if (((*Root)->left == NULL) && ((*Root)->right == NULL))
            *Root = NULL;
        else if ((*Root)->left == NULL)
            *Root = (*Root)->right;
        else if ((*Root)->right == NULL)
            *Root = (*Root)->left;
        else
            (*Root)->key = DeleteMin(&(*Root)->right);
    }
}
// Duyệt cây
void pre_order_display(TreeType *r)
{
    if (r == NULL)
        return;
    printf("%d ", r->key);
    pre_order_display(r->left);
    pre_order_display(r->right);
}

void in_order_display(TreeType *r)
{
    if (r == NULL)
        return;
    in_order_display(r->left);
    printf("%d ", r->key);
    in_order_display(r->right);
}

void post_order_display(TreeType *r)
{
    if (r == NULL)
        return;
    post_order_display(r->left);
    post_order_display(r->right);
    printf("%d ", r->key);
}

void freeTree(TreeType *r)
{
    if (r != NULL)
    {
        freeTree(r->left);
        freeTree(r->right);
        free(r);
    }
}

int main()
{
    TreeType *Root = NULL;
    printf("\nTao 10 node random");
    srand(time(0));
    for (int i = 0; i < 10; ++i)
    {
        int r = rand() % 50;
        printf("\nDa insert : %d ", r);
        InsertNode(r, &Root);
    }

    int choice;
    while (1)
    {
        printf("\n--------------------------------");
        printf("\n1.Pre-order Display:\n2.In-order Display\n3.Post-order Display\n4.Search\n5.Delete\n6.Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            pre_order_display(Root);
            break;
        case 2:
            in_order_display(Root);
            break;
        case 3:
            post_order_display(Root);
            break;
        case 4:
            printf("\nEnter node: ");
            int a;
            scanf("%d", &a);
            TreeType *result = Search(a, Root);
            if (result)
            {
                printf("\nFound: %d", result->key);
            }
            else
                printf("\nNot found");
            break;
        case 5:
            printf("\nEnter node: ");
            int b;
            scanf("%d", &b);
            DeleteNode(b, &Root);
            break;
        case 6:
            goto end;
        default:
            goto end;
            break;
        }
    }

end:
    freeTree(Root);
}
