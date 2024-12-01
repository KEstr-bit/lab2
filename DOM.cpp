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

int Entity::lastID = 0;

void changeFinal(EndingOption option, final* f)
{
    f->gameEndType = option;
}


int main()
{
    srand(time(NULL));
    std::string worldMap[GameMap::MAPSIZEX];
    worldMap[0] += "##k####d##";
    worldMap[1] += "#........#";
    worldMap[2] += "#........w";
    worldMap[3] += "w...##...#";
    worldMap[4] += "#...#d...k";
    worldMap[5] += "#...k#...#";
    worldMap[6] += "w...#k...w";
    worldMap[7] += "#..#..#..#";
    worldMap[8] += "#........n";
    worldMap[9] += "##d#######";

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
    bool spawnfl = true;


    window.setMouseCursorVisible(false);
    sf::Mouse::setPosition(sf::Vector2i(drawer::SCREEN_WIDTH/2, drawer::SCREEN_HEIGHT/2), window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
                {
                    if (shotfl)
                    {
                        DOM->playerShot();
                        shotfl = false;
                    }
                }
            else
                shotfl = true;
            

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i currentMousePosition = sf::Mouse::getPosition(window);
                int deltaX = currentMousePosition.x - drawer::SCREEN_WIDTH/2;
                DOM->you->changeVision(deltaX*0.1);
                sf::Mouse::setPosition(sf::Vector2i(drawer::SCREEN_WIDTH/2, drawer::SCREEN_HEIGHT/2), window);
            }
        }
        
        window.clear(sf::Color::Black);

        if (!endFl)
        {
            //обработка действий игрока
            if (GetAsyncKeyState(0X57))
            {
                DOM->you->playerMapStep(North, wMap);
            }
            if (GetAsyncKeyState(0X53))
            {
                DOM->you->playerMapStep(South, wMap);
            }
            if (GetAsyncKeyState(0X44))
            {
                DOM->you->playerMapStep(East, wMap);
            }
            if (GetAsyncKeyState(0X41))
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


            if (GetAsyncKeyState(VK_F1))
            {
                if (spawnfl)
                {
                    (*DOM)++;
                    spawnfl = false;
                }
            }
            else
                spawnfl = true;

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





















