#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// blądy są przez to że visual studio myśłe że funckcje z jezyka C są niebezpeczne.
#define _CRT_SECURE_NO_WARNINGS

// dane
// 9 - sciana
// 3 - coin
/**/

/////
int level;
int i = 0;
int paused = 0;
int maxcoins = 0;
int** tab;
int** copytab;
int game = 1;
enum eDirection { STOP = 0, LEFT = 1, TOP = 2, RIGHT = 3, DOWN = 4 };
eDirection dir;
struct rozmiar
{
    int height;
    int width;
};
rozmiar map;

struct pacman
{
    int life = 2;
    int x = 1;
    int y = 1;
    int score = 0;
    int xa = 1;
    int yb = 1;
};
pacman pac;

struct monst1
{
    int x = 8;
    int y = 1;

    int point_l2 = 0;
    int point_w2 = 0;
    int point_l = 1;
    int point_w = 1;
    int kod = 1;
    int j = 1;
    int ak1 = 0;
    int bk1 = 0;
};
monst1 monstr1;

struct monst2
{
    int x = 1;
    int y = 8;

    int point_l2 = 0;
    int point_w2 = 0;
    int point_l = 1;
    int point_w = 1;
    int kod = 1;
    int j = 1;
    int ak3 = 0;
    int bk3 = 0;
};
monst2 monstr2;

struct follow
{
    int up = 0;
    int right = 0;
    int left = 0;
    int down = 0;

};

follow follow1;
follow follow2;

/////
void unpause()
{
    FILE* file;
    file = fopen("pause.txt", "r");
    fscanf(file, "%d", &pac.life);
    fscanf(file, "%d", &pac.x);
    fscanf(file, "%d", &pac.y);
    fscanf(file, "%d", &pac.score);
    fscanf(file, "%d", &maxcoins);
    fscanf(file, "%d", &map.height);
    fscanf(file, "%d", &map.width);
    fscanf(file, "%d", &monstr1.x);
    fscanf(file, "%d", &monstr1.y);
    fscanf(file, "%d", &monstr2.x);
    fscanf(file, "%d", &monstr2.y);

    /*
    tab = new int* [map.height];

    for (int i = 0; i < map.height; i++)
    {
        tab[i] = new int[map.width];
    }


    copytab = new int* [map.height];

    for (int i = 0; i < map.height; i++)
    {
        copytab[i] = new int[map.width];
    }
    */

    tab = (int**)malloc(map.height * sizeof(int*));
    for (int i = 0; i < map.height; i++)
    {
        tab[i] = (int*)malloc(map.width * sizeof(int));
    }

    copytab = (int**)malloc(map.height * sizeof(int*));
    for (int i = 0; i < map.height; i++)
    {
        copytab[i] = (int*)malloc(map.width * sizeof(int));
    }

    for (int i = 0; i < map.height; i = i + 1)
    {
        for (int j = 0; j < map.width; j = j + 1)
        {
            fscanf(file, "%d", &tab[i][j]);
        }
    }

    for (int i = 0; i < map.height; i = i + 1)
    {
        for (int j = 0; j < map.width; j = j + 1)
        {
            fscanf(file, "%d", &copytab[i][j]);
        }
    }




    fclose(file);
}

void repeat(int first, int* second)
{

    *second = first;
}

