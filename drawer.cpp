#include "Drawer.h"
#include "Helper.h"

const double Drawer::RAY_STEP = 0.01;

Drawer::Drawer()
{
    for (auto& it : lengthsAndIndexes)
    {
	    it[0] = 0;
	    it[1] = 0;
    }
}

Drawer::~Drawer()
{
}

void Drawer::drawVerticalSegment(sf::RenderWindow& window, const float length, const float stripIndex, const float x, const float y, const sf::Texture& texture) {

    sf::Sprite stripeSprite(texture);

    // Устанавливаем текстуру только для нужной полосы шириной в 1 пиксель
    const sf::IntRect textureRect(stripIndex, 0, 1, (texture).getSize().y); // 1 пиксель шириной, вся высота текстуры
    stripeSprite.setTextureRect(textureRect);

    // Устанавливаем позицию спрайта
    stripeSprite.setPosition(x, y);

    // Масштабируем спрайт по высоте, чтобы сделать полоску нужной длины
    stripeSprite.setScale(1.0, length / (texture).getSize().y);

    // Рисуем полоску в окне
    window.draw(stripeSprite);
}


void Drawer::drawImage(sf::RenderWindow& window, const sf::Texture& texture, const float x, const float y, const float textureX, const float textureY, const float width, const float height) {
    // Создаем спрайт и устанавливаем текстуру
    sf::Sprite sprite(texture);

    sf::IntRect textureRect(Helper::round(textureX) * 128, textureY * 128, 128, 128);
    sprite.setTextureRect(textureRect);

    // Устанавливаем позицию спрайта
    sprite.setPosition(x, y);

    // Рассчитываем масштаб для изменения размера
    const float scaleX = width / 128;  // Масштаб по оси X
    const float scaleY = height / 128; // Масштаб по оси Y
    sprite.setScale(scaleX, scaleY);                // Применяем масштаб

    // Рисуем спрайт в окне
    window.draw(sprite);
}

void Drawer::entityDraw(const Game& gm, sf::RenderWindow& window) const
{
    double entityCordX, entityCordY;
    double playerCordX, playerCordY;

    const int countEntities = gm.getCountEntity();
    if (countEntities < 1)
        throw std::out_of_range("В игре не осталось entity");

    gm.player->getCords(playerCordX, playerCordY);
    if(!gm.player->isAlive())
        throw std::logic_error("В игре не осталось entity");

    std::vector<double> distToEntity;       //вектор расстояний до объектов
    std::vector<Entity*> pointersEntity;    //вектор указателей на объекты

    //заполнение векторов distToEntity и pointersEntity
    for (int i = 0; i < countEntities; i++)
    {
        Entity* e = gm.getEntityByIndex(i);
        e->getCords(entityCordX, entityCordY);
        distToEntity.emplace_back(Helper::calcDistance(entityCordX, entityCordY, playerCordX, playerCordY));
        pointersEntity.emplace_back(e);
    }

    //сортировка по убыванию расстояний
    Helper::dependSorting(distToEntity, pointersEntity, 0, static_cast<int>(distToEntity.size()) - 1);

    const double playerAngle = gm.player->getAngle();

    for (int i = 0; i < countEntities; i++)
    {
	    const double distance = distToEntity[i];
        Entity* e = pointersEntity[i];

        e->getCords(entityCordX, entityCordY);

        double spriteSize = e->size;

	    const double cosPlEnLine = (entityCordX - playerCordX) / distance;
	    const double sinPlEnLine = (entityCordY - playerCordY) / distance;

	    const double rotAngle = Helper::getRotationAngle(Helper::degToRad(playerAngle), cosPlEnLine, sinPlEnLine);
        if (abs(rotAngle) > Player::FOV)
	       continue;

        int vertLineNum = static_cast<int>(Helper::round(SCREEN_WIDTH * rotAngle / Player::FOV));       //номер вертикальной полосы

        vertLineNum += SCREEN_WIDTH / 2;

        spriteSize *= SCREEN_HEIGHT / distance;

        Animations animation;
        int frame;
        e->getAnimationState(animation, frame);
        //отрисовка объекта
        if(e->size > 1)
        {
            drawImage(window, *gm.texture_pack->getTexture(e->texture), vertLineNum - spriteSize / 2,
                SCREEN_HEIGHT/2 - spriteSize + SCREEN_HEIGHT / (2*distance), frame, animation, spriteSize, spriteSize);
        }
        else
        {

            drawImage(window, *gm.texture_pack->getTexture(e->texture), vertLineNum - spriteSize / 2,
                (SCREEN_HEIGHT - spriteSize) / 2, frame, animation, spriteSize, spriteSize);
        }
        vertLineNum -= static_cast<int>(spriteSize / 2);
        int rightBorder = static_cast<int>(vertLineNum + spriteSize + 2);

        if (vertLineNum < 0)
            vertLineNum = 0;

        if (rightBorder > SCREEN_WIDTH)
            rightBorder = SCREEN_WIDTH;

        //отрисовка вертикальных полос, перекрывающих объект
        for (; vertLineNum < rightBorder; vertLineNum++)
        {
            //если вертикальная полоса находится позади объекта
            if (lengthsAndIndexes[vertLineNum][0] > distance)
                continue;

            const double len = SCREEN_HEIGHT / lengthsAndIndexes[vertLineNum][0];


            drawVerticalSegment(window, len, lengthsAndIndexes[vertLineNum][1], vertLineNum, (SCREEN_HEIGHT - len) / 2,*gm.texture_pack->getTexture(WALLS));
        }



    }
}

