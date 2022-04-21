#include <stdio.h>
#define Al_Length 26

int main(void)
{
    int count[Al_Length] = {0};
    printf("\nNhap chuoi ky tu: ");
    char c = '\0';
    c = getchar();

    while (c != '\n' && c > 0)
    {
        if (c >= 'a' && c <= 'z')
            count[c - 'a']++;
        if (c >= 'A' && c <= 'Z')
            count[c - 'A']++;
        c = getchar();
    }

    for (int i = 0; i < Al_Length; ++i)
    {
        if (count[i] > 0)
        {
            printf("\nChu '%c' xuat hien %d lan!!", i + 'a', count[i]);
        }
    }
    return 0;
}