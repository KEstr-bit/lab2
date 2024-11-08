#include "drawer.h"
#include <iostream>
#include "helper.h"

const double drawer::RAY_STEP = 0.01;

drawer::drawer()
{
    for (int i = 0; i < SCREEN_WIDTH; i++)
        mas[i] = 0;

}

drawer::~drawer()
{
}

void drawer::drawVerticalSegment(sf::RenderWindow& window, float length, float width, float x, float y, sf::Color color) {
    //вертикальный отрезок
    sf::RectangleShape segment(sf::Vector2f(width, length));

    segment.setPosition(x, y);

    //цвет отрезка
    segment.setFillColor(color);

    //рисование
    window.draw(segment);
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

int drawer::entityDraw(game* gm, sf::RenderWindow& window) {
    double EntityCoordX, EntityCoordY;
    double PlayerCoordX, PlayerCoordY;


        gm->monster->getEntityCoord(&EntityCoordX, &EntityCoordY);
        gm->you->getEntityCoord(&PlayerCoordX, &PlayerCoordY);

        double playerAngle = gm->you->getEntityAngle();

        double distance = calcDistance(EntityCoordX, EntityCoordY, PlayerCoordX, PlayerCoordY);

        double cosPlEnLine = (EntityCoordX - PlayerCoordX) / distance;
        double sinPlEnLine = (EntityCoordY - PlayerCoordY) / distance;

        double cosRotAngle = cos(degToRad(playerAngle)) * cosPlEnLine + sin(degToRad(playerAngle)) * sinPlEnLine;
        double sinRotAngle = sin(degToRad(playerAngle)) * cosPlEnLine - cos(degToRad(playerAngle)) * sinPlEnLine;

        double rotAngle = radToDeg(acos(cosRotAngle));

        if (sinRotAngle < 0)
            rotAngle *= -1;

        if (abs(rotAngle) < gm->you->FOV)
        {

            int vertLineNum = SCREEN_WIDTH * rotAngle / gm->you->FOV;

            vertLineNum += SCREEN_WIDTH / 2;

            double spriteSize = SCREEN_HEIGHT / distance;

            sf::Texture texture;
            if (!texture.loadFromFile("image.png")) {
                return -1; // Выход, если не удалось загрузить изображение
            }


            drawImage(window, texture, vertLineNum - spriteSize / 2, (SCREEN_HEIGHT - spriteSize) / 2, spriteSize, spriteSize);

            vertLineNum -= spriteSize / 2;
            for (int j = vertLineNum + spriteSize + 1; vertLineNum <= j; vertLineNum++)
            {
                if (mas[vertLineNum] > distance)
                    continue;

                double len = SCREEN_HEIGHT / distance;

                double Ws = 255 / sqrt(mas[vertLineNum]);
                if (Ws > 255)
                    Ws = 255;

                drawVerticalSegment(window, len, 1, vertLineNum, (SCREEN_HEIGHT - len) / 2, sf::Color(Ws, Ws, Ws));
            }
        }
        return 0;
    
}

int drawer::newDraw(GameMap* map, game* gm, sf::RenderWindow& window) {
    double EntityCoordX, EntityCoordY;


    if (!gm->you->getEntityCoord(&EntityCoordX, &EntityCoordY))
    {
        double realPlayerAngle = gm->you->getEntityAngle();
        double curentPlayerAngle = realPlayerAngle;

        curentPlayerAngle += gm->you->FOV / 2.0;

        for (int i = 0; i < SCREEN_WIDTH; i++)
        {
            //флаг найденной стены в этом направлении
            bool flNotWall = true;

            double currentCosinus = cos(degToRad(curentPlayerAngle));
            double currentSinus = sin(degToRad(curentPlayerAngle));


            //поиск стены на пути луча
            for (double distance = RAY_STEP; distance < 10 && flNotWall; distance += RAY_STEP)
            {
                double x = distance * currentCosinus;
                double y = distance * currentSinus;

                x += EntityCoordX;
                y += EntityCoordY;

                //если стена
                if (map->isWall(x, y))
                {
                    //исправление эффекта рыбьего глаза по оси Y
                    distance = distance * cos(degToRad(curentPlayerAngle - realPlayerAngle));

                    mas[i] = distance;

                    double len = SCREEN_HEIGHT / distance;

                    //цвет полосы
                    double Ws = 255 / sqrt(distance);
                    if (Ws > 255)
                        Ws = 255;

                    drawVerticalSegment(window, len, 1, i, (SCREEN_HEIGHT - len)/2, sf::Color(Ws, Ws, Ws));

                    flNotWall = false;
                }

            }
            //исправление эффекта рыбьего глаза по оси X
            curentPlayerAngle = atan(tan(degToRad(curentPlayerAngle - realPlayerAngle)) - (2 * tan(degToRad(gm->you->FOV * 0.5)) / SCREEN_WIDTH));
            curentPlayerAngle = radToDeg(curentPlayerAngle);
            curentPlayerAngle += realPlayerAngle;
        }
    }
        return 0;
}


