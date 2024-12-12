#pragma once
#include <SFML/Graphics.hpp>
#include "GameMap.h"
#include "Game.h"
#include "Entity.h"
#include <vector>

using namespace sf;

class Drawer
{
public:
	//отрисовка стен
	void drawWalls(GameMap* map, Game* gm, sf::RenderWindow& window);
	//отрисовка объектов
	void entityDraw(Game* gm, sf::RenderWindow& window);

	void drawPlayerWeapon(Game* gm, sf::RenderWindow& window)
	{
		gm->you->getActiveWeapon()->getTextureX();
		gm->you->getActiveWeapon()->getTextureY();
		drawImage(window, gm->tPack->getTexture(gm->you->getActiveWeapon()->texture), SCREEN_WIDTH - SCREEN_HEIGHT,
			SCREEN_HEIGHT / 3, gm->you->getActiveWeapon()->getTextureX(), gm->you->getActiveWeapon()->getTextureY(), SCREEN_HEIGHT/1.5, SCREEN_HEIGHT/1.5);
	}
	Drawer();
	~Drawer();

private:
	//отрисовка текстуры по координатам
	void drawImage(sf::RenderWindow& window, const sf::Texture* texture, float x, float y, float textureX, float textureY, float width, float
	               height);
	//отрисовка вертикальной полосы
	void drawVerticalSegment(sf::RenderWindow& window, float length, float stripIndex, float x, float y, const sf::Texture* texture);
	//зависимая сортировка
	void dependSorting(std::vector<double>& mainMas, std::vector<Entity*>& sideMas, int left, int right);
	//вычслить угол поворта
	double getRotAngle(double playerAngle, double cosPlEnLine, double sinPlEnLine);
	
public:
	static const double RAY_STEP;			//шаг луча
	static const int SCREEN_WIDTH = 640;	//ширина экрана
	static const int SCREEN_HEIGHT = 360;	//высота экрана

private:
	float mas[SCREEN_WIDTH][2];				//массив  длин вертикальных полос


};

