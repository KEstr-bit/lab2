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
        firstBuffer[EntityCoordX * MAP_SIZE_X + EntityCoordY] = 'N';
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

void drawRedSquare(sf::RenderWindow& window, float x, float y, float size) {
    // Создаем квадрат (прямоугольник)
    sf::RectangleShape square(sf::Vector2f(size, size));

    // Устанавливаем его цвет
    square.setFillColor(sf::Color::Red);

    // Устанавливаем позицию квадрата
    square.setPosition(x, y);

    // Рисуем квадрат в окне
    window.draw(square);
}

void drawImage(sf::RenderWindow& window, const sf::Texture& texture, float x, float y, float width, float height) {
    // Создаем спрайт и устанавливаем текстуру
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // Устанавливаем позицию спрайта
    sprite.setPosition(x, y);

    // Рассчитываем масштаб для изменения размера
    float scaleX = width / texture.getSize().x;  // Масштаб по оси X
    float scaleY = height / texture.getSize().y; // Масштаб по оси Y
    sprite.setScale(scaleX, scaleY);              // Применяем масштаб

    // Рисуем спрайт в окне
    window.draw(sprite);
}

int drawer::entityDraw(char world_Map[MAP_SIZE_X][MAP_SIZE_Y], game* gm, sf::RenderWindow& window) {
    double EntityCoordX, EntityCoordY;
    double PlayerCoordX, PlayerCoordY;


        gm->monster->getEntityCoord(&EntityCoordX, &EntityCoordY);
        gm->you->getEntityCoord(&PlayerCoordX, &PlayerCoordY);

        double corner = gm->you->visionCorner;

        double distance = sqrt(pow(EntityCoordX - PlayerCoordX, 2) + pow(PlayerCoordY - EntityCoordY, 2));
        if (distance > 10)
            return 1;

        double cosi = (EntityCoordX - PlayerCoordX) / distance;
        double sinu = (EntityCoordY - PlayerCoordY) / distance;

        double cosi2 = cos(corner * 3.14 / 180) * cosi + sin(corner * 3.14 / 180) * sinu;
        double sinu2 = sin(corner * 3.14 / 180) * cosi - cos(corner * 3.14 / 180) * sinu;

        double corner2 = acos(cosi2) * 180 / 3.14;

        if (sinu2 < 0)
            corner2 *= -1;

        if (abs(corner2) > gm->you->FOV / 2)
            return 2;

        int i = 400 * corner2 / (gm->you->FOV / 2);

        i += 400;

        double size = 800 / distance;

        sf::Texture texture;
         if (!texture.loadFromFile("image.png")) {
            return -1; // Выход, если не удалось загрузить изображение
        }


        drawImage(window, texture, i - size / 2, 300 - size / 2, size, size);

        i -= size / 2;
        for (int j = i + size + 2; i < j; i++)
        {
            if (mas[i] > distance)
                continue;

            double topWall = 600 / 2 - 500 / mas[i];
            double lowWall = 600 - topWall;
            double Ws = 300 / sqrt(mas[i]);
            if (Ws > 255)
                Ws = 255;

            drawVerticalSegment(window, lowWall - topWall, 1, i, lowWall, sf::Color(Ws, Ws, Ws));
        }
    
        return 0;
    
}

int drawer::newDraw(char world_Map[MAP_SIZE_X][MAP_SIZE_Y], game* gm, sf::RenderWindow& window) {
    double EntityCoordX, EntityCoordY;


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
                double x = distance * cosi;
                double y = distance * sinu;

                x += EntityCoordX;
                y += EntityCoordY;

                //если стена
                if (isWall(world_Map[0], 10, round(x), round(y)))
                {
                    
                    distance = distance * cos(((corner - realCorner) * 3.14) / 180);
                    mas[i] = distance;
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

            corner = atan(tan((corner - realCorner) * 3.14 / 180.0) - (2 * tan((gm->you->FOV * 0.5) * 3.14 / 180.0) / 801.0));
            corner = corner * 180 / 3.14;
            corner += realCorner;
        }
    }
        return 0;
}


