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
	static const double RAY_STEP;			//шаг луча
	static const int SCREEN_WIDTH = 640;	//ширина экрана
	static const int SCREEN_HEIGHT = 360;	//высота экрана

private:
	float lengthsAndIndexes[SCREEN_WIDTH][2];				//массив  длин вертикальных полос

public:
	//отрисовка стен
	void drawWalls(GameMap& map, const Game& gm, sf::RenderWindow& window);
	//отрисовка объектов
	void entityDraw(const Game& gm, sf::RenderWindow& window);

	static void drawPlayerWeapon(const Game& gm, sf::RenderWindow& window);
	Drawer();
	~Drawer();

private:
	//отрисовка текстуры по координатам
	static void drawImage(sf::RenderWindow& window, const sf::Texture& texture, float x, float y, float textureX, float textureY, float width, float height);
	//отрисовка вертикальной полосы
	static void drawVerticalSegment(sf::RenderWindow& window, float length, float stripIndex, float x, float y, const sf::Texture& texture);
};

