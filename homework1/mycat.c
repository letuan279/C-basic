#include <stdio.h>
#include <string.h>

#define MAX_LINE 5

int main(int argc, char *argv[])
{
    FILE *f;
    if (argc != 2 && argc != 3)
    {
    error:
        printf("Wrong!!\nSYNTAX: .\\mycat.exe <file name> or .\\mycat.exe <file name> <-p>");
        return 1;
    }
    if (argc == 2)
    {
        if ((f = fopen("mycat.txt", "r")) == NULL)
        {
            printf("Cannot open %s.\n", "mycat.txt");
            return 1;
        }
        char c;
        while ((c = fgetc(f)) != EOF)
        {
            putchar(c);
        }
    }

    if (argc == 3)
    {
        if (strcmp(argv[2], "-p") != 0)
        {
            goto error;
        }
        if ((f = fopen("mycat.txt", "r")) == NULL)
        {
            printf("Cannot open %s.\n", "mycat.txt");
            return 1;
        }
        char buff[100];
        int count = 0;
        while ((fgets(buff, 100, f)) != NULL)
        {
            count++;
            if (count > MAX_LINE)
            {
                printf("\n");
                count -= MAX_LINE;
                getch();
            }
            printf("%s", buff);
        }
    }
    return 0;
}