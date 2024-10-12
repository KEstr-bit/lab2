#define _CRT_SECURE_NO_WARNINGS
#define K 0.2
#define MAX_BULLETS 10

#include <iostream>
#include <windows.h>

using namespace std;

//установка курсора на позицию  x y 
void setcur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};


enum EndingOption { WinGame, LooseGame };
enum СardinalDirections { North, East, South, West };

class final
{
private:
    EndingOption gameEndType;       //Парамтр окончания игры
    char winMessage[10];            //Сообщение при победе
    char looseMessage[10];          //Сообщение при проигрыше

public:
    final(EndingOption option, char win_mes[10], char loose_mes[10]);
    final();
    ~final();
    //Изменить параметр окончания
    int changeType(EndingOption option);
    //Вывести сообщение об завершении игры
    int vivodFinal();

};

class entity
{
protected:
    double X_Coord;             //координата по X
    double Y_Coord;             //координата по Y
    int Hit_Points;             //очки здоровья 
    int Damage;                 //урон наносимый
    double speed;               //скорость 
public:
    entity(double x, double y, double sp, int hp, int dm);
    entity();
    ~entity();
    int getEntityCoord(double* x, double* y);
    int getEntityCoord(int* x, int* y);
    int getEntityDamage();
    int getEntityHitPoints();
    int attackEntity(int dm);
    int entityStep(СardinalDirections rotation);


};

class bullet : public entity
{
public:
    bullet(double X_Crd, double Y_Crd, double fX_Crd, double fY_Crd, int dm, double sp);
    bullet();
    ~bullet();

    //получение координат точки назначения пули
    int getBulletCoords(double* fin_x, double* fin_y);
    //движение пули
    int bulletMovment();

private:
    double fin_X_Coord; //конечная координата пули по X
    double fin_Y_Coord; //конечная координата пул по Y
};

class weapon
{
protected:
    int bulletCount;    //количество пуль, выпускаемых за раз
    double speed;       //скорость полета пули
    int damage;         //урон, наносимы пулей
    int type;           //тип оружия: 0 - дробовик, 1 - автомат
    int activeBullets[10];              //список, существующих пуль
    СardinalDirections playerRotation;  //направление взгляда игрока
    int countActiveBullets;
public:
    bullet* bulls[MAX_BULLETS];         //массив пуль

public:
    weapon(int bc, double sp, int tp, int dm);
    weapon();
    ~weapon();
    //получит характеристики оружия
    int getWeaponStat(int* bc, double* sp, int* dm, int* t);
    int getWeaponCountBullets();
    int setActiveBullet(int index, int active);
    int getActiveBullet(int index);
    int changeCountActiveBullets(int change);
    int allBulletMovment();

};

class shotGun : public weapon
{
public:
    int Shot(double X_coord, double Y_coord, int rotation);
};

class avtomat : public weapon
{
public:
    int Shot(double X_coord, double Y_coord, int rotation);
};


class player : public entity
{
public:
    player(double x, double y, double sp, int hp, int dm, СardinalDirections rotation);
    player();
    ~player();
    //перемщение игрока
    int playerStep(СardinalDirections rotation);
    //получение координат игрока
    int getPlayerRotation();
    


private:
    СardinalDirections playerRotation;
public:
    shotGun* gun;                        //оружие игрока

};


class enemy : public entity
{
public:
    enemy(double x, double y, int hp, int dm, double sp);
    enemy();
    ~enemy();
    int enemyMovment(char* map, int Map_Size_X, player* pl);
    int playersVision(char* map, int Map_Size_X, player* pl);

private:

};

class game
{
public:
    game();
    ~game();
    //движение игрока
    int gamePlayerStep(int rot);
    //взаимодействие объектов
    int interaction();
    //вывод текущего состояния игры
    int vivod();
    //получение данных о здоровье игрока
    int getGamePlayerHitPoints();
    //получение данных о здоровье врага
    int getGameEnemyHitPoints();


public:
    int Map_Size_X;         //Размер карты по X
    int Map_Size_Y;         //Размер карты по Y
    char* map;              //карта
    player* you;            //игрок
    enemy* monster;         //враг
};



final ending;

