#include "Archer.h"

Archer::Archer(double coordX, double coordY, double speed, int hitPoints, int damage, Player* player)
{
    this->damage = damage;
    this->hitPoints = hitPoints;
    this->cordX = coordX;
    this->cordY = coordY;
    this->speed = speed;
    this->player = player;
    avt = new Rifle();
}


Archer::Archer(Player* player)
{
    damage = 50;
    hitPoints = 100;
    cordX = 1;
    cordY = 8;
    speed = 0.01;
    this->player = player;
    avt = new Rifle();
}

bool Archer::update(GameMap* map, std::vector<Entity*>& entities)
{
    static int shift = 0;
    frameShift();
    avt->update();

    if (textureY == 2.0 && textureX == TexturePack::FRAMES_COUNT / 2.0)
        if (!avt->shot(cordX, cordY, viewAngle, entities))
            avt->reloading();

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
        double distance = Helper::calcDistance(playerX, playerY, this->cordX, this->cordY);
        double angleCos = deltaX / distance;
        double angleSin = deltaY / distance;
        this->viewAngle = Helper::radToDeg(atan2(angleSin, angleCos));
        double angle = viewAngle;
        if(distance > 5)
			this->entityMapStep(map);
        else if (distance < 3)
        {
            viewAngle -= 180;
            this->entityMapStep(map);
        }
        else
        {
            if (!(rand() % 50))
            {
                textureX = 0;
                textureY = 2;
                eventFl = true;
            }

            
            if (textureX == 0.0)
            {
            	if(rand() % 2)
					shift = -90;
				else
            		shift = 90;
            }

            viewAngle += shift;
            if (this->entityMapStep(map))
                shift = -shift;

           
        }
        viewAngle = angle;

    }

    return false;
    

    

}

Archer::~Archer()
{
}
