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

final ending;

int entity::lastID = 0;

bool isEnd(game* gm)
{
    if (gm->entities.size() == 0)
        return true;

    if (gm->you->getEntityHitPoints() <= 0)
        return true;

    return false;
}

int main()
{
    game* DOM;
    DOM = new game();

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
    SetConsoleOutputCP(866);


    sf::RenderWindow window(sf::VideoMode(drawer::SCREEN_WIDTH, drawer::SCREEN_HEIGHT), "Vertical Segment Drawing");
    int s = 0;
    bool endFl = false;  //флажок работы игры
    bool resProcFl = true;
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
            endFl = isEnd(DOM);
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

            DOM->interaction(wMap);      //взаимодействие объектов

            

            //рисование кадра
            dr->newDraw(wMap, DOM, window);
            dr->entityDraw(DOM, window);
            
        }
        else if (resProcFl)
        {
            if (DOM->you->getEntityHitPoints() <= 0)
                ending.changeFinal(LooseGame);
            resProcFl = false;
        }
        else
            ending.outputFinal(window);

        window.display();
    }
}





















