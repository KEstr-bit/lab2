#pragma once
#include <SFML/Graphics.hpp>
#include "GameMap.h"
#include "game.h"
#include "entity.h"

using namespace sf;

class drawer
{
public:
	//отрисовка стен
	int drawWalls(GameMap* map, game* gm, sf::RenderWindow& window);
	//отрисовка объектов
	int entityDraw(game* gm, sf::RenderWindow& window);
	drawer();
	~drawer();

private:
	//отрисовка текстуры по координатам
	void drawImage(sf::RenderWindow& window, const sf::Texture* texture, float x, float y, float width, float height);
	//отрисовка вертикальной полосы
	void drawVerticalSegment(sf::RenderWindow& window, float length, float width, float low_X, float low_Y, sf::Color color);
	//зависимая сортировка
	void dependSorting(std::vector<double>& mainMas, std::vector<entity*>& sideMas, int left, int right);

public:
	static const double RAY_STEP;			//шаг луча
	static const int SCREEN_WIDTH = 800;	//ширина экрана
	static const int SCREEN_HEIGHT = 600;	//высота экрана

private:
	double mas[SCREEN_WIDTH];				//массив  длин вертикальных полос


};