void pause()
{

    FILE* file;
    file = fopen("pause.txt", "w");
    //fprintf(file, "Game_paused\n");
    //fprintf(file, "Lifes:\n");
    fprintf(file, "%d\n", pac.life);
    fprintf(file, "%d\n", pac.x);
    fprintf(file, "%d\n", pac.y);
    //fprintf(file, "Score:\n");
    fprintf(file, "%d\n", pac.score);
    //fprintf(file, "MaxScore:\n");
    fprintf(file, "%d\n", maxcoins);
    //fprintf(file, "height:\n");
    fprintf(file, "%d\n", map.height);
    //fprintf(file, "width:\n");
    fprintf(file, "%d\n", map.width);
    //fprintf(file, "monstr1.x:\n");
    fprintf(file, "%d\n", monstr1.x);
    //fprintf(file, "monstr1.y:\n");
    fprintf(file, "%d\n", monstr1.y);
    //fprintf(file, "monstr2.x:\n");
    fprintf(file, "%d\n", monstr2.x);
    //fprintf(file, "monstr2.y:\n");
    fprintf(file, "%d\n", monstr2.y);

    //fprintf(file, "Karta\n");

    for (int i = 0; i < map.height; i = i + 1)
    {
        for (int j = 0; j < map.width; j = j + 1)
        {
            fprintf(file, "%d ", tab[i][j]);
        }
        fprintf(file, "\n");

    }

    //fprintf(file, "CopyKarta\n");

    for (int i = 0; i < map.height; i = i + 1)
    {
        for (int j = 0; j < map.width; j = j + 1)
        {
            fprintf(file, "%d ", copytab[i][j]);
        }
        fprintf(file, "\n");

    }
    fprintf(file, "\n");

    fclose(file);

    system("cls");

    printf("Game Paused\n");
    printf("Print 'p' to continue\n");
    printf("Print any to leave\n");
    char a,b;
    scanf("%c", &a);
    scanf("%c", &b);
    if (b == 'p')
    {
        unpause();
    }
    else
    {
        game = 0;
    }

    


 

}

void statistic()
{

    FILE* file;
    file = fopen("Statistic.txt", "w");
    fprintf(file, "Lifes:\n");
    fprintf(file, "%d\n", pac.life);
    fprintf(file, "Koordynaty:\n");
    fprintf(file, "%d\n", pac.x);
    fprintf(file, "%d\n", pac.y);
    fprintf(file, "Score:\n");
    fprintf(file, "%d\n", pac.score);
    fprintf(file, "MaxScore:\n");
    fprintf(file, "%d\n", maxcoins);
    fprintf(file, "height:\n");
    fprintf(file, "%d\n", map.height);
    fprintf(file, "width:\n");
    fprintf(file, "%d\n", map.width);
    fprintf(file, "monstr1.x:\n");
    fprintf(file, "%d\n", monstr1.x);
    fprintf(file, "monstr1.y:\n");
    fprintf(file, "%d\n", monstr1.y);
    fprintf(file, "monstr2.x:\n");
    fprintf(file, "%d\n", monstr2.x);
    fprintf(file, "monstr2.y:\n");
    fprintf(file, "%d\n", monstr2.y);

    fprintf(file, "Karta\n");

    for (int i = 0; i < map.height; i = i + 1)
    {
        for (int j = 0; j < map.width; j = j + 1)
        {
            fprintf(file, "%d ", tab[i][j]);
        }
        fprintf(file, "\n");

    }

    fprintf(file, "CopyKarta\n");

    for (int i = 0; i < map.height; i = i + 1)
    {
        for (int j = 0; j < map.width; j = j + 1)
        {
            fprintf(file, "%d ", copytab[i][j]);
        }
        fprintf(file, "\n");

    }
    fprintf(file, "\n");

    fclose(file);


}

void start()
{
    printf("Choose difficulty level(-1,0,1,2,3)\n");
    printf("Level -1: continue pause\n");
    printf("Level 1: 10x10\n");
    printf("Level 2: 15x15\n");
    printf("Level 3: 25x25\n");
    printf("Level 0: where you choose size\n");
    printf(" '-1' : continue pause\n");
    printf("Your level: ");
    scanf_s("%d", &level);

    if (level == 1)
    {
        map.height = 10;
        map.width = 10;

    }
    else if (level == 2)
    {
        map.height = 15;
        map.width = 15;
    }
    else if (level == 3)
    {
        map.height = 27;
        map.width = 28;
    }
    else if (level == 0)
    {
        printf("Choose height (from 10 to 30): ");
        scanf_s("%d", &map.height);

        printf("Choose width (from 10 to 30): ");
        scanf_s("%d", &map.width);

        if (map.height > 30 || map.height < 10 || map.width >30 || map.height < 10)
        {
            printf("Choose width from 10 to 30 and height from 10 to 30 \n");
            start();

        }

    }
    else if (level == -1)
    {
        paused = 1;
        unpause();
    }
    else
    {
        printf("Eror!");
        start();
    }

    if (paused == 0)
    {

        //tablica dynamiczna
        /*
        tab = new int* [map.height];

        for (int i = 0; i < map.height; i++)
        {
            tab[i] = new int[map.width];
        }
        */

        tab = (int**)malloc(map.height * sizeof(int*));
        for (int i = 0; i < map.height; i++)
        {
            tab[i] = (int*)malloc(map.width * sizeof(int));
        }



        for (int i = 0; i < map.height; i++)
        {
            for (int j = 0; j < map.width; j++)
            {
                tab[i][0] = 9;
                tab[0][j] = 9;
                tab[i][map.width - 1] = 9;
                tab[map.height - 1][j] = 9;
            }
        }
    }
}

