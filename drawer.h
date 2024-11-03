#pragma once
#include "map.h"
#include "game.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class drawer
{
public:
	int draw(char world_Map[MAP_SIZE_X][MAP_SIZE_Y], game* gm);
	int newDraw(char world_Map[MAP_SIZE_X][MAP_SIZE_Y], game* gm, sf::RenderWindow& window);
	void drawVerticalSegment(sf::RenderWindow& window, float length, float width, float low_X, float low_Y, sf::Color color);
	drawer();
	~drawer();

private:
	char* firstBuffer;
	char* secondBuffer;
};

