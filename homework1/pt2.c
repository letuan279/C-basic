#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Wrong!!");
        return 1;
    }
    float a = atof(argv[1]);
    float b = atof(argv[2]);
    float c = atof(argv[3]);
    if (a == 0)
    {
        printf("Khong phai phuong trinh bac 2!");
    }
    else
    {
        int delta = b * b - 4 * a * c;
        if (delta > 0)
        {
            printf("x_1 = %.2f \nx_2 = %.2f", ((-b + sqrt(delta)) / (2 * a)), ((-b - sqrt(delta)) / (2 * a)));
        }
        else if (delta < 0)
        {
            printf("Vo nghiem!");
        }
        else
            printf("x_1 = x_2 = %.2f", -b / (2 * a));
    }
}