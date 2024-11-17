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

int entity::lastID = 0;

void changeFinal(EndingOption option, final* f)
{
    f->gameEndType = option;
}

int main()
{
    std::string worldMap[GameMap::MAPSIZEX];
    worldMap[0] += "##########";
    worldMap[1] += "#........#";
    worldMap[2] += "#........#";
    worldMap[3] += "#...##...#";
    worldMap[4] += "#...##...#";
    worldMap[5] += "#...##...#";
    worldMap[6] += "#...##...#";
    worldMap[7] += "#..#..#..#";
    worldMap[8] += "#........#";
    worldMap[9] += "##########";

    GameMap* wMap;
    wMap = new GameMap(worldMap);
    drawer* dr;
    dr = new drawer();
    final* ending;
    ending = new final;
    game* DOM;
    DOM = new game();
 
    sf::RenderWindow window(sf::VideoMode(drawer::SCREEN_WIDTH, drawer::SCREEN_HEIGHT), "Graphic Test");
    bool endFl = false;         //флажок работы игры
    bool shotfl = true;
    bool swapfl = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color::Black);

        if (!endFl)
        {
            //обработка действий игрока
            if (GetAsyncKeyState(VK_UP))
            {
                DOM->you->playerMapStep(North, wMap);
            }
            if (GetAsyncKeyState(VK_DOWN))
            {
                DOM->you->playerMapStep(South, wMap);
            }
            if (GetAsyncKeyState(VK_RIGHT))
            {
                DOM->you->playerMapStep(East, wMap);
            }
            if (GetAsyncKeyState(VK_LEFT))
            {

                DOM->you->playerMapStep(West, wMap);
            }

            if (GetAsyncKeyState(VK_LCONTROL))
            {
                if (swapfl)
                {
                    DOM->you->changeActiveWeapon();
                    swapfl = false;
                }
            }
            else
                swapfl = true;

            if (GetAsyncKeyState(VK_LSHIFT))
            {
                if (shotfl)
                {
                    DOM->playerShot();
                    shotfl = false;
                }
            }
            else
                shotfl = true;

            if (GetAsyncKeyState(0X41))
            {
                DOM->you->changeVision(West);

            }

            if (GetAsyncKeyState(0X44))
            {
                DOM->you->changeVision(East);
            }

            if (GetAsyncKeyState(VK_F1))
            {
                (*DOM)++;
            }

            //взаимодействие объектов
            DOM->interaction(wMap);      

            //рисование кадра
            dr->drawWalls(wMap, DOM, window);

            try
            {
                dr->entityDraw(DOM, window);
            }
            catch (std::out_of_range)
            {
                changeFinal(WinGame, ending);
                endFl = true;
            }
            catch (std::logic_error)
            {
                changeFinal(LooseGame, ending);
                endFl = true;
            }

        }
        else
            ending->outputFinal(window);

        window.display();
    }
}





















