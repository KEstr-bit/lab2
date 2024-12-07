﻿#include "drawer.h"
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


void drawer::drawImage(sf::RenderWindow& window, const sf::Texture* texture, float x, float y, float width, float height) {
    // Создаем спрайт и устанавливаем текстуру
    sf::Sprite sprite;
    sprite.setTexture(*texture);

    // Устанавливаем позицию спрайта
    sprite.setPosition(x, y);

    // Рассчитываем масштаб для изменения размера
    float scaleX = width / (*texture).getSize().x;  // Масштаб по оси X
    float scaleY = height / (*texture).getSize().y; // Масштаб по оси Y
    sprite.setScale(scaleX, scaleY);                // Применяем масштаб

    // Рисуем спрайт в окне
    window.draw(sprite);
}


void drawer::dependSorting(std::vector<double> &mainMas, std::vector<entity*> &sideMas, int left, int right) {
    //Указатели в начало и в конец массива
    int i = left, j = right;

    //Центральный элемент массива
    double mid = mainMas[(left + right) / 2];

    //Делим массив
    do {

        while (mainMas[i] > mid) {
            i++;
        }

        while (mainMas[j] < mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {

            std::swap(sideMas[i], sideMas[j]);
            std::swap(mainMas[i], mainMas[j]);

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if (left < j)
        dependSorting(mainMas, sideMas, left, j);
    if (i < right)
        dependSorting(mainMas, sideMas, i, right);
}

double drawer::getRotAngle(double playerAngle, double cosPlEnLine, double sinPlEnLine) {
    double cosRotAngle = cos(helper::degToRad(playerAngle)) * cosPlEnLine + sin(helper::degToRad(playerAngle)) * sinPlEnLine;
    double sinRotAngle = sin(helper::degToRad(playerAngle)) * cosPlEnLine - cos(helper::degToRad(playerAngle)) * sinPlEnLine;

    if (cosRotAngle > 1)
        cosRotAngle = 1;

    if (cosRotAngle < -1)
        cosRotAngle = -1;

    //угол на который игроку нужно повернуться, чтобы смотреть ровно на объект
    double rotAngle = helper::radToDeg(acos(cosRotAngle));

    if (sinRotAngle < 0)
        rotAngle *= -1;

    //если объект находится за обзором игрока
    rotAngle = round(rotAngle * 1000) / 1000.0;
    return rotAngle;
}

void drawer::entityDraw(game* gm, sf::RenderWindow& window) {
    double EntityCoordX, EntityCoordY;
    double PlayerCoordX, PlayerCoordY;

    int countEnt = gm->getCountEntity();
    if (countEnt < 1)
        throw std::out_of_range("В игре не осталось entity");

    if(gm->you->getEntityCoord(&PlayerCoordX, &PlayerCoordY))
        throw std::logic_error("В игре не осталось entity");

    std::vector<double> distToEntity;       //вектор расстояний до объектов
    std::vector<entity*> pointersEntity;    //вектор указателей на объекты

    //заполнение векторов distToEntity и pointersEntity
    for (int i = 0; i < countEnt; i++)
    {
        entity* e = gm->getEntityByIndex(i);
        e->getEntityCoord(&EntityCoordX, &EntityCoordY);
        distToEntity.emplace_back(helper::calcDistance(EntityCoordX, EntityCoordY, PlayerCoordX, PlayerCoordY));
        pointersEntity.emplace_back(e);
    }

    //сортировка по убыванию расстояний
    dependSorting(distToEntity, pointersEntity, 0, distToEntity.size() - 1);

    double playerAngle = gm->you->getEntityAngle();

    for (int i = 0; i < countEnt; i++)
    {
        double distance = distToEntity[i];
        entity* e = pointersEntity[i];

        e->getEntityCoord(&EntityCoordX, &EntityCoordY);

        double spriteSize = e->getSize();

        double cosPlEnLine = (EntityCoordX - PlayerCoordX) / distance;
        double sinPlEnLine = (EntityCoordY - PlayerCoordY) / distance;

        double rotAngle = getRotAngle(playerAngle, cosPlEnLine, sinPlEnLine);
        if (abs(rotAngle) > gm->you->FOV)
            continue;

        int vertLineNum = SCREEN_WIDTH * rotAngle / gm->you->FOV;       //номер вертикальной полосы

        vertLineNum += SCREEN_WIDTH / 2;

        spriteSize *= SCREEN_HEIGHT / distance;

        //отрисовка объекта
        drawImage(window, gm->tPack->getTexture(e->getTextureType()), vertLineNum - spriteSize / 2, (SCREEN_HEIGHT - spriteSize) / 2, spriteSize, spriteSize);

        vertLineNum -= spriteSize / 2;
        int rightBorder = vertLineNum + spriteSize + 2;

        if (vertLineNum < 0)
            vertLineNum = 0;

        if (rightBorder > SCREEN_WIDTH)
            rightBorder = SCREEN_WIDTH;

        //отрисовка вертикальных полос, перекрывающих объект
        for (; vertLineNum < rightBorder; vertLineNum++)
        {
            //если вертикальная полоса находится позади объекта
            if (mas[vertLineNum] > distance)
                continue;

            double len = SCREEN_HEIGHT / distance;

            //вычисление цвета вертикальной полосы
            double Ws = 255 / sqrt(mas[vertLineNum]);
            if (Ws > 255)
                Ws = 255;

            drawVerticalSegment(window, len, 1, vertLineNum, (SCREEN_HEIGHT - len) / 2, sf::Color(Ws, Ws, Ws));
        }



    }
}

void drawer::drawWalls(GameMap* map, game* gm, sf::RenderWindow& window) {
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

            double currentCosinus = cos(helper::degToRad(curentPlayerAngle));
            double currentSinus = sin(helper::degToRad(curentPlayerAngle));


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
                    distance = distance * cos(helper::degToRad(curentPlayerAngle - realPlayerAngle));

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
            curentPlayerAngle = atan(tan(helper::degToRad(curentPlayerAngle - realPlayerAngle)) - (2 * tan(helper::degToRad(gm->you->FOV * 0.5)) / SCREEN_WIDTH));
            curentPlayerAngle = helper::radToDeg(curentPlayerAngle);
            curentPlayerAngle += realPlayerAngle;
        }
    }
}


