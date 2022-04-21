#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct Ball
{
    char name[40];
    int id;
    int score;
    int win_goal;
    int lost_goal;
    struct Ball *next;
} Ball;

typedef struct Round
{
    int *list;
} Round;
Round *r;

Ball *first = NULL;
int N;

Ball *makeNode(char *name, int id, int score, int win_goal, int lost_goal)
{
    Ball *node = (Ball *)malloc(sizeof(Ball));
    strcpy(node->name, name);
    node->score = score;
    node->id = id;
    node->win_goal = win_goal;
    node->lost_goal = lost_goal;
    node->next = NULL;
    return node;
}

void insertFirst(char *name, int id, int score, int win_goal, int lost_goal)
{
    if (first == NULL)
    {
        first = makeNode(name, id, score, win_goal, lost_goal);
    }
    else
    {
        Ball *newNode = makeNode(name, id, score, win_goal, lost_goal);
        newNode->next = first;
        first = newNode;
    }
}

Ball *findById(int id)
{
    Ball *p = first;
    for (; p != NULL; p = p->next)
    {
        if (p->id == id)
            return p;
    }
    return NULL;
}

void loadFile(char *fileName)
{
    FILE *f = fopen(fileName, "r");
    if (f == NULL)
    {
        printf("file not found\n");
        exit(0);
    }

    fscanf(f, "%d", &N);

    for (int i = 0; i < N; ++i)
    {
        int id;
        fscanf(f, "%d", &id);
        char name[40];
        fgets(name, 40, f);
        name[strlen(name) - 1] = '\0';
        insertFirst(name, id, 0, 0, 0);
    }

    r = (Round *)malloc((N) * sizeof(Round));

    for (int i = 1; i <= N - 1; ++i)
    {
        char buff[100];
        int c;
        char d;
        fscanf(f, "%s %d%c", buff, &c, &d);
        r[i].list = (int *)malloc((N + 1) * sizeof(int));
        for (int k = 1; k <= N; ++k)
        {
            r[i].list[k] = 0;
        }
        for (int j = 1; j <= N / 2; ++j)
        {
            int l, right;
            fscanf(f, "%d\t%d%c", &l, &right);
            r[i].list[l] = right;
        }
    }

    fclose(f);
}

void printBXH(Ball *team)
{
    if (team == NULL)
        return;
    printBXH(team->next);
    printf("\n%-10d%-20s%-10d%-10d%-10d", team->id, team->name, team->score, team->win_goal, team->lost_goal);
}

void printRound()
{
    for (int i = 1; i <= N - 1; ++i)
    {
        printf("\nVong %d", i);
        for (int j = 1; j < N; ++j)
        {
            if (r[i].list[j] != 0)
            {
                printf("\n%s - %s", findById(j)->name, findById(r[i].list[j])->name);
            }
        }
    }
}

void updateResult()
{
    for (int i = 1; i <= N - 1; ++i)
    {
        printf("\nVong %d", i);
        for (int j = 1; j < N; ++j)
        {
            if (r[i].list[j] != 0)
            {
                Ball *left = findById(j);
                Ball *right = findById(r[i].list[j]);
                printf("\n%s - %s: ", left->name, right->name);
                printf("\n%s: ", left->name);
                int l_score;
                scanf("%d", &l_score);
                printf("\n%s: ", right->name);
                int r_score;
                scanf("%d", &r_score);

                left->win_goal += l_score;
                left->lost_goal += r_score;
                right->win_goal += r_score;
                right->lost_goal += l_score;

                if (l_score > r_score)
                {
                    left->score += 3;
                }
                else if (l_score < r_score)
                {
                    right->score += 3;
                }
                else
                {
                    left->score += 1;
                    right->score += 1;
                }
            }
        }
    }
    printf("\n%-10s%-20s%-10s%-10s%-10s", "Id", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
    printBXH(first);
}

void removeTeamById(int id)
{
    if (first == NULL)
        printf("\nList empty!!");
    else
    {
        Ball *p = first;
        Ball *prev = NULL;
        while (p != NULL && p->id != id)
        {
            prev = p;
            p = p->next;
        }
        if (p == NULL)
        {
            printf("NOT FOUND Team %s\n", p->name);
        }
        else if (p == first)
        {
            first = first->next;
            free(p);
        }
        else
        {
            prev->next = p->next;
            free(p);
        }
    }
}

void thongke(Ball *f)
{
    int min = 100000;
    for (int i = 1; i <= N; ++i)
    {
        min = (min < f->score) ? min : f->score;
        f = f->next;
    }

    Ball *p = first;

    printf("\nCac doi co diem thap nhat la:");
    printf("\n%-10s%-20s%-10s%-10s%-10s", "Id", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
    for (int i = 1; i <= N; ++i)
    {
        if (p->score == min)
        {
            printf("\n%-10d%-20s%-10d%-10d%-10d", p->id, p->name, p->score, p->win_goal, p->lost_goal);
            removeTeamById(p->id);
        }
        p = p->next;
    }

    printf("\nCac doi con lai la:");
    printf("\n%-10s%-20s%-10s%-10s%-10s", "Id", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
    printBXH(first);
}

int main()
{
    while (1)
    {
        system("cls");
        printf("\n1. In thong tin doi bong\n2. In thong tin lich thi dau\n3. Cap nhat ket qua vong dau\n4. Thong ke\n5. Thoat");
        printf("\nNhap lenh(1~5): ");
        char cmd[256];
        scanf("%s", cmd);
        if (strcmp(cmd, "5") == 0)
        {
            break;
        }
        else if (strcmp(cmd, "1") == 0)
        {
            loadFile("bongda.txt");
            printf("\n%-10s%-20s%-10s%-10s%-10s", "Id", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
            printBXH(first);
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
        }
        else if (strcmp(cmd, "2") == 0)
        {
            printRound();
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
        }
        else if (strcmp(cmd, "3") == 0)
        {
            updateResult();
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
        }
        else if (strcmp(cmd, "4") == 0)
        {
            thongke(first);
            printf("\nNhap phim bat ky de tiep tuc");
            getch();
        }
        else
            printf("\nInvalid");
    }
    return 0;
}
