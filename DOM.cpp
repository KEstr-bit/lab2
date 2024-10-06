#define _CRT_SECURE_NO_WARNINGS
#define K 0.2
#define MAX_BULLETS 10
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


class final
{
private:
    int type;       //Парамтр окончания игры
    char win[10];   //Сообщение при победе
    char loose[10]; //Сообщение при проигрыше

public:
    final(int t, char w[10], char l[10]);
    final();
    ~final();
    //Изменить параметр окончания
    int changeType(int t);
    //Ввести с консоли
    int vvodFinal();
    //Вывести сообщение об завершении игры
    int vivodFinal();

};

class weapon
{
public:
    weapon(int bc, double sp, int tp, int dm);
    weapon();
    ~weapon();
    //получит характеристики оружия
    int getWeaponStat(int* bc, double* sp, int* dm, int* t);
    //установить характеристики оружия
    int setWeaponStat(int bc, double sp, int dm, int t);
    //ввести характеристики с консоли
    int vvodWeapon();

private:
    int bulletCount;    //количество пуль, выпускаемых за раз
    double speed;       //скорость полета пули
    int damage;         //урон, наносимы пулей
    int type;           //тип оружия: 0 - дробовик, 1 - автомат

};

class player
{
public:
    player(double x, double y, int hp, int dm, int rot);
    player();
    ~player();
    //ввести с консоли
    int vvodPlayer();
    //перемщение игрока
    int playerStep(int rotation);
    //получение координат игрока
    int getPlayerCoord(double* x, double* y, int* r);
    int getPlayerCoord(int* x, int* y);
    //нанесение урона игроку
    int playerDamage(int d);
    //получение данных о здоровье игрока
    int getPlayerHitPoints();
    //получение характеристик оружия игрока
    int playerWeaponStat(int* bc, double* sp, int* dm, int* t);


private:
    double X_Coord; //координата игрока по X
    double Y_Coord; //координата игрока по Y
    int rotate;     //направление взгляда игрока: 1 - N, 2 - E, 3 - S, 4 - W 
    int Hit_Points; //очки здоровья игрока
    int Damage;     //урон наносимый игроком
    weapon *gun;    //оружие игрока
};


class enemy
{
public:
    enemy(double x, double y, int hp, int dm, double sp);
    enemy();
    ~enemy();
    //ввод с консоли характеристик врага
    int vvodEnemy();
    //перемещение врага
    int enemyStep(int rotation);
    //получение координат врага
    int getEnemyCoord(double* x, double* y);
    int getEnemyCoord(int* x, int* y);
    //нанесение урона врагу
    int enemyDamage(int d);
    //получение данных об уроне врага
    int getEnemyDamage();
    //получение данных о здоровье врага
    int getEnemyHitPoints();


private:
    double X_Coord;     //координата врага по X
    double Y_Coord;     //координата врага по Y
    double speed;       //скорость врага
    int Hit_Points;     //здоровье врага
    int Damage;         //урон врага
};



class bullet
{
public:
    bullet(int act, double X_Crd, double Y_Crd, double fX_Crd, double fY_Crd, int dm, double sp);
    bullet();
    ~bullet();
    //перемещение пули
    int bulletStep(int rotation);
    //получение данных об уроне пули
    int getBulletDamage();
    //получение координат пули: текущего и точки назначения
    int getBulletCoords(double* st_x, double* st_y, double* fin_x, double* fin_y);


private:
    int active;         //параметр существования пули
    double X_Coord;     //текущая координата пули по X
    double Y_Coord;     //текущая координата пули по Y
    double fin_X_Coord; //конечная координата пули по X
    double fin_Y_Coord; //конечная координата пул по Y
    int damage;         //урон пули
    double speed;       //скорость пули
};



