#define _CRT_SECURE_NO_WARNINGS
#define K 0.2
#include <iostream>

using namespace std;



struct player
{
    int X_Coord = -1;
    int Y_Coord = -1;
    int Hit_Points = -1;
    int Damage = -1;
};

struct enemy
{
    int X_Coord = -1;
    int Y_Coord = -1;
    int Hit_Points = -1;
    int Damage = -1;
};

struct game
{
    int Map_Size_X = 10;
    int Map_Size_Y = 10;
    char map[10][10] = 
    {   {'#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','#','#','#','#','#','#','#','#','#'}
    };
    player you;
    enemy monster;

};

void playerStepN(player* p)
{
    (*p).X_Coord -= 1;
}

void playerStepS(player* p)
{
    (*p).X_Coord += 1;
}

void playerStepW(player* p)
{
    (*p).Y_Coord -= 1;
}

void playerStepE(player* p)
{
    (*p).Y_Coord += 1;
}

void enemyStepN(enemy* p)
{
    (*p).X_Coord -= 1;
}

void enemyStepS(enemy* p)
{
    (*p).X_Coord += 1;
}

void enemyStepW(enemy* p)
{
    (*p).Y_Coord -= 1;
}

void enemyStepE(enemy* p)
{
    (*p).Y_Coord += 1;
}

void playerCoord(player* p, int* x, int* y)
{
    *x = (*p).X_Coord;
    *y = (*p).Y_Coord;
}

void enemyCoord(enemy* p, int* x, int* y)
{
    *x = (*p).X_Coord;
    *y = (*p).Y_Coord;
}

void enemyMovment(game *p)
{
    int play_x, play_y;
    int enem_x, enem_y;
    double x, y;
    int roundX, roundY;
    int fl = 1;
    playerCoord(&((*p).you), &play_x, &play_y);
    enemyCoord(&((*p).monster), &enem_x, &enem_y);
    x = enem_x;
    y = enem_y;
    do{
        
        double d = sqrt((x - play_x)*(x - play_x) + (y - play_y)*(y - play_y));
        x = (K * play_x + (d - K) * x) / d;
        y = (K * play_y + (d - K) * y) / d;
       
        roundX = round(x);
        roundY = round(y);
        if ((*p).map[roundX][roundY] == '#')
            fl = 0;

    }while ((roundX != play_x || roundY != play_y) && fl);
    if (fl)
    {
        if (abs(enem_x - play_x) > abs(enem_y - play_y))
        {
            if((*p).map[enem_x + 1][enem_y] != '#' && enem_x < play_x)
                enemyStepS(&((*p).monster));
            else
                if ((*p).map[enem_x - 1][enem_y] != '#' && enem_x > play_x)
                    enemyStepN(&((*p).monster));

        }
        else
        {
            if ((*p).map[enem_x][enem_y -1] != '#' && enem_y > play_y)
                enemyStepW(&((*p).monster));
            else
                if((*p).map[enem_x][enem_y +1] != '#' && enem_y < play_y)
                enemyStepE(&((*p).monster));
        }
    }
        
}

int vivod(game p)
{
    int m, map_x, map_y;
    int ent_x, ent_y;
    char* mp;

    map_x = p.Map_Size_X;
    map_y = p.Map_Size_Y;
    
    m = map_x * map_y;
    mp = (char*)calloc(m, sizeof(char));

    if (mp == NULL)
    {
        puts("Нет памяти.Конец работы.");
        return 1;
    }

    for(int i = 0; i < map_x; i++)
        for (int j = 0; j < map_y; j++)
        {
            mp[i* map_x + j] = p.map[i][j];
        }

    playerCoord(&(p.you), &ent_x, &ent_y);
    if(ent_x < map_x && ent_x >= 0 && ent_y >= 0 && ent_y < map_y)
        mp[ent_x * map_x + ent_y] = 'Y';

    enemyCoord(&(p.monster), &ent_x, &ent_y);
    if (ent_x < map_x && ent_x >= 0 && ent_y >= 0 && ent_y < map_y)
        mp[ent_x * map_x + ent_y] = 'M';

    for (int i = 0; i < map_x; i++) {
        for (int j = 0; j < map_y; j++) {
            cout << mp[i* map_x + j] << " ";
        }
        cout << endl; 
    }
    free(mp);
    return 0;
}

void playerInit(player *p, int x, int y, int hp, int dm)
{
    (*p).Damage = dm;
    (*p).Hit_Points = hp;
    (*p).X_Coord = x;
    (*p).Y_Coord = y;
}

void enemyInit(enemy *p, int x, int y, int hp, int dm)
{
    (*p).Damage = dm;
    (*p).Hit_Points = hp;
    (*p).X_Coord = x;
    (*p).Y_Coord = y;
}




int main()
{
    game DOM;
    playerInit(&DOM.you, 8, 1, 100, 50);
    enemyInit(&DOM.monster, 1, 8, 100, 50);
    vivod(DOM);
    getchar();
    playerStepN(&DOM.you);
    enemyMovment(&DOM);
    vivod(DOM);
    getchar();
    playerStepE(&DOM.you);
    enemyMovment(&DOM);
    vivod(DOM);
    getchar();
    playerStepS(&DOM.you);
    enemyMovment(&DOM);
    vivod(DOM);
    getchar();
    playerStepW(&DOM.you);
    enemyMovment(&DOM);
    vivod(DOM);
    getchar();
}

