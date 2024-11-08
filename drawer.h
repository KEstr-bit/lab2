#pragma once
#include "GameMap.h"
#include "game.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class drawer
{
public:
	int newDraw(GameMap* map, game* gm, sf::RenderWindow& window);
	void drawVerticalSegment(sf::RenderWindow& window, float length, float width, float low_X, float low_Y, sf::Color color);
	int entityDraw(game* gm, sf::RenderWindow& window);
	drawer();
	~drawer();

public:
	static const double RAY_STEP;
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

private:
	double mas[SCREEN_WIDTH];


};

