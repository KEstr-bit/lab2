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

int main()
{
    game* DOM;
    DOM = new game();
    GameMap* wMap;
    wMap = new GameMap();
    drawer* dr;
    dr = new drawer();
    SetConsoleOutputCP(866);

    char map[10][10];
    wMap->getWorldMap(map);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Vertical Segment Drawing");
    int s = 0;
    int fl = 1;  //флажок работы игры
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (s > 50)
        {
            s = 0;
            //обработка действий игрока
            if (GetAsyncKeyState(VK_UP))
            {
                DOM->you->gamePlayerStep(map[0], North);
            }
            if (GetAsyncKeyState(VK_DOWN))
            {
                DOM->you->gamePlayerStep(map[0], South);
            }
            if (GetAsyncKeyState(VK_RIGHT))
            {
                DOM->you->gamePlayerStep(map[0], East);
            }
            if (GetAsyncKeyState(VK_LEFT))
            {

                DOM->you->gamePlayerStep(map[0], West);
            }
            if (GetAsyncKeyState(VK_LCONTROL))
            {

                DOM->you->changeActiveWeapon();
            }
            if (GetAsyncKeyState(VK_LSHIFT))
            {

                DOM->you->shot(DOM->bullets);
            }

            
        }


            DOM->interaction(map);      //взаимодействие объектов

            //проверка окончания игры
            if (DOM->you->getEntityHitPoints() <= 0)
            {
                ending.changeType(LooseGame);
                fl = 0;
            }
            if (DOM->monster->getEntityHitPoints() <= 0)
            {
                ending.changeType(WinGame);
                fl = 0;
            }
        

        s++;
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
        dr->newDraw(map, DOM, window);


        //отображение содержимого окна
        window.display();

        Sleep(1);

    }
}





