class game
{
public:
    game();
    ~game();
    //движение врага
    int enemyMovment();
    //движение игрока
    int gamePlayerStep(int rot);
    //выстрел игрока
    int Shot();
    //движение пули
    int bulletMovment();
    //взаимодействие объектов
    int interaction();
    //вывод текущего состояния игры
    int vivod();
    //получение данных о здоровье игрока
    int getGamePlayerHitPoints();
    //получение данных о здоровье врага
    int getGameEnemyHitPoints();

private:
    int Map_Size_X;         //Размер карты по X
    int Map_Size_Y;         //Размер карты по Y
    char* map;              //карта
    int activeBullets[10];  //список, существующих пуль
    int bulcnt = 0;         //кол-во существующих пуль
    player *you;            //игрок
    enemy *monster;         //враг
    bullet *bulls[MAX_BULLETS]; //массив пуль
};



final ending;

int main()
{
    //Ввод данных об окончании игры
    ending.vvodFinal();
    system("cls");
    game DOM;
    
    
    printf("\e[?25l");
    int i = 1;  //флажок работы игры
    while (i)
    {
        //обработка действий игрока
        if (GetAsyncKeyState(VK_UP))
        {
            DOM.gamePlayerStep(1);
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            DOM.gamePlayerStep(3);
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            DOM.gamePlayerStep(2);
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            DOM.gamePlayerStep(4);
        }
        if (GetAsyncKeyState(VK_BACK))
        {
            DOM.Shot();
        }

        DOM.enemyMovment();     //движение врага
        DOM.bulletMovment();    //движение пули
        DOM.interaction();      //взаимодействие объектов

        //проверка окончания игры
        if (DOM.getGamePlayerHitPoints() <= 0)
        {
            ending.changeType(2);
            i = 0;
        }
        if (DOM.getGameEnemyHitPoints() <= 0)
        {
            ending.changeType(1);
            i = 0;
        }

        //вывод состояния игры
        DOM.vivod();
        Sleep(50);
        
        
    };
    //завершение игры
    system("cls");
    ending.vivodFinal();
    Sleep(50);

    
}

final::final(int t, char w[10], char l[10])
{
    type = t;
    strcpy(win, w);
    strcpy(loose, l);
}

final::final()
{
    type = 0;
    strcpy(win, "You WIN!");
    strcpy(loose, "You Loose");
}

final::~final()
{
}

int final::vvodFinal()
{
    char w[10];
    char l[10];

    printf("Enter messages when you win: ");
    fgets(w, 10, stdin);
    printf("Enter messages when you loose: ");
    fgets(l, 10, stdin);

    strcpy(win, w);
    strcpy(loose, l);
    return 0;
}

int final::changeType(int t)
{
    type = t;
    return 0;
}

int final::vivodFinal()
{
    if (type == 1)
        printf("\n%s\n", win);
    if (type == 2)
        printf("\n%s\n", loose);
    return 0;
}


weapon::weapon(int bc, double sp, int tp, int dm)
{
    damage = dm;
    bulletCount = bc;
    speed = sp;
    type = tp;
}

weapon::weapon()
{
    bulletCount = 3;
    speed = 0.5;
    damage = 50;
    type = 0;
}

weapon::~weapon()
{
}

int weapon::getWeaponStat(int* bc, double* sp, int* dm, int* t)
{
    *bc = bulletCount;
    *sp = speed;
    *dm = damage;
    *t = type;
    return 0;
}

int weapon::setWeaponStat(int bc, double sp, int dm, int t)
{
    bulletCount = bc;
    speed = sp;
    damage = dm;
    type = t;
    return 0;
}

int weapon::vvodWeapon()
{
    double sp;
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
    
    bulletCount = bc;
    speed = sp;
    damage = dm;
    type = tp;
    return 0;
}


enemy::enemy(double x, double y, int hp, int dm, double sp)
{
    Damage = dm;
    Hit_Points = hp;
    X_Coord = x;
    Y_Coord = y;
    speed = sp;
}

enemy::enemy()
{
    Damage = 50;
    Hit_Points = 100;
    X_Coord = 1;
    Y_Coord = 8;
    speed = 0.2;
}

