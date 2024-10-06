#define _CRT_SECURE_NO_WARNINGS
#define K 0.2
#include <iostream>
#include <windows.h>
#include <string.h>
using namespace std;

//установка курсора на позицию  x y 
void setcur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

struct weapon
{
    int bulletCount = 3;    //количество пуль, выпускаемых оружием
    double speed = 0.5;     //скорость пули
    int damage = 50;        //урон пули
    int type = 1;           //тип оружия
};

//инициализация оружия
void weaponInit(weapon* p, int bc, double sp, int tp, int dm);
//получение данных об оружии
void weaponStat(weapon p, int* bc, double* sp, int* dm, int* t);
//ввод оружия с консоли
void vvodweapon(weapon* p);

struct player
{
    double X_Coord = -1;    //координата игрока по X
    double Y_Coord = -1;    //координата игрока по Y
    int rotate = 1;         //направление игрока
    int Hit_Points = -1;    //здоровье игрока
    int Damage = -1;        //урон игрока
    weapon gun;             //оружие игрока
};

//инициализация игрока
void playerInit(player* p, int x, int y, int hp, int dm, int rot);
//ввод игрока с консоли
void vvodPlayer(player* p);
//получение данных об оружии игрока
void playerWeaponStat(player p, int* bc, double* sp, int* dm, int* t);
//шаг на север
void playerStepN(player* p);
//шаг на юг
void playerStepS(player* p);
//шаг на запад
void playerStepW(player* p);
//шаг на восток
void playerStepE(player* p);
//получение координат по игрокам
void playerCoord(player* p, double* x, double* y, int* r);
void playerCoord(player p, int* x, int* y);
//нанесение урона игроку
void playerDamage(player* p, int d);
//получение данных о здоровье игрока
int playerHitPoints(player p);

struct enemy
{
    double X_Coord = -1;        //координата врага по X
    double Y_Coord = -1;        //координата врага по Y
    double speed = 0.2;         //скорость врага
    int Hit_Points = -1;        //здоровье врага
    int Damage = -1;            //урон врага
};

//инициализация врага
void enemyInit(enemy* p, double x, double y, int hp, int dm, double sp);
void enemyInit(enemy* p);
//ввод врага с консоли
void vvodEnemy(enemy* p);
//шаг на север
void enemyStepN(enemy* p);
//шаг на юг
void enemyStepS(enemy* p);
//шаг на запад
void enemyStepW(enemy* p);
//шаг на восток
void enemyStepE(enemy* p);
//получение данных о здоровье врага
int enemyHitPoints(enemy p);
//получение координат врага
void enemyCoord(enemy* p, double* x, double* y);
void enemyCoord(enemy* p, int* x, int* y);
//нанесение урона врагу
void enemyDamage(enemy* p, int d);
//получение данных об уроне врага
int getEnemyDamage(enemy p);

struct bullet
{
    int active = 0;             //флаг существования пули
    double X_Coord = -1;        //текущая координата пули по X
    double Y_Coord = -1;        //текущая координата пули по Y
    double fin_X_Coord = -1;    //конечная координата пули по X
    double fin_Y_Coord = -1;    //конечная координата пули по Y
    int damage = 0;             //урон пули
    double speed = 0.2;         //скорость пули
};

//инициализация пули
void bulletInit(bullet* p, int active, double X_Coord, double Y_Coord, double fin_X_Coord, double fin_Y_Coord, int damage, double speed);
void bulletInit(bullet* p);
//шаг на север
void bulletStepN(bullet* p);
//шаг на юг
void bulletStepS(bullet* p);
//шаг на запад
void bulletStepW(bullet* p);
//шаг на восток
void bulletStepE(bullet* p);
//получение данных об уроне пули
int bulletDamage(bullet p);
//получение координат пули: текущих и конечных
void bulletCoords(bullet p, double* st_x, double* st_y, double* fin_x, double* fin_y);




struct game
{
    int Map_Size_X = 10;    //размер карты по X
    int Map_Size_Y = 10;    //размер карты по Y
    char map[10][10] =      //карта
    { {'#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','#','#','#','#','#','#','.','.','#'},
        {'#','.','.','.','.','.','#','.','.','#'},
        {'#','.','.','.','.','.','.','.','.','#'},
        {'#','.','.','.','#','.','.','.','.','#'},
        {'#','.','.','.','#','.','.','.','.','#'},
        {'#','#','#','#','#','#','#','#','#','#'}
    };
    int bulcnt = 0;         //количество пуль
    player you;             //игрок
    enemy monster;          //враг
    bullet bulls[10];       //пули

};

