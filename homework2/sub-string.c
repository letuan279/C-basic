#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 100

char *subStr(char *s, int offset, int number)
{
    char *result;
    result = (char *)malloc(number);
    for (int i = 0; i < number; ++i)
    {
        result[i] = s[offset];
        offset++;
    }
    result[number] = '\0';
    return result;
}

int main()
{
    char s[MAX_LEN];
    int offset, number;
    printf("\nNhap chuoi can tach: ");
    gets(s);
    fflush(stdin);
    do
    {
        printf("\nNhap offset: ");
        scanf("%d", &offset);
    } while (offset < 0 || offset > strlen(s));

    printf("\nNhap number: ");
    scanf("%d", &number);
    if (offset + number > strlen(s))
        number = strlen(s) - offset;

    printf("\nKet qua: %s", subStr(s, offset, number));
}