void karta10()
{


    tab[2][2] = 9;
    tab[3][2] = 9;
    tab[2][3] = 9;
    tab[3][3] = 9;

    tab[2][7] = 9;
    tab[3][7] = 9;
    tab[2][6] = 9;
    tab[3][6] = 9;

    tab[6][7] = 9;
    tab[7][7] = 9;
    tab[6][6] = 9;
    tab[7][6] = 9;

    tab[6][2] = 9;
    tab[7][2] = 9;
    tab[6][3] = 9;
    tab[7][3] = 9;

    tab[4][4] = 9;
    tab[4][5] = 9;
    tab[5][4] = 9;
    tab[5][5] = 9;

}

void karta20()
{
    tab[2][2] = 9;
    tab[3][2] = 9;
    tab[2][3] = 9;
    tab[3][3] = 9;

    tab[2][11] = 9;
    tab[3][11] = 9;
    tab[2][12] = 9;
    tab[3][12] = 9;

    tab[11][2] = 9;
    tab[12][2] = 9;
    tab[11][3] = 9;
    tab[12][3] = 9;

    tab[11][11] = 9;
    tab[12][11] = 9;
    tab[11][12] = 9;
    tab[12][12] = 9;

    for (int i = 2; i <= 5; i++)
    {
        tab[5][i] = 9;
    }

    for (int i = 2; i <= 5; i++)
    {
        tab[i][5] = 9;
    }

    for (int i = 2; i <= 12; i++)
    {
        tab[i][7] = 9;
    }


    for (int i = 2; i <= 12; i++)
    {
        tab[7][i] = 9;
    }

    for (int i = 2; i <= 5; i++)
    {
        tab[9][i] = 9;
        tab[i][9] = 9;
    }

    for (int i = 9; i <= 12; i++)
    {
        tab[9][i] = 9;
        tab[5][i] = 9;
    }

    for (int i = 9; i <= 12; i++)
    {
        tab[i][5] = 9;
        tab[i][9] = 9;
    }

}