//выстрел
void Shot(game* p);
//движение пули
void bulletMovment(game* p);
//движение врага
void enemyMovment(game* p);
//вывод текущего состояния игры
int vivod(game p);
//шаг игрока на север
void gamePlayerStepN(game* p);
//шаг игрока на юг
void gamePlayerStepS(game* p);
//шаг игрока на запад
void gamePlayerStepW(game* p);
//шиг на восток
void gamePlayerStepE(game* p);
//взаимодействие пуль врага и игрока
void interaction(game* p);

struct final
{
    int type = 0;       //параметр финала
    char win[10] = { 'Y','o','u',' ','W','I','N','!','\n' };  //сообщение при победе
    char loose[10] = { 'Y','o','u',' ','L','O','O','S','E','\n' };   //сообщение при проигрыше
};

//инициализация финала
void finalInit(final* p, int t, char w[10], char l[10]);
//вывод финала
void vivodFinal(final p);
//изменение типа финала
void changeType(final* p, int t);
//ввод финала
void vvodFinal(final* p);


final ending;

int main()
{
    //ввод финала
    vvodFinal(&ending);
    system("cls");
    //инициализация
    game DOM;
    playerInit(&DOM.you, 8, 1, 100, 50, 1);
    enemyInit(&DOM.monster, 1, 8, 100, 50, 0.2);
    weaponInit(&DOM.you.gun, 5, 0.2, 1, 50);
    printf("\e[?25l");
    int i = 1;
    //обработка дейсвий игрока
    while (i)
    {
        if (GetAsyncKeyState(VK_UP))
        {
            gamePlayerStepN(&DOM);
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            gamePlayerStepS(&DOM);
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            gamePlayerStepE(&DOM);
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            gamePlayerStepW(&DOM);
        }
        if (GetAsyncKeyState(VK_BACK))
        {
            Shot(&DOM);
        }

        enemyMovment(&DOM);
        bulletMovment(&DOM);
        interaction(&DOM);

        //изменение финала
        if (playerHitPoints(DOM.you) <= 0)
        {
            changeType(&ending, 2);
            i = 0;
        }
        if (enemyHitPoints(DOM.monster) <= 0)
        {
            changeType(&ending, 1);
            i = 0;
        }
        //вывод текущего состояния игры
        vivod(DOM);
        Sleep(50);


    };
    //завершение игры
    system("cls");
    vivodFinal(ending);
    Sleep(50);


}

void weaponInit(weapon* p, int bc, double sp, int tp, int dm)
{
    p->damage = dm;
    p->bulletCount = bc;
    p->speed = sp;
    p->type = tp;
}

void weaponStat(weapon p, int* bc, double* sp, int* dm, int* t)
{
    *bc = p.bulletCount;
    *sp = p.speed;
    *dm = p.damage;
    *t = p.type;
}

void vvodweapon(weapon* p)
{
    double x, y, sp;
    int bc, tp, dm;

    do {
        printf("Enter bullets count: ");
        scanf("%d", &bc);
    } while (bc <= 0);
    do {
        printf("Enter type: ");
        scanf("%d", &tp);
    } while (tp < 0 || tp >1);
    do {
        printf("Enter damage: ");
        scanf("%d", &dm);
    } while (dm <= 0);
    do {
        printf("Enter speed: ");
        scanf("%lf", &sp);
    } while (sp <= 0);
    weaponInit(p, bc, sp, tp, dm);
}

void enemyInit(enemy* p, double x, double y, int hp, int dm, double sp)
{
    p->Damage = dm;
    p->Hit_Points = hp;
    p->X_Coord = x;
    p->Y_Coord = y;
    p->speed = sp;
}

void enemyInit(enemy* p)
{
    p->Damage = -1;
    p->Hit_Points = -1;
    p->X_Coord = -1;
    p->Y_Coord = -1;
    p->speed = 0.2;
}

void vvodEnemy(enemy* p)
{
    double x, y, sp;
    int hp, dm;
    do {
        printf("Enter the X coordinate: ");
        scanf("%lf", &x);
    } while (x < 0);
    do {
        printf("Enter the Y coordinate: ");
        scanf("%lf", &y);
    } while (y < 0);
    do {
        printf("Enter hp: ");
        scanf("%d", &hp);
    } while (hp <= 0);
    do {
        printf("Enter damage: ");
        scanf("%d", &dm);
    } while (dm <= 0);
    do {
        printf("Enter speed: ");
        scanf("%lf", &sp);
    } while (sp <= 0);

    enemyInit(p, x, y, hp, dm, sp);
}

void enemyStepN(enemy* p)
{
    p->X_Coord -= p->speed;
}

