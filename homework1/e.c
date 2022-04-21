#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Wrong!!");
    }
    printf("%.3lf", exp(atoi(argv[1])));
}