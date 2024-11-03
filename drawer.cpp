#include "drawer.h"
#include <iostream>
#include "helper.h"

drawer::drawer()
{
	firstBuffer = (char*)calloc(MAP_SIZE_X * MAP_SIZE_Y, sizeof(char));
	secondBuffer = (char*)calloc(MAP_SIZE_X * MAP_SIZE_Y, sizeof(char));
}

drawer::~drawer()
{
}

int drawer::draw(char world_Map[MAP_SIZE_X][MAP_SIZE_Y], game* gm)
{
    int EntityCoordX, EntityCoordY;

    //копирование карты в динамический массив
    for (int i = 0; i < MAP_SIZE_X; i++)
        for (int j = 0; j < MAP_SIZE_Y; j++)
        {
            firstBuffer[i * MAP_SIZE_X + j] = world_Map[i][j];
        }


    //если игрок живой
    if (!gm->you->getEntityCoord(&EntityCoordX, &EntityCoordY))
    {
        СardinalDirections rotPlayer;
        rotPlayer = gm->you->getPlayerDirection();

        switch (rotPlayer)
        {
        case North: firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'N'; break;
        case East: firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'E'; break;
        case South: firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'S'; break;
        case West: firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'W'; break;
        }
    }

    if (!gm->monster->getEntityCoord(&EntityCoordX, &EntityCoordY))
    {
        firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'M';
    }

    //отображение пуль
    for (int i = 0; i < gm->bullets.size(); i++)
    {

            gm->bullets[i].getEntityCoord(&EntityCoordX, &EntityCoordY);
            firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = '0';

    }

    

    setcur(0, 0);
    //вывод новой карты
    for (int i = 0; i < MAP_SIZE_X; i++)
    {
        for (int j = 0; j < MAP_SIZE_Y; j++)
        {
            if (firstBuffer[i * MAP_SIZE_X + j] != secondBuffer[i * MAP_SIZE_X + j])
            {
                setcur(2 * j, i);
                std::cout << firstBuffer[i * MAP_SIZE_X + j] << " ";
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < MAP_SIZE_X; i++)
        for (int j = 0; j < MAP_SIZE_Y; j++)
        {
            secondBuffer[i * MAP_SIZE_X + j] = firstBuffer[i * MAP_SIZE_X + j];
        }
    return 0;
}

void drawer::drawVerticalSegment(sf::RenderWindow& window, float length, float width, float low_X, float low_Y, sf::Color color) {
    //вертикальный отрезок
    sf::RectangleShape segment(sf::Vector2f(width, length));

    segment.setPosition(low_X - width / 2, low_Y - length);

    //цвет отрезка
    segment.setFillColor(color);

    //рисование
    window.draw(segment);
}

int drawer::newDraw(char world_Map[MAP_SIZE_X][MAP_SIZE_Y], game* gm, sf::RenderWindow& window) {
    int EntityCoordX, EntityCoordY;


    if (!gm->you->getEntityCoord(&EntityCoordX, &EntityCoordY))
    {
        double corner = gm->you->visionCorner;
        double realCorner = corner;
        corner += gm->you->FOV / 2;
        for (int i = 0; i < 800; i++)
        {

            //сдвиг угла на ??? 



            //флаг найденной стены в этом направлении
            bool fl = true;

            double cosi = cos((corner * 3.14) / 180);
            double sinu = sin((corner * 3.14) / 180);


            //поиск стены на пути луча
            for (double distance = 0.01; distance < 10 && fl; distance += 0.01)
            {
                int x = distance * cosi;
                int y = distance * sinu;

                x += EntityCoordX;
                y += EntityCoordY;

                //если стена
                if (isWall(world_Map[0], 10, x, y))
                {
                    distance = distance * cos(((corner - realCorner) * 3.14) / 180);
                    double topWall = 600 / 2 - 500 / distance;
                    double lowWall = 600 - topWall;
                    double len = 600 / distance;
                    //цвет полосы
                    double Ws = 300 / sqrt(distance);
                    if (Ws > 255)
                        Ws = 255;

                    drawVerticalSegment(window, lowWall - topWall, 1, i, lowWall, sf::Color(Ws, Ws, Ws));

                    fl = false;
                }

            }

            corner = atan(tan((corner - realCorner) * 3.14 / 180.0) - ((90 * 3.14 / 180) * tan((gm->you->FOV * 0.5) * 3.14 / 180.0) / 801.0));
            corner = corner * 180 / 3.14;
            corner += realCorner;
        }
    }
        return 0;
}