void enemyStepS(enemy* p)
{
    p->X_Coord += p->speed;
}

void enemyStepW(enemy* p)
{
    p->Y_Coord -= p->speed;
}

void enemyStepE(enemy* p)
{
    p->Y_Coord += p->speed;
}

int enemyHitPoints(enemy p)
{
    return p.Hit_Points;
}

void enemyCoord(enemy* p, double* x, double* y)
{
    *x = p->X_Coord;
    *y = p->Y_Coord;
}

void enemyCoord(enemy* p, int* x, int* y)
{
    *x = round(p->X_Coord);
    *y = round(p->Y_Coord);
}

void enemyDamage(enemy* p, int d)
{
    p->Hit_Points -= d;
}

int getEnemyDamage(enemy p)
{
    return p.Damage;
}

void bulletInit(bullet* p, int active, double X_Coord, double Y_Coord, double fin_X_Coord, double fin_Y_Coord, int damage, double speed)
{
    p->active = active;
    p->X_Coord = X_Coord;
    p->Y_Coord = Y_Coord;
    p->fin_X_Coord = fin_X_Coord;
    p->fin_Y_Coord = fin_Y_Coord;
    p->speed = speed;
    p->damage = damage;


}

void bulletInit(bullet* p)
{
    p->active = 0;
    p->X_Coord = -1;
    p->Y_Coord = -1;
    p->fin_X_Coord = -1;
    p->fin_Y_Coord = -1;
    p->speed = 0.2;
    p->damage = 0;

}

void bulletStepN(bullet* p)
{
    p->X_Coord -= p->speed;
}

void bulletStepS(bullet* p)
{
    p->X_Coord += p->speed;
}

void bulletStepW(bullet* p)
{
    p->Y_Coord -= p->speed;
}

void bulletStepE(bullet* p)
{
    p->Y_Coord += p->speed;
}

int bulletDamage(bullet p)
{
    return p.damage;
}

void bulletCoords(bullet p, double* st_x, double* st_y, double* fin_x, double* fin_y)
{
    *st_x = p.X_Coord;
    *st_y = p.Y_Coord;
    *fin_x = p.fin_X_Coord;
    *fin_y = p.fin_Y_Coord;
}

void finalInit(final* p, int t, char w[10], char l[10])
{
    p->type = t;
    p->win;
    strcpy(p->win, w);
    strcpy(p->loose, l);
}

void vivodFinal(final p)
{
    if (p.type == 1)
        printf("\n%s\n", p.win);
    if (p.type == 2)
        printf("\n%s\n", p.loose);
}

void changeType(final* p, int t)
{
    p->type = t;
}

void vvodFinal(final* p)
{
    char w[10];
    char l[10];
    printf("Enter messages when you win: ");
    fgets(w, 10, stdin);
    printf("Enter messages when you loose: ");
    fgets(l, 10, stdin);
    finalInit(p, 0, w, l);
}

void playerInit(player* p, int x, int y, int hp, int dm, int rot)
{
    p->Damage = dm;
    p->Hit_Points = hp;
    p->X_Coord = x;
    p->Y_Coord = y;
    p->rotate = rot;
}








void vvodPlayer(player* p)
{
    double x, y;
    int hp, dm;
    do {
        printf("Enter the X coordinate: ");
        scanf("%lf", &x);
    } while (x < 0);
    do {
        printf("Enter the Y coordinate: ");
        scanf("%lf", &y);
    } while (y < 0);
    do {
        printf("Enter hp: ");
        scanf("%d", &hp);
    } while (hp <= 0);
    do {
        printf("Enter damage: ");
        scanf("%d", &dm);
    } while (dm <= 0);

    playerInit(p, x, y, hp, dm, 1);
}






void playerWeaponStat(player p, int* bc, double* sp, int* dm, int* t)
{
    weaponStat(p.gun, bc, sp, dm, t);
}

void playerStepN(player* p)
{
    p->X_Coord -= 1;
    p->rotate = 1;
}

void playerStepS(player* p)
{
    p->X_Coord += 1;
    p->rotate = 3;
}

void playerStepW(player* p)
{
    p->Y_Coord -= 1;
    p->rotate = 4;
}

void playerStepE(player* p)
{
    p->Y_Coord += 1;
    p->rotate = 2;
}



void playerCoord(player* p, double* x, double* y, int* r)
{
    *r = p->rotate;
    *x = p->X_Coord;
    *y = p->Y_Coord;
}

void playerCoord(player p, int* x, int* y)
{
    *x = round(p.X_Coord);
    *y = round(p.Y_Coord);
}

void playerDamage(player* p, int d)
{
    p->Hit_Points -= d;
}

