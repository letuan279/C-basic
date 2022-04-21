#include <stdio.h>
#include <stdlib.h>

void double_space(FILE *ifp, FILE *ofp)
{
    int c;
    while ((c = fgetc(ifp)) != EOF)
    {
        fputc(c, ofp);
        if (c == '\n')
            fputc('\n', ofp);
    }
}

int main(int argc, char **argv)
{
    FILE *ifp, *ofp;

    if (argc != 3)
    {
        printf("Wrong!!\nSYNTAX: ./double-line <file 1> <file 2>");
        return 1;
    }
    ifp = fopen(argv[1], "r");
    ofp = fopen(argv[2], "w");
    double_space(ifp, ofp);
    fclose(ifp);
    fclose(ofp);
    return 0;
}