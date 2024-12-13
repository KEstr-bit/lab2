#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Game.h"
#include "Final.h"
#include "Drawer.h"
#include "GameMap.h"

using namespace std;
using namespace sf;

const float AnimationControl::FRAME_SPEED = 0.25;
const double Rifle::SIDE_SHIFT = 0.25;
const double ShotGun::SIDE_SHIFT = 0.25;
const int ShotGun::SPREAD_ANGLE = 30;

void change_final(const EndingOption option, Final* f)
{
	f->endingOption = option;
}

int main()
{
	srand(time(nullptr));
	std::string worldMap[GameMap::MAP_SIZE_X];
	worldMap[0] += "##k####d##";
	worldMap[1] += "#........#";
	worldMap[2] += "#........w";
	worldMap[3] += "w........#";
	worldMap[4] += "#........k";
	worldMap[5] += "#..#k....#";
	worldMap[6] += "w...#k...w";
	worldMap[7] += "#..#..#..#";
	worldMap[8] += "#........n";
	worldMap[9] += "##########";

	GameMap* gameMap;
	gameMap = new GameMap(worldMap);
	Drawer* drawer;
	drawer = new Drawer();
	Final* ending;
	ending = new Final;
	Game* game;
	game = new Game();

	RenderWindow window(VideoMode(Drawer::SCREEN_WIDTH, Drawer::SCREEN_HEIGHT), "Graphic Test");
	//RenderWindow window(VideoMode(1920, 1080), "Graphic Test");
	window.setSize(sf::Vector2u(1280, 720));
	window.setPosition(sf::Vector2i(320, 180));
	bool endFl = false; //флажок работы игры
	bool shotFl = true;
	bool swapFl = true;
	bool reloadingFl = true;

	window.setMouseCursorVisible(false);
	Mouse::setPosition(Vector2i(Drawer::SCREEN_WIDTH / 2, Drawer::SCREEN_HEIGHT / 2), window);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				if (shotFl)
				{
					game->playerShot();
					
					shotFl = false;
				}
			}
			else
				shotFl = true;


			if (event.type == Event::MouseMoved)
			{
				Vector2i currentMousePosition = Mouse::getPosition(window);
				int deltaX = currentMousePosition.x - Drawer::SCREEN_WIDTH / 2;
				game->player->changeVision(deltaX * 0.1);
				Mouse::setPosition(Vector2i(Drawer::SCREEN_WIDTH / 2, Drawer::SCREEN_HEIGHT / 2), window);
			}

			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				window.close();
				return 0;
			}
		}

		window.clear(Color::Black);

		if (!endFl)
		{
			//обработка действий игрока
			if (GetAsyncKeyState(0X57))
			{
				game->player->playerMapStep(NORTH, *gameMap);
			}
			if (GetAsyncKeyState(0X53))
			{
				game->player->playerMapStep(SOUTH, *gameMap);
			}
			if (GetAsyncKeyState(0X44))
			{
				game->player->playerMapStep(EAST, *gameMap);
			}
			if (GetAsyncKeyState(0X41))
			{
				game->player->playerMapStep(WEST, *gameMap);
			}

			if (GetAsyncKeyState(VK_LCONTROL))
			{
				if (swapFl)
				{
					game->player->changeActiveWeapon();
					swapFl = false;
				}
			}
			else
				swapFl = true;

			if (GetAsyncKeyState(VK_LSHIFT))
			{
				if (reloadingFl)
				{
					game->player->getActiveWeapon()->reloading();
					reloadingFl = false;
				}
			}
			else
				reloadingFl = true;


			//взаимодействие объектов
			game->interaction(*gameMap);

			//рисование кадра
			drawer->drawWalls(*gameMap, *game, window);

			try
			{
				drawer->entityDraw(*game, window);
			}
			catch (std::out_of_range)
			{
				change_final(WIN_GAME, ending);
				endFl = true;
			}
			catch (std::logic_error)
			{
				change_final(LOOSE_GAME, ending);
				endFl = true;
			}

			drawer->drawPlayerWeapon(*game, window);
		}
		else
			ending->outputFinal(window);

		window.display();
	}
}
