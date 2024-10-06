#define _CRT_SECURE_NO_WARNINGS
#define K 0.2
#define MAX_BULLETS 10
#include <iostream>
#include <windows.h>
#include <string.h>
using namespace std;


void setcur(int x, int y)//установка курсора на позицию  x y 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};


class final
{
private:
    int type = 0;
    char win[10];
    char loose[10];

public:
    final(int t, char w[10], char l[10]);
    final();
    ~final();
    int changeType(int t);
    int vvodFinal();
    int vivodFinal();

};

class weapon
{
public:
    weapon(int bc, double sp, int tp, int dm);
    weapon();
    ~weapon();
    int getWeaponStat(int* bc, double* sp, int* dm, int* t);
    int setWeaponStat(int bc, double sp, int dm, int t);
    int vvodWeapon();

private:
    int bulletCount;
    double speed;
    int damage;
    int type;

};

class player
{
public:
    player(double x, double y, int hp, int dm, int rot);
    player();
    ~player();
    int vvodPlayer();
    int playerStep(int rotation);
    int getPlayerCoord(double* x, double* y, int* r);
    int getPlayerCoord(int* x, int* y);
    int playerDamage(int d);
    int getPlayerHitPoints();
    int playerWeaponStat(int* bc, double* sp, int* dm, int* t);


private:
    double X_Coord;
    double Y_Coord;
    int rotate;
    int Hit_Points;
    int Damage;
    weapon *gun;
};


class enemy
{
public:
    enemy(double x, double y, int hp, int dm, double sp);
    enemy();
    ~enemy();
    int vvodEnemy();
    int enemyStep(int rotation);
    int getEnemyCoord(double* x, double* y);
    int getEnemyCoord(int* x, int* y);
    int enemyDamage(int d);
    int getEnemyDamage();
    int getEnemyHitPoints();


private:
    double X_Coord;
    double Y_Coord;
    double speed;
    int Hit_Points;
    int Damage;
};



class bullet
{
public:
    bullet(int act, double X_Crd, double Y_Crd, double fX_Crd, double fY_Crd, int dm, double sp);
    bullet();
    ~bullet();
    int bulletStep(int rotation);
    int getBulletDamage();
    int getBulletCoords(double* st_x, double* st_y, double* fin_x, double* fin_y);


private:
    int active;
    double X_Coord;
    double Y_Coord;
    double fin_X_Coord;
    double fin_Y_Coord;
    int damage;
    double speed;
};





class game
{
public:
    game();
    ~game();
    int enemyMovment();
    int gamePlayerStep(int rot);
    int Shot();
    int bulletMovment();
    int interaction();
    int vivod();
    int getGamePlayerHitPoints();
    int getGameEnemyHitPoints();

private:
    int Map_Size_X;
    int Map_Size_Y;
    char* map;
    int activeBullets[10];
    int bulcnt = 0;
    player *you;
    enemy *monster;
    bullet *bulls[MAX_BULLETS];
};



final ending;

int main()
{
    ending.vvodFinal();
    system("cls");
    game DOM;
    
    
    printf("\e[?25l");
    int i = 1;
    while (i)
    {
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

        DOM.enemyMovment();
        DOM.bulletMovment();
        DOM.interaction();
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
        DOM.vivod();
        Sleep(50);
        
        
    };
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
    for (int x = 0; x < Map_Size_X; x++)
    {
        for (int y = 0; y < Map_Size_Y; y++)
        {
            *(map + x * Map_Size_X + y) = preMap[x][y];
        }
    }
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
    int i = 0;
    int HP;
    HP=monster->getEnemyHitPoints();

    if (HP > 0)
    {
        double play_x, play_y;
        double enem_x, enem_y;
        double x, y;
        int roundX, roundY;
        int fl = 1;
        int rotPlayer;
        you->getPlayerCoord(&play_x, &play_y, &rotPlayer);
        monster->getEnemyCoord(&enem_x, &enem_y);
        x = enem_x;
        y = enem_y;

        double d = sqrt((x - play_x) * (x - play_x) + (y - play_y) * (y - play_y));
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
    if (bulletCount > 0 && bulcnt == 0)
    {
        switch (type_weapon)
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
    
    int bulletCount = bulcnt;
    for (int i = 0; i < 10; i++)
    {
        if (activeBullets[i] == 1)
        {
            double st_x, st_y;
            double fin_x, fin_y;
            bulls[i]->getBulletCoords(&st_x, &st_y, &fin_x, &fin_y);

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
    if (bulcnt > 0)
    {
        for (int i = 0; i < 10; i++)
        {
            if (activeBullets[i] == 1)
            {
                double st_x, st_y;
                double fin_x, fin_y;
                int map_x, map_y;
                bulls[i]->getBulletCoords(&st_x, &st_y, &fin_x, &fin_y);
                map_x = round(st_x);
                map_y = round(st_y);
                if (*(map+map_x*Map_Size_X+map_y) == '#')
                {
                    delete bulls[i];
                    activeBullets[i] = 0;
                    bulcnt -= 1;
                }
                else
                {
                    monster->getEnemyCoord(&map_x, &map_y);
                    if (round(st_x) == map_x && round(st_y) == map_y)
                    {

                        monster->enemyDamage(bulls[i]->getBulletDamage());
                        delete bulls[i];
                        activeBullets[i] = 0;
                        bulcnt -= 1;

                    }
                    else
                    {
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

    for (int i = 0; i < Map_Size_X; i++)
        for (int j = 0; j < Map_Size_Y; j++)
        {
            mp[i * Map_Size_X + j] = map[i * Map_Size_X + j];
        }


    if (you->getPlayerHitPoints() > 0)
    {
        int rotPlayer;
        you->getPlayerCoord(&ent_x, &ent_y, &rotPlayer);

        roundX = round(ent_x);
        roundY = round(ent_y);
        if (ent_x < Map_Size_X && ent_x >= 0 && ent_y >= 0 && ent_y < Map_Size_Y)
            switch (rotPlayer)
            {
            case 1: mp[roundX * Map_Size_X + roundY] = 'N'; break;
            case 2: mp[roundX * Map_Size_X + roundY] = 'E'; break;
            case 3: mp[roundX * Map_Size_X + roundY] = 'S'; break;
            case 4: mp[roundX * Map_Size_X + roundY] = 'W'; break;
            }
    }
    
    
    if (monster->getEnemyHitPoints() > 0)
    {
        monster->getEnemyCoord(&ent_x, &ent_y);
        roundX = round(ent_x);
        roundY = round(ent_y);
        if (ent_x < Map_Size_X && ent_x >= 0 && ent_y >= 0 && ent_y < Map_Size_Y)
            mp[roundX * Map_Size_X + roundY] = 'M';
    }

    
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