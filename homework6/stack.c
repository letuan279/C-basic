#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    char data;
    struct Node *next;
} Node;

Node *top;

Node *makeNode(char data)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = data;
    p->next = NULL;
    return p;
}

void initStack()
{
    top = NULL;
}

int isEmpty()
{
    return top == NULL;
}

void push(char data)
{
    Node *p = makeNode(data);
    p->next = top;
    top = p;
}

char pop()
{
    if (isEmpty())
        return ' ';
    char x = top->data;
    Node *tmp = top;
    top = top->next;
    free(tmp);
    return x;
}

int match(char a, char b)
{
    if (a == '(' && b == ')')
        return 1;
    if (a == '[' && b == ']')
        return 1;
    if (a == '{' && b == '}')
        return 1;
    return 0;
}

int check(char *s)
{
    initStack();
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
        {
            push(s[i]);
        }
        else
        {
            if (isEmpty())
                return 0;
            char x = pop();
            if (!match(x, s[i]))
                return 0;
        }
    }
    return isEmpty();
}

int main()
{
    printf("Enter input: ");
    char s[100];
    scanf("%s", s);
    char result[100];
    if (check(s))
    {
        strcpy(result, "Dung");
    }
    else
        strcpy(result, "Sai");
    printf("\nKet qua: %s", result);
}
