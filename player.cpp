#include "player.h"


int player::gamePlayerStep(char* world_Map, ÑardinalDirections step_Direction)
{

    int fl = 0;
    if (hitPoints > 0)
    {
        double x, y;
        this->getEntityCoord(&x, &y);


        //èçìåíåíèå êîîðäèíàò èãðîêà â çàâèñèìîñòè îò íàïðàâëåíèÿ
        this->playerStep(step_Direction);
        double newX, newY;
        double dX, dY;
        this->getEntityCoord(&newX, &newY);
        try
        {
            if (isWall(world_Map, MAP_SIZE_X, roundd(newX), roundd(newY)))
            {
                dX = newX - x;
                dY = newY - y;
                if (!isWall(world_Map, MAP_SIZE_X, roundd(x + dX), roundd(y)))
                {
                    this->coordX = x + dX;
                    this->coordY = y;
                }
                else if (!isWall(world_Map, MAP_SIZE_X, roundd(x), roundd(y + dY)))
                {
                    this->coordX = x;
                    this->coordY = y + dY;
                }
                else
                {
                    this->coordX = x;
                    this->coordY = y;
                }
            }
        }
        catch (const std::exception&)
        {
            this->coordX = x;
            this->coordY = y;
        }
    }
    return fl;
}

player::player(double coord_X, double coord_Y, double entity_Speed, int hit_Points, int entity_Damage)
{
    damage = entity_Damage;
    hitPoints = hit_Points;
    coordX = coord_X;
    coordY = coord_Y;
    speed = entity_Speed;
    activeWeapon = ShotGun;
    firstGun = new shotGun();
    secondGun = new avtomat();

    visionCorner = 0;
}

player::player()
{
    coordX = 7;
    coordY = 2;
    hitPoints = 100;
    speed = 0.05;
    damage = 50;
    activeWeapon = ShotGun;
    firstGun = new shotGun();
    secondGun = new avtomat();

    visionCorner = 0;

}

player::~player()
{
}


int player::playerStep(ÑardinalDirections step_Direction)
{

    if (hitPoints > 0)
    {
        double corner = this->visionCorner;
        int i = 0;
        switch (step_Direction)
        {
        case East: corner -= 90; break;
        case South: corner += 180; break;
        case West: corner += 90; break;
        default: i = 1;
        }
        corner = (corner * 3.14) / 180;
        double x = this->speed * cos(corner);
        double y = this->speed * sin(corner);

        this->coordX += x;
        this->coordY += y;
        return i;
    }
    return 2;

}


int player::changeActiveWeapon() 
{
    switch (activeWeapon)
    {
    case ShotGun:
        activeWeapon = Automat;
        break;
    case Automat:
        activeWeapon = ShotGun;
        break;
    }
    return activeWeapon;
};

int player::shot(std::vector<bullet>& bullets)
{
    switch (activeWeapon)
    {
    case ShotGun:   
        this->firstGun->shot(coordX, coordY, visionCorner, bullets);
        break;
    case Automat:
        this->secondGun->shot(coordX, coordY, visionCorner, bullets);
        break;
    }

    return activeWeapon;
};

void player::changeVision(ÑardinalDirections direct_pl)
{
    switch (direct_pl)
    {
    case East:
        visionCorner -= VISION_SPEED;
        break;
    case West:
        visionCorner += VISION_SPEED;
        break;
    default:
        break;
    };

    if (abss(visionCorner) >= 360)
    {
        visionCorner = 0;
    }


    

};