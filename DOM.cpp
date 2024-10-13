#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <windows.h>
#include "final.h"
#include "helper.h"
#include "game.h"
using namespace std;

final ending;

int main()
{
    system("cls");
    game* DOM;
    DOM = new game();

    printf("\e[?25l");
    int i = 1;  //флажок работы игры
    while (i)
    {
        //обработка действий игрока
        if (GetAsyncKeyState(VK_UP))
        {
            DOM->gamePlayerStep(North);
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            DOM->gamePlayerStep(South);
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            DOM->gamePlayerStep(East);
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            DOM->gamePlayerStep(West);
        }
        if (GetAsyncKeyState(VK_BACK))
        {
            double X_Coord, Y_Coord;
            int rotation;
            DOM->you->getEntityCoord(&X_Coord, &Y_Coord);
            rotation = DOM->you->getPlayerRotation();
            DOM->you->gun->Shot(X_Coord, Y_Coord, rotation);
        }

        DOM->monster->enemyMovment(DOM->map, DOM->Map_Size_X, DOM->you);     //движение врага
        DOM->you->gun->allBulletMovment();    //движение пули
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
    ending.vivodFinal();
    Sleep(50);


}





