int playerHitPoints(player p)
{
    return p.Hit_Points;
}

void Shot(game* p)
{
    int bulletCount = 0;
    double speed = 0;
    int damage = 0;
    int type = 0;
    double X_coord, Y_coord;
    double fin_X_coord, fin_Y_coord;
    int rotation;

    playerCoord(&p->you, &X_coord, &Y_coord, &rotation);
    playerWeaponStat(p->you, &bulletCount, &speed, &damage, &type);
    int d = 0 - bulletCount / 2;
    p->bulcnt = bulletCount;
    if (bulletCount > 0)
    {
        switch (type)
        {
        case 0:
            for (int i = 0; i < bulletCount; i++)
            {
                double x, y;
                x = X_coord;
                y = Y_coord;
                switch (rotation)
                {
                case 1:
                    fin_X_coord = X_coord - 4 - d;
                    fin_Y_coord = Y_coord + d;
                    y += d;
                    break;
                case 2:
                    fin_X_coord = X_coord + d;
                    fin_Y_coord = Y_coord + 4 + d;
                    x += d;

                    break;
                case 3:
                    fin_X_coord = X_coord + 4 + d;
                    fin_Y_coord = Y_coord + d;
                    y += d;
                    break;
                case 4:
                    fin_X_coord = X_coord + d;
                    fin_Y_coord = Y_coord - 4 - d;
                    x += d;
                    break;

                }
                d += 1;
                bulletInit(&p->bulls[i], 1, x, y, fin_X_coord, fin_Y_coord, damage, speed);
            }
            break;
        case 1:
            for (int i = 0; i < bulletCount; i++)
            {
                switch (rotation)
                {
                case 1:
                    fin_X_coord = X_coord - 10;
                    fin_Y_coord = Y_coord;
                    X_coord -= i;
                    break;
                case 2:
                    fin_X_coord = X_coord;
                    fin_Y_coord = Y_coord + 10;
                    Y_coord += i;
                    break;
                case 3:
                    fin_X_coord = X_coord + 10;
                    fin_Y_coord = Y_coord;
                    X_coord += i;
                    break;
                case 4:
                    fin_X_coord = X_coord;
                    fin_Y_coord = Y_coord - 10;
                    Y_coord -= i;
                    break;
                }
                bulletInit(&p->bulls[i], 1, X_coord, Y_coord, fin_X_coord, fin_Y_coord, damage, speed);
            }
        }
    }
}

void bulletMovment(game* p)
{
    int bulletCount = p->bulcnt;
    for (int i = 0; i < bulletCount; i++)
    {
        double st_x, st_y;
        double fin_x, fin_y;
        bulletCoords(p->bulls[i], &st_x, &st_y, &fin_x, &fin_y);

        if (abs(fin_x - st_x) > abs(fin_y - st_y))
        {
            if (fin_x < st_x)
                bulletStepN(&(p->bulls[i]));
            else
                if (fin_x > st_x)
                    bulletStepS(&(p->bulls[i]));

        }
        else
        {
            if (fin_y > st_y)
                bulletStepE(&(p->bulls[i]));
            else
                if (fin_y < st_y)
                    bulletStepW(&(p->bulls[i]));
        }
    }
}

void enemyMovment(game* p)
{
    double play_x, play_y;
    double enem_x, enem_y;
    double x, y;
    int roundX, roundY;
    int fl = 1;
    int rotPlayer;
    playerCoord(&(p->you), &play_x, &play_y, &rotPlayer);
    enemyCoord(&(p->monster), &enem_x, &enem_y);
    x = enem_x;
    y = enem_y;
    roundX = enem_x;
    roundY = enem_y;
    double d = sqrt((x - play_x) * (x - play_x) + (y - play_y) * (y - play_y));
    while (d > 1 && fl)
    {

        d = sqrt((x - play_x) * (x - play_x) + (y - play_y) * (y - play_y));
        x = (K * play_x + (d - K) * x) / d;
        y = (K * play_y + (d - K) * y) / d;

        roundX = round(x);
        roundY = round(y);
        if (p->map[roundX][roundY] == '#')
            fl = 0;

    }
    roundX = round(enem_x);
    roundY = round(enem_y);
    if (fl)
    {
        if (abs(enem_x - play_x) > abs(enem_y - play_y))
        {
            if (p->map[roundX + 1][roundY] != '#' && enem_x < play_x)
                enemyStepS(&(p->monster));
            else
                if (p->map[roundX - 1][roundY] != '#' && enem_x > play_x)
                    enemyStepN(&(p->monster));

        }
        else
        {
            if (p->map[roundX][roundY - 1] != '#' && enem_y > play_y)
                enemyStepW(&(p->monster));
            else
                if (p->map[roundX][roundY + 1] != '#' && enem_y < play_y)
                    enemyStepE(&(p->monster));
        }
    }

}