enemy::~enemy()
{
}

int enemy::vvodEnemy()
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

    Damage = dm; 
    Hit_Points = hp;
    X_Coord = x;
    Y_Coord = y;
    speed = sp;

    return 0;
}

int enemy::enemyStep(int rotation)
{
    int i = 0;
    switch (rotation)
    {
    case 1: X_Coord -= speed; break;
    case 2: Y_Coord += speed; break;
    case 3: X_Coord += speed; break;
    case 4: Y_Coord -= speed; break;
    default: i = 1;
    }
    return 0;
}

int enemy::getEnemyCoord(double* x, double* y)
{
    *x = X_Coord;
    *y = Y_Coord;
    return 0;
}

int enemy::getEnemyCoord(int* x, int* y)
{
    *x = round(X_Coord);
    *y = round(Y_Coord);
    return 0;
}

int enemy::enemyDamage(int d)
{
    Hit_Points -= d;
    return 0;
}

int enemy::getEnemyDamage()
{
    return Damage;
}

int enemy::getEnemyHitPoints()
{
    return Hit_Points;
}

player::player(double x, double y, int hp, int dm, int rot)
{
    Damage = dm;
    Hit_Points = hp;
    X_Coord = x;
    Y_Coord = y;
    rotate = rot;
    gun = new weapon();
}

player::player()
{
    X_Coord = 8;
    Y_Coord = 1;
    rotate = 1;
    Hit_Points = 100;
    Damage = 50;
    gun = new weapon();
    
}

player::~player()
{
}

int player::vvodPlayer()
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

    X_Coord = x;
    Y_Coord = y;
    Hit_Points = hp;
    Damage = dm;

    return 0;
}

int player::playerStep(int rotation)
{
    int i = 0;
    switch (rotation)
    {
    case 1: X_Coord -= 1; rotate = 1;  break;
    case 2: Y_Coord += 1; rotate = 2; break;
    case 3: X_Coord += 1; rotate = 3; break;
    case 4: Y_Coord -= 1; rotate = 4; break;
    default: i = 1;
    }

    return 0;

}

int player::getPlayerCoord(double* x, double* y, int* r)
{
    *r = rotate;
    *x = X_Coord;
    *y = Y_Coord;
    return 0;
}

int player::getPlayerCoord(int* x, int* y)
{
    *x = round(X_Coord);
    *y = round(Y_Coord);
    return 0;
}

int player::playerDamage(int d)
{
    Hit_Points -= d;
    return 0;
}

int player::getPlayerHitPoints()
{
    return Hit_Points;
}

int player::playerWeaponStat(int* bc, double* sp, int* dm, int* t)
{
    gun->getWeaponStat(bc, sp, dm, t);
    return 0;
}

bullet::bullet(int act, double X_Crd, double Y_Crd, double fX_Crd, double fY_Crd, int dm, double sp)
{
    active = act;
    X_Coord = X_Crd;
    Y_Coord = Y_Crd;
    fin_X_Coord = fX_Crd;
    fin_Y_Coord = fY_Crd;
    speed = sp;
    damage = dm;
}

bullet::bullet()
{
    active = 0;
    X_Coord = -1;
    Y_Coord = -1;
    fin_X_Coord = -1;
    fin_Y_Coord = -1;
    speed = 0.2;
    damage = 50;
}

bullet::~bullet()
{
}

int bullet::bulletStep(int rotation)
{
    int i = 0;
    switch (rotation)
    {
    case 1: X_Coord -= speed; break;
    case 2: Y_Coord += speed; break;
    case 3: X_Coord += speed; break;
    case 4: Y_Coord -= speed; break;
    default: i = 1;
    }
    return 0;
}


int bullet::getBulletDamage()
{
    return damage;
}

int bullet::getBulletCoords(double* st_x, double* st_y, double* fin_x, double* fin_y)
{
    *st_x = X_Coord;
    *st_y = Y_Coord;
    *fin_x = fin_X_Coord;
    *fin_y = fin_Y_Coord;
    return 0;
}

