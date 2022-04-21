#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LEN 100

int main()
{
    int choice;
    FILE *f1, *f2;
    if ((f1 = fopen("copy-text.txt", "r")) == NULL)
    {
        printf("\nCannot open copy-text.txt");
        return 1;
    }
    for (;;)
    {
        clock_t start, end;
        double time_spent;
        rewind(f1);

        printf("\n1. Copy by character");
        printf("\n2. Copy by line");
        printf("\n3. Copy by block - optional size");
        printf("\n4. Quit");
        printf("\nLua chon (1~4): ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            if ((f2 = fopen("copy-text-1.txt", "w")) == NULL)
            {
                printf("\nCannot open copy-text-1.txt");
                return 1;
            }
            start = clock();
            char c = '\0';
            while ((c = fgetc(f1)) != EOF)
            {
                fputc(c, f2);
            }
            end = clock();
            time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("\nTime spent: %f", time_spent);
            fclose(f2);
            break;
        case 2:
            if ((f2 = fopen("copy-text-2.txt", "w")) == NULL)
            {
                printf("\nCannot open copy-text-2.txt");
                return 1;
            }
            start = clock();
            char buff2[MAX_LEN];
            while (fgets(buff2, MAX_LEN, f1) != NULL)
            {
                fputs(buff2, f2);
            }
            end = clock();
            time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("\nTime spent: %f", time_spent);
            fclose(f2);
            break;
        case 3:
            if ((f2 = fopen("copy-text-3.txt", "w")) == NULL)
            {
                printf("\nCannot open copy-text-3.txt");
                return 1;
            }
            start = clock();
            char buff[MAX_LEN];
            while (!feof(f1))
            {
                int num = fread(buff, sizeof(char), MAX_LEN, f1);
                buff[num * sizeof(char)] = '\0';
                fwrite(buff, sizeof(char), num, f2);
            }
            end = clock();
            time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("\nTime spent: %f", time_spent);
            fclose(f2);
            break;
        default:
            return 1;
        }
    }

    return 0;
}