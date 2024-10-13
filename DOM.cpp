#define _CRT_SECURE_NO_WARNINGS


#include <windows.h>
#include "final.h"
#include "helper.h"
#include "game.h"
using namespace std;

final ending;

int main()
{
    game* DOM;
    DOM = new game();
    char map[10][10];
    int mapSizeX;
    DOM->getWorldMap(map);
    mapSizeX = DOM->getMapSizeX();
    int i = 1;  //флажок работы игры
    while (i)
    {
        
        //обработка действий игрока
        if (GetAsyncKeyState(VK_UP))
        {
            DOM->you->gamePlayerStep(map[0], mapSizeX, North);
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            DOM->you->gamePlayerStep(map[0], mapSizeX, South);
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            DOM->you->gamePlayerStep(map[0], mapSizeX, East);
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            DOM->you->gamePlayerStep(map[0], mapSizeX, West);
        }
        if (GetAsyncKeyState(VK_LCONTROL))
        {

            DOM->you->changeActiveWeapon();
        }
        if (GetAsyncKeyState(VK_LSHIFT))
        {

            DOM->you->shot();
        }

       
        DOM->interaction();      //взаимодействие объектов

        //проверка окончания игры
        if (DOM->you->getEntityHitPoints() <= 0)
        {
            ending.changeType(LooseGame);
            i = 0;
        }
        if (DOM->monster->getEntityHitPoints() <= 0)
        {
            ending.changeType(WinGame);
            i = 0;
        }

        //вывод состояния игры
        DOM->vivod();
        Sleep(50);


    };
    //завершение игры
    system("cls");
    ending.outputFinal();
    Sleep(50);


}





















