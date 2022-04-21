#include <stdio.h>
#include <stdlib.h>

int main()
{
    char input[100];
    int check = 0;
    printf("Nhap cau muon cat: ");
    char c = '\0';
    c = getchar();
    while (c != '\n' && c > 0)
    {
        if (c != ' ')
        {
            check = 0;
            printf("%c", c);
        }
        else
        {
            if (check == 0)
            {
                printf("\n");
                check = 1;
            }
        }
        c = getchar();
    }
}