void Drawer::drawPlayerWeapon(const Game& gm, sf::RenderWindow& window)
{
	Animations animation;
	int frame;
	gm.player->getActiveWeapon()->getAnimationState(animation, frame);
	drawImage(window, *gm.texture_pack->getTexture(gm.player->getActiveWeapon()->texture), SCREEN_WIDTH - SCREEN_HEIGHT,
	          SCREEN_HEIGHT / 3, frame, animation, SCREEN_HEIGHT/1.5, SCREEN_HEIGHT/1.5);
}

void Drawer::drawWalls(GameMap& map, const Game& gm, sf::RenderWindow& window) {
    double entityCordX, entityCordY;

    gm.player->getCords(entityCordX, entityCordY);
    if (gm.player->isAlive())
    {
	    const double realPlayerAngle = gm.player->getAngle();
        double currentPlayerAngle = realPlayerAngle;

        currentPlayerAngle += Player::FOV / 2.0;

        for (int i = 0; i < SCREEN_WIDTH; i++)
        {
            //флаг найденной стены в этом направлении
            bool flNotWall = true;

            const double currentCosines = cos(Helper::degToRad(currentPlayerAngle));
            const double currentSinus = sin(Helper::degToRad(currentPlayerAngle));


            //поиск стены на пути луча
            for (double distance = RAY_STEP; distance < 10 && flNotWall; distance += RAY_STEP)
            {
                double x = distance * currentCosines;
                double y = distance * currentSinus;

                x += entityCordX;
                y += entityCordY;

                //если стена
                if (map.isWall(x, y))
                {
                    //исправление эффекта рыбьего глаза по оси Y
                    distance = distance * cos(Helper::degToRad(currentPlayerAngle - realPlayerAngle));


                    const double len = SCREEN_HEIGHT / distance;

                    //цвет полосы
                    const float dx = x - Helper::round(x) + 0.5;
                    const float dy = y - Helper::round(y) + 0.5;
                    float stripIndex = (dx + dy) * 128;
                    if (stripIndex > 128)
                        stripIndex -= 128;

                    stripIndex += map.whatIsWall(x, y) * 128;

                    lengthsAndIndexes[i][0] = distance;
                    lengthsAndIndexes[i][1] = stripIndex;


                    drawVerticalSegment(window, len, stripIndex, i, (SCREEN_HEIGHT - len)/2, *gm.texture_pack->getTexture(WALLS));

                    flNotWall = false;
                }

            }
            //исправление эффекта рыбьего глаза по оси X
            currentPlayerAngle = atan(tan(Helper::degToRad(currentPlayerAngle - realPlayerAngle)) - (2 * tan(Helper::degToRad(
	            Player::FOV * 0.5)) / SCREEN_WIDTH));
            currentPlayerAngle = Helper::radToDeg(currentPlayerAngle);
            currentPlayerAngle += realPlayerAngle;
        }
    }
}


