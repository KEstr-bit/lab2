#pragma once
#include <SFML/Graphics.hpp>
#include "GameMap.h"
#include "game.h"
#include "entity.h"

using namespace sf;

class drawer
{
public:
	//��������� ����
	int drawWalls(GameMap* map, game* gm, sf::RenderWindow& window);
	//��������� ��������
	int entityDraw(game* gm, sf::RenderWindow& window);
	drawer();
	~drawer();

private:
	//��������� �������� �� �����������
	void drawImage(sf::RenderWindow& window, const sf::Texture* texture, float x, float y, float width, float height);
	//��������� ������������ ������
	void drawVerticalSegment(sf::RenderWindow& window, float length, float width, float low_X, float low_Y, sf::Color color);
	//��������� ����������
	void dependSorting(std::vector<double>& mainMas, std::vector<entity*>& sideMas, int left, int right);

public:
	static const double RAY_STEP;			//��� ����
	static const int SCREEN_WIDTH = 800;	//������ ������
	static const int SCREEN_HEIGHT = 600;	//������ ������

private:
	double mas[SCREEN_WIDTH];				//������  ���� ������������ �����


};

