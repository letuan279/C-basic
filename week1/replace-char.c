#include <stdio.h>
#include <string.h>

void replace_char(char *str, char c1, char c2)
{
    for (int i = 0; i < strlen(str); ++i)
    {
        if (str[i] == c1)
        {
            str[i] = c2;
        }
    }
}

int main()
{
    char str[100], c1, c2;
    printf("Nhap chuoi bat ky: ");
    scanf("%s", str);
    printf("Nhap ky tu can doi: ");
    fflush(stdin);
    scanf("%c", &c1);
    printf("Nhap ky tu doi: ");
    fflush(stdin);
    scanf("%c", &c2);
    replace_char(str, c1, c2);
    printf("Ket qua: %s", str);
}