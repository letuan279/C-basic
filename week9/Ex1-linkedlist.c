#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct phoneaddress_t
{
    char name[20];
    char tel[11];
    char email[25];
} phoneaddress;

typedef struct phoneaddress_linkedlist
{
    phoneaddress data;
    struct phoneaddress_linkedlist *next;
} phoneaddress_ll;

phoneaddress_ll *first = NULL;
phoneaddress_ll *sorted = NULL;
phoneaddress_ll *first2 = NULL;

phoneaddress_ll *makeAddress(char *name, char *tel, char *email)
{
    phoneaddress_ll *node = (phoneaddress_ll *)malloc(sizeof(phoneaddress_ll));
    strcpy(node->data.name, name);
    strcpy(node->data.email, email);
    strcpy(node->data.tel, tel);
    node->next = NULL;
    return node;
}

void insertFirst(phoneaddress_ll **first, char *name, char *tel, char *email)
{
    phoneaddress_ll *s = makeAddress(name, tel, email);
    s->next = *first;
    *first = s;
}

void processPrint(phoneaddress_ll *head)
{
    for (phoneaddress_ll *p = head; p != NULL; p = p->next)
        printf("Name: %-15s Tel: %-20s Email: %-10s\n", p->data.name, p->data.tel, p->data.email);
}

int count_insertion = 0;
int count_selection = 0;
void sortedInsert(phoneaddress_ll *newnode)
{
    if (sorted == NULL || strcmp(sorted->data.email, newnode->data.email) > 0)
    {
        newnode->next = sorted;
        sorted = newnode;
        count_insertion++;
    }
    else
    {
        phoneaddress_ll *cur = sorted;
        while (cur->next != NULL && strcmp(cur->next->data.email, newnode->data.email) < 0)
        {
            cur = cur->next;
            count_insertion++;
        }
        newnode->next = cur->next;
        cur->next = newnode;
    }
}

void insertion_sort()
{
    phoneaddress_ll *cur = first;
    while (cur != NULL)
    {
        phoneaddress_ll *next = cur->next;
        sortedInsert(cur);
        cur = next;
    }
    first = sorted;
}

void selection_sort()
{
    phoneaddress_ll *cur = first2;
    while (cur != NULL)
    {
        phoneaddress_ll *min = cur;
        phoneaddress_ll *r = cur->next;
        while (r != NULL)
        {
            if (strcmp(min->data.email, r->data.email) > 0)
                min = r;
            r = r->next;
            count_selection++;
        }
        phoneaddress tmp = cur->data;
        cur->data = min->data;
        min->data = tmp;

        cur = cur->next;
    }
}

int main()
{
    // Read data
    FILE *fp;
    phoneaddress phonearr[MAX];
    int i, n;
    n = 10;
    if ((fp = fopen("phonebook.dat", "rb")) == NULL)
    {
        printf("Can not open %s.\n", "phonebook.dat");
        return 1;
    }
    fread(phonearr, sizeof(phoneaddress), n, fp);

    // Import data to linked list
    for (i = 0; i < n; ++i)
    {
        insertFirst(&first, phonearr[i].name, phonearr[i].tel, phonearr[i].email);
    }
    processPrint(first);
    printf("\n--------------------------------\n");

    // Insertion sort
    insertion_sort();
    processPrint(first);

    // Selection sort
    printf("\n--------------------------------\n");
    for (i = 0; i < n; ++i)
    {
        insertFirst(&first2, phonearr[i].name, phonearr[i].tel, phonearr[i].email);
    }
    selection_sort();
    processPrint(first2);

    // Count
    printf("\ncount_insertion = %d", count_insertion);
    printf("\ncount_selection = %d", count_selection);

    fclose(fp);
}
