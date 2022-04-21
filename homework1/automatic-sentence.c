#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char article[5][100] = {"the", "a", "one", "some", "any"};
char noun[5][100] = {"boy", "girl", "dog", "town", "car"};
char verb[5][100] = {"drove", "jumped", "ran", "walked", "skipped"};
char pre[5][100] = {"to", "from", "over", "under", "on"};

void changeArtical()
{
    for (int i = 0; i < 5; ++i)
    {
        article[i][0] -= 32;
    }
}

int main()
{
    changeArtical();
    srand((int)time(0));
    for (int i = 0; i < 10; ++i)
    {
        int r1 = rand() % 5;
        int r2 = rand() % 5;
        int r3 = rand() % 5;
        int r4 = rand() % 5;
        printf("\n%s %s %s %s.", article[r1], noun[r2], verb[r3], pre[r4]);
    }
}