game::game()
{
    Map_Size_X = 10;
    Map_Size_Y = 10;
    map = (char*)calloc(Map_Size_X * Map_Size_Y, sizeof(char));
    char preMap[10][10] = 
    { 
        {'#','#','#','#','#','#','#','#','#','#'},
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
    //копирование premap в map
    for (int x = 0; x < Map_Size_X; x++)
    {
        for (int y = 0; y < Map_Size_Y; y++)
        {
            *(map + x * Map_Size_X + y) = preMap[x][y];
        }
    }
    //заполнение массива пуль нулями
    for (int i = 0; i < 10; i++)
        activeBullets[i] = 0;
    bulcnt = 0;
    you = new player();
    monster = new enemy();

}

game::~game()
{
}

int game::enemyMovment()
{
    int i = 0;      //флаг живого игрока
    int HP;
    HP=monster->getEnemyHitPoints();

    //если враг живой
    if (HP > 0)
    {
        double play_x, play_y;
        double enem_x, enem_y;
        double x, y;
        int roundX, roundY;
        int fl = 1;     //флаг видимости игрока
        int rotPlayer;
        you->getPlayerCoord(&play_x, &play_y, &rotPlayer);
        monster->getEnemyCoord(&enem_x, &enem_y);
        x = enem_x;
        y = enem_y;

        double d = sqrt((x - play_x) * (x - play_x) + (y - play_y) * (y - play_y));

        //движение по прямой от врага до игрока с шагом K
        //проверка: видит ли враг игрока
        while (d > 1 && fl)
        {


            x = (K * play_x + (d - K) * x) / d;
            y = (K * play_y + (d - K) * y) / d;
            d = sqrt((x - play_x) * (x - play_x) + (y - play_y) * (y - play_y));

            roundX = round(x);
            roundY = round(y);
            if (*(map + roundX * Map_Size_X + roundY) == '#')
                fl = 0;

        }

        roundX = round(enem_x);
        roundY = round(enem_y);

        //движение врага к игроку
        if (fl)
        {
            if (abs(enem_x - play_x) > abs(enem_y - play_y))
            {
                if (*(map + (roundX + 1) * Map_Size_X + roundY) != '#' && enem_x < play_x)
                    monster->enemyStep(3);
                else
                    if (*(map + (roundX - 1) * Map_Size_X + roundY) != '#' && enem_x > play_x)
                        monster->enemyStep(1);

            }
            else
            {
                if (*(map + (roundX)*Map_Size_X + roundY - 1) != '#' && enem_y > play_y)
                    monster->enemyStep(4);
                else
                    if (*(map + (roundX)*Map_Size_X + roundY + 1) != '#' && enem_y < play_y)
                        monster->enemyStep(2);
            }
        }
    }
    else
        i = 1;
    return i;

}

int game::gamePlayerStep(int rot)
{
    int HP;
    int fl = 0;
    HP = you->getPlayerHitPoints();
    if (HP > 0)
    {
        double x, y;
        int roundX, roundY;
        you->getPlayerCoord(&x, &y, &roundX);
        roundX = round(x);
        roundY = round(y);
        //изменение координат игрока в зависимости от направления
        switch (rot)
        {
        case 1:
            if (*(map + (roundX - 1) * Map_Size_X + roundY) != '#')
                you->playerStep(1);
            else
                fl = 2;
            break;
        case 2:
            if (*(map + (roundX)*Map_Size_X + roundY + 1) != '#')
                you->playerStep(2);
            else
                fl = 2;
            break;
        case 3:
            if (*(map + (roundX + 1) * Map_Size_X + roundY) != '#')
                you->playerStep(3);
            else
                fl = 2;
            break;
        case 4:
            if (*(map + (roundX)*Map_Size_X + roundY - 1) != '#')
                you->playerStep(4);
            else
                fl = 2;
            break;
        default:
            fl = 1;
        }
    }
    return fl;
}

int game::Shot()
{
    int bulletCount = 0;
    double speed = 0;
    int damage = 0;
    int type_weapon = 0;
    double X_coord, Y_coord;
    double fin_X_coord = 0, fin_Y_coord = 0;
    int rotation;

    you->getPlayerCoord(& X_coord, & Y_coord, & rotation);
    you->playerWeaponStat(&bulletCount, &speed, &damage, &type_weapon);

    int d = 0 - bulletCount / 2;
    int fl = 0;
    int j = 0;
    //если оружие выстреливает больше 0 пуль и на карте ни одной пули
    if (bulletCount > 0 && bulcnt == 0)
    {
        //выбор типа оружия
        switch (type_weapon)
        {
        case 0:
            for (int i = 0; i < bulletCount; i++)
            {
                double x, y;
                x = X_coord;
                y = Y_coord;
                //выбор координа в зависимости от направления
                switch (rotation)
                {
                case 1:
                    fin_X_coord = X_coord - 4;
                    fin_Y_coord = Y_coord + d;
                    y += d;
                    break;
                case 2:
                    fin_X_coord = X_coord + d;
                    fin_Y_coord = Y_coord + 4;
                    x += d;

                    break;
                case 3:
                    fin_X_coord = X_coord + 4;
                    fin_Y_coord = Y_coord + d;
                    y += d;
                    break;
                case 4:
                    fin_X_coord = X_coord + d;
                    fin_Y_coord = Y_coord - 4;
                    x += d;
                    break;

                }
                d += 1;
                // инициализация пуль
                for(int fl = 1; j < 10 && fl; j++)
                    if (activeBullets[j] == 0)
                    {
                        bulls[j] = new bullet(1, x, y, fin_X_coord, fin_Y_coord, damage, speed);
                        bulcnt += 1;
                        activeBullets[j] = 1;
                        fl = 0;
                    }
                
                
            }
            break;
        case 1:
            for (int i = 0; i < bulletCount; i++)
            {
                //выбор координат в зависимости от направления
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
                //инициализация пуль
                for (int fl = 1; j < 10 && fl; j++)
                    if (activeBullets[j] == 0)
                    {
                        bulls[j] = new bullet(1, X_coord, Y_coord, fin_X_coord, fin_Y_coord, damage, speed);
                        bulcnt += 1;
                        activeBullets[j] = 1;
                        fl = 0;
                    }
                
            }
        }

    }
    else 
        fl = 1;
    return fl;
}

int game::bulletMovment()
{
    
    for (int i = 0; i < 10; i++)
    {
        //если пуля существует
        if (activeBullets[i] == 1)
        {
            double st_x, st_y;
            double fin_x, fin_y;
            bulls[i]->getBulletCoords(&st_x, &st_y, &fin_x, &fin_y);

            //движение пули к конечной точке
            if (abs(fin_x - st_x) > abs(fin_y - st_y))
            {
                if (fin_x < st_x)
                    bulls[i]->bulletStep(1);
                else
                    if (fin_x > st_x)
                        bulls[i]->bulletStep(3);

            }
            else
            {
                if (fin_y > st_y)
                    bulls[i]->bulletStep(2);
                else
                    if (fin_y < st_y)
                        bulls[i]->bulletStep(4);
            }
        }
    }
    return 0;
}

int game::interaction()
{
    //если на карте есть пули
    if (bulcnt > 0)
    {
        for (int i = 0; i < 10; i++)
        {
            //если пуля существует
            if (activeBullets[i] == 1)
            {
                double st_x, st_y;
                double fin_x, fin_y;
                int map_x, map_y;
                bulls[i]->getBulletCoords(&st_x, &st_y, &fin_x, &fin_y);
                map_x = round(st_x);
                map_y = round(st_y);
                //если пуля столкнулась со стеной
                if (*(map+map_x*Map_Size_X+map_y) == '#')
                {
                    delete bulls[i];
                    activeBullets[i] = 0;
                    bulcnt -= 1;
                }
                else
                {
                    monster->getEnemyCoord(&map_x, &map_y);
                    //если пуля попала во врага
                    if (round(st_x) == map_x && round(st_y) == map_y)
                    {

                        monster->enemyDamage(bulls[i]->getBulletDamage());
                        delete bulls[i];
                        activeBullets[i] = 0;
                        bulcnt -= 1;

                    }
                    else
                    {
                        //если пуля достигла своей конечной точки
                        if (round(st_x) == round(fin_x) && round(st_y) == round(fin_y))
                        {
                            delete bulls[i];
                            activeBullets[i] = 0;
                            bulcnt -= 1;
                        }
                    }
                }
            }
        }
    }
    int map_x, map_y;
    int pl_x, pl_y;
    you->getPlayerCoord(&pl_x, &pl_y);
    monster->getEnemyCoord(&map_x, &map_y);
    //если враг достиг игрока
    if (map_x == pl_x && map_y == pl_y)
    {
        you->playerDamage(monster->getEnemyDamage());
    }
    return 0;
}

int game::vivod()
{
    int m;
    double ent_x, ent_y;
    int roundX, roundY;
    char* mp;

    m = Map_Size_X * Map_Size_Y;
    mp = (char*)calloc(m, sizeof(char));

    if (mp == NULL)
    {
        return 1;
    }

    //копирование карты в динамический массив
    for (int i = 0; i < Map_Size_X; i++)
        for (int j = 0; j < Map_Size_Y; j++)
        {
            mp[i * Map_Size_X + j] = map[i * Map_Size_X + j];
        }


    //если игрок живой
    if (you->getPlayerHitPoints() > 0)
    {
        int rotPlayer;
        you->getPlayerCoord(&ent_x, &ent_y, &rotPlayer);

        roundX = round(ent_x);
        roundY = round(ent_y);
        //обозначение игрока в зависимости от направления взгляда
        if (ent_x < Map_Size_X && ent_x >= 0 && ent_y >= 0 && ent_y < Map_Size_Y)
            switch (rotPlayer)
            {
            case 1: mp[roundX * Map_Size_X + roundY] = 'N'; break;
            case 2: mp[roundX * Map_Size_X + roundY] = 'E'; break;
            case 3: mp[roundX * Map_Size_X + roundY] = 'S'; break;
            case 4: mp[roundX * Map_Size_X + roundY] = 'W'; break;
            }
    }
    
    //если враг живой
    if (monster->getEnemyHitPoints() > 0)
    {
        monster->getEnemyCoord(&ent_x, &ent_y);
        roundX = round(ent_x);
        roundY = round(ent_y);
        if (ent_x < Map_Size_X && ent_x >= 0 && ent_y >= 0 && ent_y < Map_Size_Y)
            mp[roundX * Map_Size_X + roundY] = 'M';
    }

    //отображение пуль
    for (int i = 0; i < 10; i++)
    {
        if (activeBullets[i] == 1)
        {
            double st_x, st_y;
            double fin_x, fin_y;
            bulls[i]->getBulletCoords(&st_x, &st_y, &fin_x, &fin_y);
            roundX = round(st_x);
            roundY = round(st_y);
            if (st_x < Map_Size_X && st_x >= 0 && st_y >= 0 && st_y < Map_Size_Y)
                mp[roundX * Map_Size_X + roundY] = '0';
        }
    }

    setcur(0, 0);
    //вывод новой карты
    for (int i = 0; i < Map_Size_X; i++) {
        for (int j = 0; j < Map_Size_Y; j++) {
            cout << mp[i * Map_Size_X + j] << " ";
        }
        cout << endl;
    }
    free(mp);
    return 0;
}

int game::getGamePlayerHitPoints()
{
    return you->getPlayerHitPoints();
}

int game::getGameEnemyHitPoints()
{
    return monster->getEnemyHitPoints();
}