int main()
{
    system("cls");
    game* DOM;
    DOM = new game();

    printf("\e[?25l");
    int i = 1;  //флажок работы игры
    while (i)
    {
        //обработка действий игрока
        if (GetAsyncKeyState(VK_UP))
        {
            DOM->gamePlayerStep(1);
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            DOM->gamePlayerStep(3);
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            DOM->gamePlayerStep(2);
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            DOM->gamePlayerStep(4);
        }
        if (GetAsyncKeyState(VK_BACK))
        {
            double X_Coord, Y_Coord;
            int rotation;
            DOM->you->getEntityCoord(&X_Coord, &Y_Coord);
            rotation = DOM->you->getPlayerRotation();
            DOM->you->gun->Shot(X_Coord, Y_Coord, rotation);
        }

        DOM->monster->enemyMovment(DOM->map, DOM->Map_Size_X, DOM->you);     //движение врага
        DOM->you->gun->allBulletMovment();    //движение пули
        DOM->interaction();      //взаимодействие объектов

        //проверка окончания игры
        if (DOM->getGamePlayerHitPoints() <= 0)
        {
            ending.changeType(LooseGame);
            i = 0;
        }
        if (DOM->getGameEnemyHitPoints() <= 0)
        {
            ending.changeType(WinGame);
            i = 0;
        }

        //вывод состояния игры
        DOM->vivod();
        Sleep(50);


    };
    //завершение игры
    system("cls");
    ending.vivodFinal();
    Sleep(50);


}

final::final(EndingOption option, char w[10], char l[10])
{
    gameEndType = option;
    strcpy(winMessage, w);
    strcpy(looseMessage, l);
}

final::final()
{
    gameEndType = WinGame;
    strcpy(winMessage, "You WIN!");
    strcpy(looseMessage, "You Loose");
}

final::~final()
{
}


int final::changeType(EndingOption option)
{
    gameEndType = option;
    return 0;
}

