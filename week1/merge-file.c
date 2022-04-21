#include <stdio.h>
#define MAX_LEN 100

void LineMerge(FILE *f1, FILE *f2, FILE *f3)
{
    char buff1[MAX_LEN], buff2[MAX_LEN];
    while ((fgets(buff1, MAX_LEN, f1) != NULL) && (fgets(buff2, MAX_LEN, f2) != NULL))
    {
        fputs(buff1, f3);
        fputs(buff2, f3);
    }
    if (buff1 != NULL)
        fputs(buff1, f3);
    while (fgets(buff1, MAX_LEN, f1) != NULL)
    {
        fputs(buff1, f3);
    }
    if (buff2 != NULL)
        fputs(buff2, f3);

    while (fgets(buff2, MAX_LEN, f2) != NULL)
    {
        fputs(buff2, f3);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Wrong!!\nSYNTAX: ./merge-file.exe <file 1> <file 2> <file 3>");
    }
    FILE *f1, *f2, *f3;
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "r");
    f3 = fopen(argv[3], "w");
    LineMerge(f1, f2, f3);
    return 0;
}