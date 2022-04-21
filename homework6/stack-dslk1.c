#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <conio.h>
#define MAX_LEN 50

typedef struct student
{
    char name[MAX_LEN];
    char email[MAX_LEN];
    struct student *next;
} student;
student *first, *last;