void karta30()
{

    for (int i = 2; i <= 3; i++)
    {
        for (int j = 2; j <= 5; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 2; i <= 3; i++)
    {
        for (int j = 7; j <= 11; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 5; i <= 6; i++)
    {
        for (int j = 2; j <= 5; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 8; i <= 12; i++)
    {
        for (int j = 1; j <= 5; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 14; i <= 18; i++)
    {
        for (int j = 1; j <= 5; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 1; i <= 3; i++)
    {
        for (int j = 13; j <= 14; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 2; i <= 3; i++)
    {
        for (int j = 16; j <= 20; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 2; i <= 3; i++)
    {
        for (int j = 22; j <= 25; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 20; i <= 21; i++)
    {
        for (int j = 2; j <= 5; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 23; i <= 24; i++)
    {
        for (int j = 2; j <= 5; j++)
        {
            tab[i][j] = 9;
        }
    }


    for (int i = 23; i <= 24; i++)
    {
        for (int j = 16; j <= 20; j++)
        {
            tab[i][j] = 9;
        }
    }


    for (int i = 23; i <= 25; i++)
    {
        for (int j = 13; j <= 14; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 23; i <= 24; i++)
    {
        for (int j = 22; j <= 25; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 23; i <= 24; i++)
    {
        for (int j = 7; j <= 11; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 8; i <= 12; i++)
    {
        for (int j = 22; j <= 26; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 14; i <= 18; i++)
    {
        for (int j = 22; j <= 26; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 5; i <= 6; i++)
    {
        for (int j = 22; j <= 25; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 20; i <= 21; i++)
    {
        for (int j = 22; j <= 25; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 5; i <= 12; i++)
    {
        for (int j = 7; j <= 8; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 14; i <= 21; i++)
    {
        for (int j = 7; j <= 8; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 5; i <= 12; i++)
    {
        for (int j = 19; j <= 20; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 14; i <= 21; i++)
    {
        for (int j = 19; j <= 20; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 5; i <= 6; i++)
    {
        for (int j = 10; j <= 17; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 20; i <= 21; i++)
    {
        for (int j = 10; j <= 17; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 16; i <= 21; i++)
    {
        for (int j = 13; j <= 14; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 6; i <= 10; i++)
    {
        for (int j = 13; j <= 14; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 8; i <= 10; i++)
    {
        for (int j = 9; j <= 11; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 8; i <= 10; i++)
    {
        for (int j = 16; j <= 18; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 16; i <= 18; i++)
    {
        for (int j = 9; j <= 11; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 16; i <= 18; i++)
    {
        for (int j = 16; j <= 18; j++)
        {
            tab[i][j] = 9;
        }
    }


    for (int i = 12; i <= 12; i++)
    {
        for (int j = 10; j <= 17; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int i = 14; i <= 14; i++)
    {
        for (int j = 10; j <= 17; j++)
        {
            tab[i][j] = 9;
        }
    }

    for (int j = 10; j <= 17; j++)
    {
        tab[13][j] = 9;
    }



}

void kartaXY()
{
    for (int i = 2; i < map.height - 1; i = i + 2)
    {
        for (int j = 2; j < map.width - 1; j = j + 2)
        {
            tab[i][j] = 9;
        }
    }
}

void coins()
{
    for (int i = 0; i < map.height; i++)
    {
        for (int j = 0; j < map.width; j++)
        {
            if (tab[i][j] != 9)
            {
                tab[i][j] = 3;
                maxcoins++;
            }
        }
    }
}

void copy()
{
    /*
    copytab = new int* [map.height];
    for (int i = 0; i < map.height; i++)
    {
        copytab[i] = new int[map.width];
    }
    */

    copytab = (int**)malloc(map.height * sizeof(int*));
    for (int i = 0; i < map.height; i++)
    {
        copytab[i] = (int*)malloc(map.width * sizeof(int));
    }

    for (int i = 0; i < map.height; i = i + 1)
    {
        for (int j = 0; j < map.width; j = j + 1)
        {
            copytab[i][j] = tab[i][j];
        }
    }

}

void karta()
{

    if (level == 1)
    {
        karta10();
    }
    else if (level == 2)
    {
        karta20();
    }
    else if (level == 3)
    {
        karta30();
    }
    else if (level == 0)
    {
        kartaXY();
    }
}

void output()
{
    system("cls"); // "clear"
    for (int i = 0; i < map.height; i++)
    {
        for (int j = 0; j < map.width; j++)
        {
            if (tab[i][j] == 9)
            {
                printf("#");//sciana
            }
            else if (tab[i][j] == 5)
            {
                printf("@");//pac-man
            }
            else if (tab[i][j] == 3)
            {
                printf(".");//jedzenie
            }
            else if (tab[i][j] == -1)
            {
                printf("X");//przeciwniki
            }
            else if (tab[i][j] == -2)
            {
                printf("x");//przeciwniki male
            }
            else if (tab[i][j] == -10)
            {
                printf("0");//super jedzenie
            }
            else
            {
                printf(" ");
            }

        }
        printf("\n");
    }

    printf("Your score is ");
    printf("%d\n", pac.score);

    printf("Lives - ");
    printf("%d\n", pac.life);
    printf("'p' - to pause\n");

}

void input()
{

    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'w':
            dir = TOP;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'p':
            pause();
            break;
        case 'k':
            pac.life = 0;
            break;
        }
    }

}

void logic()
{
    repeat(pac.x, &pac.xa);
    repeat(pac.y, &pac.yb);
    //pac.xa = pac.x;
    //pac.yb = pac.y;

    //urachomiamy pac-man
    switch (dir)
    {
    case LEFT:
        pac.x--;
        break;

    case RIGHT:
        pac.x++;
        break;

    case DOWN:
        pac.y++;
        break;

    case TOP:
        pac.y--;
        break;
    case STOP:
        break;
    }

    if (tab[pac.y][pac.x] == 9)
    {
        pac.y = pac.yb;
        pac.x = pac.xa;
    }

    if (tab[pac.y][pac.x] == 3)
    {
        pac.score++;

        copytab[pac.y][pac.x] = 0;
    }

    tab[pac.yb][pac.xa] = 0;
    tab[pac.y][pac.x] = 5;
}

void check()
{

    if (pac.score == maxcoins)
    {
        pac.score++;
        coins();

        for (int i = 0; i < map.height; i = i + 1)
        {
            for (int j = 0; j < map.width; j = j + 1)
            {
                copytab[i][j] = tab[i][j];
            }
        }

    }




    if (pac.x == monstr1.x && pac.y == monstr1.y)
    {

        for (int i = 0; i < map.height; i = i++)
        {
            for (int j = 0; j < map.width; j = j++)
            {

                if (tab[i][j] == -1 && copytab[i][j] == 3)
                {
                    tab[i][j] = 3;
                }
                else if (tab[i][j] == -1)
                {
                    tab[i][j] = 0;
                }

                if (tab[i][j] == 5)
                {
                    tab[i][j] = 0;
                }
            }
        }
        Sleep(1000);
        pac.life--;
        pac.x = 1;
        pac.y = 1;
        monstr1.x = 8;
        monstr1.y = 1;
        monstr2.x = 1;
        monstr2.y = 8;
        Sleep(1000);
    }

    if (pac.x == monstr2.x && pac.y == monstr2.y)
    {
        for (int i = 0; i < map.height; i = i++)
        {
            for (int j = 0; j < map.width; j = j++)
            {

                if (tab[i][j] == -1 && copytab[i][j] == 3)
                {
                    tab[i][j] = 3;
                }
                else if (tab[i][j] == -1)
                {
                    tab[i][j] = 0;
                }

                if (tab[i][j] == 5)
                {
                    tab[i][j] = 0;
                }

            }
        }
        Sleep(1000);
        pac.life--;
        pac.x = 1;
        pac.y = 1;
        monstr1.x = 5;
        monstr1.y = 1;
        monstr2.x = 1;
        monstr2.y = 5;
        i = 0;
        Sleep(1000);
    }
}

void monstrik1()
{

    //kopiujemy koordynaty
    //int ak1 = monstr1.x;
    //int bk1 = monstr1.y;
    repeat(monstr1.x, &monstr1.ak1);
    repeat(monstr1.y, &monstr1.bk1);


    // część dla x
    if (monstr1.j % 2 == 0) {

        if (monstr1.kod == 1) {
            monstr1.point_l = rand() % 2;
            monstr1.point_l2 = monstr1.point_l;
        }

        if (monstr1.kod == 0)
        {
            monstr1.point_l = monstr1.point_l2;
        }

        monstr1.point_w2 = 1 - monstr1.point_w2;


        if (monstr1.point_l == 0)
        {
            monstr1.x++;
        }

        if (monstr1.point_l == 1)
        {
            monstr1.x--;
        }


        monstr1.kod = 1;

    }

    // część dla y
    if (monstr1.j % 2 == 1)
    {

        if (monstr1.kod == 1) {
            monstr1.point_w = rand() % 2;
            monstr1.point_w2 = monstr1.point_w;
        }

        if (monstr1.kod == 0)
        {
            monstr1.point_w = monstr1.point_w2;
        }

        monstr1.point_l2 = 1 - monstr1.point_l2;

        if (monstr1.point_w == 0)
        {
            monstr1.y++;
        }

        if (monstr1.point_w == 1)
        {
            monstr1.y--;
        }


    }

    monstr1.j++;
    // spawdziamy nie idzie w scianu
    if (tab[monstr1.y][monstr1.x] == 9)
    {
        monstr1.x = monstr1.ak1;
        monstr1.y = monstr1.bk1;
        monstr1.kod = 0;
        monstr1.point_w2 = 1 - monstr1.point_w2;
        monstr1.point_l2 = 1 - monstr1.point_l2;
    }

    if (copytab[monstr1.bk1][monstr1.ak1] == 3)
    {
        tab[monstr1.bk1][monstr1.ak1] = 3;
    }
    else
    {
        tab[monstr1.bk1][monstr1.ak1] = 0;
    }

    tab[monstr1.y][monstr1.x] = -1;
}

void monstrik2()
{

    //kopiujemy koordynaty
    //int ak3 = monstr2.x;
    //int bk3 = monstr2.y;

    repeat(monstr2.x, &monstr2.ak3);
    repeat(monstr2.y, &monstr2.bk3);


    // część dla x
    if (monstr2.j % 2 == 0) {

        if (monstr2.kod == 1) {
            monstr2.point_l = rand() % 2;
            monstr2.point_l2 = monstr2.point_l;
        }

        if (monstr2.kod == 0)
        {
            monstr2.point_l = monstr2.point_l2;
        }

        monstr2.point_w2 = 1 - monstr2.point_w2;


        if (monstr2.point_l == 0)
        {
            monstr2.x++;
        }

        if (monstr2.point_l == 1)
        {
            monstr2.x--;
        }


        monstr2.kod = 1;

    }

    // część dla y
    if (monstr2.j % 2 == 1)
    {

        if (monstr2.kod == 1) {
            monstr2.point_w = rand() % 2;
            monstr2.point_w2 = monstr2.point_w;
        }

        if (monstr2.kod == 0)
        {
            monstr2.point_w = monstr2.point_w2;
        }

        monstr2.point_l2 = 1 - monstr2.point_l2;

        if (monstr2.point_w == 0)
        {
            monstr2.y++;
        }

        if (monstr2.point_w == 1)
        {
            monstr2.y--;
        }


    }

    monstr2.j++;
    // spawdziamy nie idzie w scianu
    if (tab[monstr2.y][monstr2.x] == 9)
    {
        monstr2.x = monstr2.ak3;
        monstr2.y = monstr2.bk3;
        monstr2.kod = 0;
        monstr2.point_w2 = 1 - monstr2.point_w2;
        monstr2.point_l2 = 1 - monstr2.point_l2;
    }

    if (copytab[monstr2.bk3][monstr2.ak3] == 3)
    {
        tab[monstr2.bk3][monstr2.ak3] = 3;
    }
    else
    {
        tab[monstr2.bk3][monstr2.ak3] = 0;
    }

    tab[monstr2.y][monstr2.x] = -1;
}

void monstrik1_catch()
{

    repeat(monstr1.x, &monstr1.ak1);
    repeat(monstr1.y, &monstr1.bk1);

    if (tab[monstr1.y][monstr1.x - 1] != 9)
    {
        follow1.left = pac.x - monstr1.x - 1;
        if (follow1.left < 0)
        {
            follow1.left *= -1;
        }
    }
    else
    {
        follow1.left = -1;
    }

    if (tab[monstr1.y][monstr1.x + 1] != 9)
    {
        follow1.right = pac.x - monstr1.x + 1;
        if (follow1.right < 0)
        {
            follow1.right *= -1;
        }
    }
    else
    {
        follow1.right = -1;
    }

    if (tab[monstr1.y + 1][monstr1.x] != 9)
    {
        follow1.down = pac.y - monstr1.y + 1;
        if (follow1.down < 0)
        {
            follow1.down *= -1;
        }
    }
    else
    {
        follow1.down = -1;
    }

    if (tab[monstr1.y - 1][monstr1.x] != 9)
    {
        follow1.up = pac.y - monstr1.y - 1;
        if (follow1.up < 0)
        {
            follow1.up *= -1;
        }
    }
    else
    {
        follow1.up = -1;
    }

    int max = follow1.left;
    if (max < follow1.right)
    {
        max = follow1.right;
    }

    if (max < follow1.down)
    {
        max = follow1.down;
    }

    if (max < follow1.up)
    {
        max = follow1.up;
    }

    if (max == follow1.left && follow1.left != 999)
    {
        monstr1.x--;
    }
    else if (max == follow1.right && follow1.right != 999)
    {
        monstr1.x++;
    }
    else if (max == follow1.down && follow1.down != 999)
    {
        monstr1.y++;
    }
    else if (max == follow1.up && follow1.up != 999)
    {
        monstr1.y--;
    }



    if (copytab[monstr1.bk1][monstr1.ak1] == 3)
    {
        tab[monstr1.bk1][monstr1.ak1] = 3;
    }
    else
    {
        tab[monstr1.bk1][monstr1.ak1] = 0;
    }


    tab[monstr1.y][monstr1.x] = -1;

    //tab[monstr2.y][monstr2.x] = -1;

}

void monstrik2_catch()
{

    repeat(monstr2.x, &monstr2.ak3);
    repeat(monstr2.y, &monstr2.bk3);

    if (tab[monstr2.y][monstr2.x - 1] != 9)
    {
        follow2.left = pac.x - monstr2.x - 1;
        if (follow2.left < 0)
        {
            follow2.left *= -1;
        }
    }
    else
    {
        follow2.left = -1;
    }

    if (tab[monstr2.y][monstr2.x + 1] != 9)
    {
        follow2.right = pac.x - monstr2.x + 1;
        if (follow2.right < 0)
        {
            follow2.right *= -1;
        }
    }
    else
    {
        follow2.right = -1;
    }

    if (tab[monstr2.y + 1][monstr2.x] != 9)
    {
        follow2.down = pac.y - monstr2.y + 1;
        if (follow2.down < 0)
        {
            follow2.down *= -1;
        }
    }
    else
    {
        follow2.down = -1;
    }


    if (tab[monstr2.y - 1][monstr2.x] != 9)
    {
        follow2.up = pac.y - monstr2.y - 1;
        if (follow2.up < 0)
        {
            follow2.up *= -1;
        }
    }
    else
    {
        follow2.up = -1;
    }

    int max = follow2.left;
    if (max < follow2.right)
    {
        max = follow2.right;
    }

    if (max < follow2.down)
    {
        max = follow2.down;
    }

    if (max < follow2.up)
    {
        max = follow2.up;
    }

    if (max == follow2.left && follow2.left != 999)
    {
        monstr2.x--;
    }
    else if (max == follow2.right && follow2.right != 999)
    {
        monstr2.x++;
    }
    else if (max == follow2.down && follow2.down != 999)
    {
        monstr2.y++;
    }
    else if (max == follow2.up && follow2.up != 999)
    {
        monstr2.y--;
    }



    if (copytab[monstr2.bk3][monstr2.ak3] == 3)
    {
        tab[monstr2.bk3][monstr2.ak3] = 3;
    }
    else
    {
        tab[monstr2.bk3][monstr2.ak3] = 0;
    }

    tab[monstr2.y][monstr2.x] = -1;

}



int main()
{
    start();

    if (paused == 0)
    {
        karta();
        coins();
        copy();
    }
    Sleep(1000);
    while (pac.life > 0 && game == 1)
    {
        input();
        check();

        if (i <= 10)
        {
            monstrik1();
            monstrik2();
        }
        else
        {
            monstrik1_catch();
            monstrik2_catch();
        }

        if (i >= 20)
        {
            i = 1;
        }
        i++;

        check();
        logic();
        output();
        Sleep(200);
        statistic();
    }
    Sleep(100);
    system("cls"); // "clear"
    printf("Your score is ");
    printf("%d", pac.score);

    free(*tab);
    free(*copytab);

    return 0;
}



