#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Circle
{
    float x;
    float y;
    float radius;
    int *list;
} circle;

int check_2_circles(circle c1, circle c2)
{
    float x_dist = c1.x - c2.x;
    float y_dist = c1.y - c2.y;
    float sumRadius = c1.radius + c2.radius;
    float minusRadius = c1.radius - c2.radius;
    return x_dist * x_dist + y_dist * y_dist <= sumRadius * sumRadius &&
           x_dist * x_dist + y_dist * y_dist >= minusRadius * minusRadius;
}

void check_all_circles(circle *c, int size)
{
    int max = 0, pos = 0, circles = 0;
    for (int i = 0; i < size; ++i)
    {
        int count = 0, index = 0;
        for (int j = 0; j < size; ++j)
        {
            if (check_2_circles(c[i], c[j]))
            {
                count++;
                c[i].list[index] = j + 1;
                index++;
            }
        }
        if (max < count)
        {

            max = count;
            pos = i + 1;
            circles = index;
        }
    }

    //output
    printf("\nDuong tron giao voi nhieu duong tron khac nhat:");
    printf("\nDuong tron %d", pos);
    printf("\nTam: %3.2f %3.2f", c[pos - 1].x, c[pos - 1].y);
    printf("\nBan kinh: %3.2f", c[pos - 1].radius);
    printf("\nGiao voi %d duong tron khac, bao gom: ", max - 1);
    for (int i = 1; i < circles; ++i)
    {
        printf("%d ", c[pos - 1].list[i]);
    }
}

void input(circle *c, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("\nNhap thong tin ve duong tron %d: ", i + 1);
        printf("\nNhap toa do tam: ");
        scanf("%f %f", &c[i].x, &c[i].y);
        printf("\nNhap ban kinh:");
        scanf("%f", &c[i].radius);
        c[i].list = (int *)malloc(size * sizeof(int));
    }
}

void info(circle *c, int size)
{
    printf("\nThong tin ve cac duong tron:\n");
    for (int i = 0; i < size; i++)
    {
        printf("\nDuong tron %d", i + 1);
        printf("\nTam: %3.2f %3.2f", c[i].x, c[i].y);
        printf("\nBan kinh: %3.2f\n", c[i].radius);
    }
}

void randomCircles(circle *c, int size)
{
    srand((int)time(0));
    for (int i = 0; i < size; ++i)
    {
        int x = -5 + rand() % 10;
        int y = -5 + rand() % 10;
        int r = 1 + rand() % 10;
        c[i].x = x;
        c[i].y = y;
        c[i].radius = r;
        c[i].list = (int *)malloc(size * sizeof(int));
    }
}

int main()
{
    int n;
    printf("\nNhap so duong tron: ");
    scanf("%d", &n);
    circle *c = (circle *)malloc(n * sizeof(circle));

    int option;
    printf("\n1. nhap thu cong\n2. Sinh tu dong\nLua chon(1 or 2):");
    scanf("%d", &option);

    if (option == 1)
    {
        input(c, n);
        info(c, n);
        check_all_circles(c, n);
    }
    else if (option == 2)
    {
        randomCircles(c, n);
        info(c, n);
        check_all_circles(c, n);
    }
    return 0;
}