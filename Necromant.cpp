#include "Necromant.h"

#include "Archer.h"
#include "Bomber.h"

Necromant::Necromant(double coordX, double coordY, double speed, int hitPoints, int damage, Player* player)
{
    this->damage = damage;
    this->hitPoints = hitPoints;
    this->cordX = coordX;
    this->cordY = coordY;
    this->speed = speed;
    this->player = player;
    size = 2;
    texture = NEGROMANT;
    avt = new shotGun();
}

Necromant::Necromant(Player* player)
{
    damage = 50;
    hitPoints = 500;
    cordX = 1;
    cordY = 8;
    speed = 0.02;
    this->player = player;
    size = 2;
    texture = NEGROMANT;
    avt = new shotGun();
}

bool Necromant::update(GameMap* map, std::vector<Entity*>& entities)
{
    static int shift = 0;
    frameShift();
    avt->update();
    if (textureY == 2.0 && textureX == TexturePack::FRAMES_COUNT / 2.0)
        if (!avt->shot(cordX, cordY, viewAngle, entities))
            avt->reloading();

    if (textureY == 4.0 && textureX == TexturePack::FRAMES_COUNT / 2.0)
        respawn(map, entities);

    if (eventFl)
        return false;

    if (!this->isAlive())
        return true;

    double playerX, playerY;
    player->getEntityCord(&playerX, &playerY);

    double deltaX = playerX - this->cordX;
    double deltaY = playerY - this->cordY;

    //если враг видит игрока
    if (playersVision(map))
    {
        double distance = helper::calcDistance(playerX, playerY, this->cordX, this->cordY);
        double angleCos = deltaX / distance;
        double angleSin = deltaY / distance;
        this->viewAngle = helper::radToDeg(atan2(angleSin, angleCos));

        if (distance > 5)
            this->entityMapStep(map);

            if(rand()%50 == 0)
            {
	            if(rand()%2)
	            {
                    textureY = 2;
                    textureX = 0;
                    eventFl = true;
	            }
                else
                {
                    textureY = 4;
                    textureX = 0;
                    eventFl = true;
                }
            }
        
        

    }

    return false;

}

void Necromant::respawn(GameMap* map, std::vector<Entity*>& entities)
{
    double angle = viewAngle;
    angle -= 45;
    for(int i = 0; i < 4; i++)
    {
        angle += 90;
        double x, y;
        x = 2 * cos(helper::degToRad(angle)) + cordX;
        y = 2 * sin(helper::degToRad(angle)) + cordY;
        if (!map->isWall(x, y))
        {
	        if(rand()%2)
	        {
                entities.emplace_back(new Bomber(x, y, 0.06, 100, 200, player));
	        }
            else
            {
                entities.emplace_back(new Archer(x, y, 0.02, 100, 200, player));
            }
        }
    }
}

Necromant::~Necromant()
{
}
