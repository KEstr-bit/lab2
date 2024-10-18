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
    map* wMap;
    wMap = new map();

    char map[10][10];
    int mapSizeX;
    wMap->getWorldMap(map);

    int fl = 1;  //флажок работы игры
    while (fl)
    {
        
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

            DOM->you->shot();
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

        //вывод состояния игры
        DOM->vivod(map);
        Sleep(50);


    };
    //завершение игры
    system("cls");
    ending.outputFinal();
    Sleep(50);


}





















