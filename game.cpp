#include <iostream>
#include "game.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "helper.h"

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




int game::gamePlayerStep(СardinalDirections rot)
{
    
    int fl = 0;
    if (you->getEntityHitPoints() > 0)
    {
        int roundX, roundY;
        you->getEntityCoord(&roundX, &roundY);

        
        //изменение координат игрока в зависимости от направления
        switch (rot)
        {
        case North:
            if (*(map + (roundX - 1) * Map_Size_X + roundY) != '#')
                you->playerStep(North);
            else
                fl = 2;
            break;
        case East:
            if (*(map + (roundX)*Map_Size_X + roundY + 1) != '#')
                you->playerStep(East);
            else
                fl = 2;
            break;
        case South:
            if (*(map + (roundX + 1) * Map_Size_X + roundY) != '#')
                you->playerStep(South);
            else
                fl = 2;
            break;
        case West:
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
            std::cout << mp[i * Map_Size_X + j] << " ";
        }
        std::cout << std::endl;
    }
    free(mp);
    return 0;
}
