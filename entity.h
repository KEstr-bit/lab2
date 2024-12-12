#pragma once
#include "TexturePack.h"
#include "GameMap.h"
#include "Helper.h"
#include "QuadTree.h"

class Entity
{
protected:
    double cordX;             //координата по X
    double cordY;             //координата по Y
    double hitPoints;             //очки здоровья 
    int damage;                //урон наносимый
    double speed;              //скорость 
    double viewAngle;          //угол обзора
    double size;               //размер
    textureType texture;       //текстура 
    float textureX;
    float textureY;
    bool eventFl = false;
    bool friendly = false;
public:
    virtual ~Entity() = default;
    static int last_id;          //последний записанный id
    static const float FRAME_SPEED;
    Entity(double cord_x, double cord_y, double speed, int hit_points, int damage, textureType texture);
    Entity();
    bool isfriendly();
    bool getEntityCord(double* cord_x, double* cord_y) const;
    bool getEntityCord(int* cord_x, int* cord_y);
    int getEntityDamage();
    int getEntityHitPoints();
    double getEntityAngle();
    double getSize();
    textureType getTextureType();
    float getTextureX() const;
    float getTextureY() const;
    //нанести урон объекту
    void attackEntity(int damage);
    //движение вдоль направления взгляда
    bool isAlive();
    bool entityStep();
    bool entityStep(double len);
    //движение с учетом стен
    bool entityMapStep(GameMap* map);
    void Step(GameMap* map, double angle);
    //виртуальная функция движения для наследников
    virtual bool update(GameMap* map, std::vector<Entity*>& entities) = 0;
    bool frameShift();

    bool intersects(const Entity* other, float error_rate) const {
	    const double distance = Helper::calcDistance(cordX, cordY, other->cordX, other->cordY);
	    return distance < (size + other->size) * error_rate / 2;
    }


};
