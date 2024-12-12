#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <windows.h>
#include "game.h"
#include "final.h"
#include "drawer.h"
#include "GameMap.h"
#include "entity.h"


using namespace std;
using namespace sf;

int Entity::last_id = 0;
const float Entity::FRAME_SPEED = 0.25;
void change_final(const EndingOption option, final* f)
{
	f->gameEndType = option;
}


int main()
{
	srand(time(nullptr));
	std::string world_map[GameMap::MAPSIZEX];
	world_map[0] += "##k####d##";
	world_map[1] += "#........#";
	world_map[2] += "#........w";
	world_map[3] += "w........#";
	world_map[4] += "#........k";
	world_map[5] += "#..#k....#";
	world_map[6] += "w...#k...w";
	world_map[7] += "#..#..#..#";
	world_map[8] += "#........n";
	world_map[9] += "##########";

	GameMap* w_map;
	w_map = new GameMap(world_map);
	drawer* dr;
	dr = new drawer();
	final* ending;
	ending = new final;
	game* dom;
	dom = new game();

	RenderWindow window(VideoMode(drawer::SCREEN_WIDTH, drawer::SCREEN_HEIGHT), "Graphic Test");
	//RenderWindow window(VideoMode(1920, 1080), "Graphic Test");
	window.setSize(sf::Vector2u(1280, 720));
	window.setPosition(sf::Vector2i(320, 180));
	bool end_fl = false; //флажок работы игры
	bool shot_fl = true;
	bool swap_fl = true;
	bool spawn_fl = true;
	bool reloading_fl = true;

	window.setMouseCursorVisible(false);
	Mouse::setPosition(Vector2i(drawer::SCREEN_WIDTH / 2, drawer::SCREEN_HEIGHT / 2), window);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				if (shot_fl)
				{
					dom->playerShot();
					shot_fl = false;
				}
			}
			else
				shot_fl = true;


			if (event.type == Event::MouseMoved)
			{
				Vector2i current_mouse_position = Mouse::getPosition(window);
				int delta_x = current_mouse_position.x - drawer::SCREEN_WIDTH / 2;
				dom->you->changeVision(delta_x * 0.1);
				Mouse::setPosition(Vector2i(drawer::SCREEN_WIDTH / 2, drawer::SCREEN_HEIGHT / 2), window);
			}

			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				window.close();
				return 0;
			}
		}

		window.clear(Color::Black);

		if (!end_fl)
		{
			//обработка действий игрока
			if (GetAsyncKeyState(0X57))
			{
				dom->you->playerMapStep(North, w_map);
			}
			if (GetAsyncKeyState(0X53))
			{
				dom->you->playerMapStep(South, w_map);
			}
			if (GetAsyncKeyState(0X44))
			{
				dom->you->playerMapStep(East, w_map);
			}
			if (GetAsyncKeyState(0X41))
			{
				dom->you->playerMapStep(West, w_map);
			}

			if (GetAsyncKeyState(VK_LCONTROL))
			{
				if (swap_fl)
				{
					dom->you->changeActiveWeapon();
					swap_fl = false;
				}
			}
			else
				swap_fl = true;

			if (GetAsyncKeyState(VK_LSHIFT))
			{
				if (reloading_fl)
				{
					dom->you->getActiveWeapon()->reloading();
					reloading_fl = false;
				}
			}
			else
				reloading_fl = true;


			if (GetAsyncKeyState(VK_F1))
			{
				if (spawn_fl)
				{
					++(*dom);
					spawn_fl = false;
				}
			}
			else
				spawn_fl = true;

			//взаимодействие объектов
			dom->interaction(w_map);

			//рисование кадра
			dr->drawWalls(w_map, dom, window);

			try
			{
				dr->entityDraw(dom, window);
			}
			catch (std::out_of_range)
			{
				change_final(WinGame, ending);
				end_fl = true;
			}
			catch (std::logic_error)
			{
				change_final(LooseGame, ending);
				end_fl = true;
			}

			dr->drawPlayerWeapon(dom, window);
		}
		else
			ending->outputFinal(window);

		window.display();
	}
}