int vivod(game p)
{
    int m, map_x, map_y;
    double ent_x, ent_y;
    int roundX, roundY;
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

    for (int i = 0; i < map_x; i++)
        for (int j = 0; j < map_y; j++)
        {
            mp[i * map_x + j] = p.map[i][j];
        }

    int rotPlayer;
    playerCoord(&(p.you), &ent_x, &ent_y, &rotPlayer);
    roundX = round(ent_x);
    roundY = round(ent_y);
    if (ent_x < map_x && ent_x >= 0 && ent_y >= 0 && ent_y < map_y)
        switch (rotPlayer)
        {
        case 1: mp[roundX * map_x + roundY] = 'N'; break;
        case 2: mp[roundX * map_x + roundY] = 'E'; break;
        case 3: mp[roundX * map_x + roundY] = 'S'; break;
        case 4: mp[roundX * map_x + roundY] = 'W'; break;
        }

    enemyCoord(&(p.monster), &ent_x, &ent_y);
    roundX = round(ent_x);
    roundY = round(ent_y);
    if (enemyHitPoints(p.monster) > 0)
    {
        if (ent_x < map_x && ent_x >= 0 && ent_y >= 0 && ent_y < map_y)
            mp[roundX * map_x + roundY] = 'M';
    }

    int count = p.bulcnt;
    for (int i = 0; i < count; i++)
    {
        double st_x, st_y;
        double fin_x, fin_y;
        bulletCoords((p).bulls[i], &st_x, &st_y, &fin_x, &fin_y);
        roundX = round(st_x);
        roundY = round(st_y);
        if (st_x < map_x && st_x >= 0 && st_y >= 0 && st_y < map_y)
            mp[roundX * map_x + roundY] = '0';
    }

    setcur(0, 0);
    for (int i = 0; i < map_x; i++) {
        for (int j = 0; j < map_y; j++) {
            cout << mp[i * map_x + j] << " ";
        }
        cout << endl;
    }
    free(mp);
    return 0;
}

void gamePlayerStepN(game* p)
{
    double x, y;
    int roundX, roundY;
    playerCoord(&p->you, &x, &y, &roundX);
    roundX = round(x);
    roundY = round(y);
    if (p->map[roundX - 1][roundY] != '#')
        playerStepN(&p->you);
}

void gamePlayerStepS(game* p)
{
    double x, y;
    int roundX, roundY;
    playerCoord(&p->you, &x, &y, &roundX);
    roundX = round(x);
    roundY = round(y);
    if (p->map[roundX + 1][roundY] != '#')
        playerStepS(&p->you);
}

void gamePlayerStepW(game* p)
{
    double x, y;
    int roundX, roundY;
    playerCoord(&p->you, &x, &y, &roundX);
    roundX = round(x);
    roundY = round(y);
    if (p->map[roundX][roundY - 1] != '#')
        playerStepW(&p->you);
}

void gamePlayerStepE(game* p)
{
    double x, y;
    int roundX, roundY;
    playerCoord(&p->you, &x, &y, &roundX);
    roundX = round(x);
    roundY = round(y);
    if (p->map[roundX][roundY + 1] != '#')
        playerStepE(&p->you);
}

void interaction(game* p)
{
    int bc = p->bulcnt;
    for (int i = 0; i < bc; i++)
    {
        double st_x, st_y;
        double fin_x, fin_y;
        int map_x, map_y;
        bulletCoords(p->bulls[i], &st_x, &st_y, &fin_x, &fin_y);
        map_x = round(st_x);
        map_y = round(st_y);
        if (p->map[map_x][map_y] == '#')
        {
            bulletInit(&p->bulls[i]);
        }
        enemyCoord(&p->monster, &map_x, &map_y);
        if (round(st_x) == map_x && round(st_y) == map_y)
        {

            enemyDamage(&p->monster, bulletDamage(p->bulls[i]));
            bulletInit(&p->bulls[i]);

        }

        if (round(st_x) == round(fin_x) && round(st_y) == round(fin_y))
        {
            bulletInit(&p->bulls[i]);
        }
    }
    int map_x, map_y;
    int pl_x, pl_y;
    playerCoord(p->you, &pl_x, &pl_y);
    enemyCoord(&p->monster, &map_x, &map_y);
    if (map_x == pl_x && map_y == pl_y)
    {
        playerDamage(&p->you, getEnemyDamage(p->monster));
    }
}