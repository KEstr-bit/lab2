#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include "final.h"
#include "helper.h"
#include "game.h"
#include "drawer.h"
#include <SFML/Graphics.hpp>
#include <windows.h>

using namespace std;
using namespace sf;
final ending;

int entity::lastID = 0;

int main()
{
    game* DOM;
    DOM = new game();

    std::string worldMap[10];
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


    sf::RenderWindow window(sf::VideoMode(800, 600), "Vertical Segment Drawing");
    int s = 0;
    int fl = 1;  //флажок работы игры

    bool shotfl = true;
    bool swapfl = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


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
            



            DOM->interaction(wMap);      //взаимодействие объектов

            //проверка окончания игры
            if (DOM->you->getEntityHitPoints() <= 0)
            {
                ending.changeType(LooseGame);
                fl = 0;
            }
        


        if (GetAsyncKeyState(0X41))
        {
            DOM->you->changeVision(West);

        }

        if (GetAsyncKeyState(0X44))
        {
            DOM->you->changeVision(East);
        }
        //очистка
        window.clear(sf::Color::Black);

        //рисование кадра
        
        dr->newDraw(wMap, DOM, window);
        dr->entityDraw(DOM, window);

        //отображение содержимого окна
        window.display();


    }
}





