int final::vivodFinal()
{
    if (gameEndType == 0)
        printf("\n%s\n", winMessage);
    if (gameEndType == 1)
        printf("\n%s\n", looseMessage);
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



player::player(double x, double y, double sp, int hp, int dm, СardinalDirections rotation)
{
    Damage = dm;
    Hit_Points = hp;
    X_Coord = x;
    Y_Coord = y;
    speed = sp;
    playerRotation = rotation;
    gun = new shotGun();
}

player::player()
{
    X_Coord = 8;
    Y_Coord = 1;
    Hit_Points = 100;
    speed = 1;
    Damage = 50;
    playerRotation = North;
    gun = new shotGun();

}

player::~player()
{
}


int player::playerStep(СardinalDirections rotation)
{
    int i = 0;
    playerRotation = rotation;
    switch (rotation)
    {
    case 0: X_Coord -= speed; break;
    case 1: Y_Coord += speed; break;
    case 2: X_Coord += speed; break;
    case 3: Y_Coord -= speed; break;
    default: i = 1;
    }

    return i;

}

int player::getPlayerRotation()
{
    return playerRotation;
}

int weapon::getWeaponCountBullets()
{
    return countActiveBullets;
}
int weapon::setActiveBullet(int index, int active)
{
    activeBullets[index] = active;
    return 0;
}
int weapon::getActiveBullet(int index)
{
    return activeBullets[index];
}
int weapon::changeCountActiveBullets(int change)
{
    countActiveBullets += change;
    return 0;
}

int weapon::allBulletMovment()
{

    for (int i = 0; i < 10; i++)
    {
        //если пуля существует
        if (activeBullets[i] == 1)
        {
            bulls[i]->bulletMovment();
        }

    }
    return 0;
}


bullet::bullet(double X_Crd, double Y_Crd, double fX_Crd, double fY_Crd, int dm, double sp)
{
    X_Coord = X_Crd;
    Y_Coord = Y_Crd;
    fin_X_Coord = fX_Crd;
    fin_Y_Coord = fY_Crd;
    speed = sp;
    Damage = dm;
}

bullet::bullet()
{
    X_Coord = -1;
    Y_Coord = -1;
    fin_X_Coord = -1;
    fin_Y_Coord = -1;
    speed = 0.2;
    Damage = 50;
}

bullet::~bullet()
{
}



int bullet::getBulletCoords(double* fin_x, double* fin_y)
{
    *fin_x = fin_X_Coord;
    *fin_y = fin_Y_Coord;
    return 0;
}

int bullet::bulletMovment()
{
    //движение пули к конечной точке
    if (abs(fin_X_Coord - X_Coord) > abs(fin_Y_Coord - Y_Coord))
    {
        if (fin_X_Coord < X_Coord)
            this->entityStep(North);
        else
            if (fin_X_Coord > X_Coord)
                this->entityStep(South);

    }
    else
    {
        if (fin_Y_Coord > Y_Coord)
            this->entityStep(East);
        else
            if (fin_Y_Coord < Y_Coord)
                this->entityStep(West);
    }

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

    you = new player();
    monster = new enemy();

}

game::~game()
{
}

int enemy::enemyMovment(char* map, int Map_Size_X, player* pl)
{
    int i = 0;      //флаг живого игрока
    double player_x, player_y;
    int roundX, roundY;
    pl->getEntityCoord(&player_x, &player_y);
    roundX = round(X_Coord);
    roundY = round(Y_Coord);

    //если враг живой
    if (Hit_Points > 0)
    {
        if (playersVision(map, Map_Size_X, pl))
        {
            if (abs(X_Coord - player_x) > abs(Y_Coord - player_y))
            {
                if (*(map + (roundX + 1) * Map_Size_X + roundY) != '#' && X_Coord < player_x)
                    this->entityStep(South);
                else
                    if (*(map + (roundX - 1) * Map_Size_X + roundY) != '#' && X_Coord > player_x)
                        this->entityStep(North);

            }
            else
            {
                if (*(map + (roundX)*Map_Size_X + roundY - 1) != '#' && X_Coord > player_y)
                    this->entityStep(West);
                else
                    if (*(map + (roundX)*Map_Size_X + roundY + 1) != '#' && X_Coord < player_y)
                        this->entityStep(East);
            }
        }
        else
        {
            switch (rand() % 4)
            {
            case 0:
                if (*(map + (roundX + 1) * Map_Size_X + roundY) != '#')
                    this->entityStep(South); break;
            case 1:
                if (*(map + (roundX - 1) * Map_Size_X + roundY) != '#')
                    this->entityStep(North); break;
            case 2:
                if (*(map + (roundX)*Map_Size_X + roundY - 1) != '#')
                    this->entityStep(West); break;
            case 3:
                if (*(map + (roundX)*Map_Size_X + roundY + 1) != '#')
                    this->entityStep(East); break;
            }
        }
    }

    return 0;
}

int enemy::playersVision(char* map, int Map_Size_X, player* pl)
{
    double player_x, player_y;
    double x, y;
    int roundX, roundY;
    x = X_Coord;
    y = Y_Coord;

    pl->getEntityCoord(&player_x, &player_y);

    int fl = 1;
    double d = sqrt((x - player_x) * (x - player_x) + (y - player_y) * (y - player_y));

    //проверка: видит ли враг игрока
    while (d > 1 && fl)
    {


        x = (K * player_x + (d - K) * x) / d;
        y = (K * player_y + (d - K) * y) / d;
        d = sqrt((x - player_x) * (x - player_x) + (y - player_y) * (y - player_y));

        roundX = round(x);
        roundY = round(y);

        if (*(map + roundX * Map_Size_X + roundY) == '#')
            fl = 0;

    }

    return fl;
}



int game::gamePlayerStep(int rot)
{
    int HP;
    int fl = 0;
    HP = you->getEntityHitPoints();
    if (HP > 0)
    {
        double x, y;
        int roundX, roundY;
        you->getEntityCoord(&x, &y);
        roundX = round(x);
        roundY = round(y);
        //изменение координат игрока в зависимости от направления
        switch (rot)
        {
        case 1:
            if (*(map + (roundX - 1) * Map_Size_X + roundY) != '#')
                you->playerStep(North);
            else
                fl = 2;
            break;
        case 2:
            if (*(map + (roundX)*Map_Size_X + roundY + 1) != '#')
                you->playerStep(East);
            else
                fl = 2;
            break;
        case 3:
            if (*(map + (roundX + 1) * Map_Size_X + roundY) != '#')
                you->playerStep(South);
            else
                fl = 2;
            break;
        case 4:
            if (*(map + (roundX)*Map_Size_X + roundY - 1) != '#')
                you->playerStep(West);
            else
                fl = 2;
            break;
        default:
            fl = 1;
        }
    }
    return fl;
}

int game::interaction()
{
    //если на карте есть пули
    if (you->gun->getWeaponCountBullets() > 0)
    {
        for (int i = 0; i < 10; i++)
        {
            //если пуля существует
            if (you->gun->getActiveBullet(i) == 1)
            {
                double st_x, st_y;
                double fin_x, fin_y;
                int map_x, map_y;
                you->gun->bulls[i]->getBulletCoords(&fin_x, &fin_y);
                you->gun->bulls[i]->getEntityCoord(&st_x, &st_y);
                map_x = round(st_x);
                map_y = round(st_y);
                //если пуля столкнулась со стеной
                if (*(map + map_x * Map_Size_X + map_y) == '#')
                {
                    delete you->gun->bulls[i];
                    you->gun->setActiveBullet(i, 0);
                    you->gun->changeCountActiveBullets(-1);
                }
                else
                {
                    monster->getEntityCoord(&map_x, &map_y);
                    //если пуля попала во врага
                    if (round(st_x) == map_x && round(st_y) == map_y)
                    {

                        monster->attackEntity(you->gun->bulls[i]->getEntityDamage());
                        delete you->gun->bulls[i];
                        you->gun->setActiveBullet(i, 0);
                        you->gun->changeCountActiveBullets(-1);

                    }
                    else
                    {
                        //если пуля достигла своей конечной точки
                        if (round(st_x) == round(fin_x) && round(st_y) == round(fin_y))
                        {
                            delete you->gun->bulls[i];
                            you->gun->setActiveBullet(i, 0);
                            you->gun->changeCountActiveBullets(-1);
                        }
                    }
                }
            }
        }
    }
    int map_x, map_y;
    int pl_x, pl_y;
    you->getEntityCoord(&pl_x, &pl_y);
    monster->getEntityCoord(&map_x, &map_y);
    //если враг достиг игрока
    if (map_x == pl_x && map_y == pl_y)
    {
        you->attackEntity(monster->getEntityDamage());
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
    if (you->getEntityHitPoints() > 0)
    {
        int rotPlayer;
        you->getEntityCoord(&ent_x, &ent_y);
        rotPlayer = you->getPlayerRotation();

        roundX = round(ent_x);
        roundY = round(ent_y);
        //обозначение игрока в зависимости от направления взгляда
        if (ent_x < Map_Size_X && ent_x >= 0 && ent_y >= 0 && ent_y < Map_Size_Y)
            switch (rotPlayer)
            {
            case 0: mp[roundX * Map_Size_X + roundY] = 'N'; break;
            case 1: mp[roundX * Map_Size_X + roundY] = 'E'; break;
            case 2: mp[roundX * Map_Size_X + roundY] = 'S'; break;
            case 3: mp[roundX * Map_Size_X + roundY] = 'W'; break;
            }
    }

    //если враг живой
    if (monster->getEntityHitPoints() > 0)
    {
        monster->getEntityCoord(&ent_x, &ent_y);
        roundX = round(ent_x);
        roundY = round(ent_y);
        if (ent_x < Map_Size_X && ent_x >= 0 && ent_y >= 0 && ent_y < Map_Size_Y)
            mp[roundX * Map_Size_X + roundY] = 'M';
    }

    //отображение пуль
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (you->gun->getActiveBullet(i) == 1)
        {
            double st_x, st_y;
            double fin_x, fin_y;
            you->gun->bulls[i]->getBulletCoords(&fin_x, &fin_y);
            you->gun->bulls[i]->getEntityCoord(&st_x, &st_y);
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
    return you->getEntityHitPoints();
}

int game::getGameEnemyHitPoints()
{
    return monster->getEntityHitPoints();
}

entity::entity(double x, double y, double sp, int hp, int dm)
{
    Damage = dm;
    Hit_Points = hp;
    X_Coord = x;
    Y_Coord = y;
    speed = sp;

}

entity::entity()
{
    X_Coord = 8;
    Y_Coord = 1;
    Hit_Points = 100;
    speed = 1;
    Damage = 50;
}

entity::~entity()
{
}

int entity::getEntityCoord(double* x, double* y)
{
    *x = X_Coord;
    *y = Y_Coord;
    return 0;
}

int entity::getEntityDamage()
{
    return Damage;
}

int entity::getEntityHitPoints()
{
    return Hit_Points;
}

int entity::attackEntity(int dm)
{
    Hit_Points -= dm;
    return 0;
}

int entity::entityStep(СardinalDirections rotation)
{
    int i = 0;
    switch (rotation)
    {
    case 0: X_Coord -= speed; break;
    case 1: Y_Coord += speed; break;
    case 2: X_Coord += speed; break;
    case 3: Y_Coord -= speed; break;
    default: i = 1;
    }

    return i;

}

int entity::getEntityCoord(int* x, int* y)
{
    *x = round(X_Coord);
    *y = round(Y_Coord);
    return 0;
}

int shotGun::Shot(double X_coord, double Y_coord, int rotation)
{
    double fin_X_coord = 0, fin_Y_coord = 0;


    int d = 0 - bulletCount / 2;
    int fl = 0;
    int j = 0;
    //если оружие выстреливает больше 0 пуль и на карте ни одной пули
    if (bulletCount > 0 && countActiveBullets == 0)
    {
        for (int i = 0; i < bulletCount; i++)
        {

            //выбор типа оружия
            double x, y;
            x = X_coord;
            y = Y_coord;
            //выбор координа в зависимости от направления
            switch (rotation)
            {
            case 0:
                fin_X_coord = X_coord - 4;
                fin_Y_coord = Y_coord + d;
                y += d;
                break;
            case 1:
                fin_X_coord = X_coord + d;
                fin_Y_coord = Y_coord + 4;
                x += d;
                break;
            case 2:
                fin_X_coord = X_coord + 4;
                fin_Y_coord = Y_coord + d;
                y += d;
                break;
            case 3:
                fin_X_coord = X_coord + d;
                fin_Y_coord = Y_coord - 4;
                x += d;
                break;
            }
            d += 1;
            // инициализация пуль
            for (int fl = 1; j < 10 && fl; j++)
                if (activeBullets[j] == 0)
                {
                    bulls[j] = new bullet(x, y, fin_X_coord, fin_Y_coord, damage, speed);
                    countActiveBullets += 1;
                    activeBullets[j] = 1;
                    fl = 0;
                }
        }
    }
    else
        fl = 1;
    return fl;
}

int avtomat::Shot(double X_coord, double Y_coord, int rotation)
{
    double fin_X_coord = 0, fin_Y_coord = 0;

    int d = 0 - bulletCount / 2;
    int fl = 0;
    int j = 0;
    //если оружие выстреливает больше 0 пуль и на карте ни одной пули
    if (bulletCount > 0 && countActiveBullets == 0)
    {
        //выбор типа оружия
        double x, y;
        x = X_coord;
        y = Y_coord;
        //выбор координа в зависимости от направления
        switch (rotation)
        {
        case 0:
            fin_X_coord = X_coord - 10;
            fin_Y_coord = Y_coord;
            X_coord -= d;
            break;
        case 1:
            fin_X_coord = X_coord;
            fin_Y_coord = Y_coord + 10;
            Y_coord += d;
            break;
        case 2:
            fin_X_coord = X_coord + 10;
            fin_Y_coord = Y_coord;
            X_coord += d;
            break;
        case 3:
            fin_X_coord = X_coord;
            fin_Y_coord = Y_coord - 10;
            Y_coord -= d;
            break;
        }
        d += 1;
        // инициализация пуль
        for (int fl = 1; j < 10 && fl; j++)
            if (activeBullets[j] == 0)
            {
                bulls[j] = new bullet(x, y, fin_X_coord, fin_Y_coord, damage, speed);
                countActiveBullets += 1;
                activeBullets[j] = 1;
                fl = 0;
            }
    }
    else
        fl = 1;
    return fl;
}