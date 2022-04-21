#include <stdio.h>
#include <string.h>

void replace_letter(char str[], char replace_what, char replace_with)
{
    for (int i = 0; i < strlen(str); ++i)
    {
        if (str[i] == replace_what)
        {
            str[i] = replace_with;
        }
    }
}

int main()
{
    char str[100];
    char replace_what, replace_with;
    printf("\nNhap chuoi ky tu: ");
    scanf("%s", str);
    fflush(stdin);
    printf("\nNhap ky tu can thay doi: ");
    scanf("%c", &replace_what);
    fflush(stdin);
    printf("\nNhap ky tu thay doi: ");
    scanf("%c", &replace_with);
    replace_letter(str, replace_what, replace_with);
    printf("ket qua: %s", str);
}
